#ifndef C1DRECOBJECTIVE_H
#define C1DRECOBJECTIVE_H
#include "PlottableObjective.h"
#include "RecCalc.h"
#include "SeismicDataComp.h"
#include <boost/shared_ptr.hpp>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include "NumUtil.h"
#include "CollapseModel.h"
#include "SeisTools.h"
#include "convert.h"
#include "miscfunc.h"
#include "FatalException.h"
namespace gplib
  {
    //! Calculate the misfit between observed receiver function for a given 1D model by calculating a synthetic receiver function from that model
    /*! The constructor takes a few essential parameters that are expected not to change during the
     * program (in most cases inversion), e.g. the data to fit. See also #C1DRecObjective for the necessary
     * constructor parameters.
     *
     * There are two ways to calculate the Misfit for a given model, either calling GeneralObjective#CalcPerformance,
     * or, for parallel programs, calling the three function PreParallel, SafeParallel and PostParallel in that order.
     * In both cases you have to give the parameter #member, which is a ::ttranscribed of size 2n, where
     * n is the number of layers of the model. The first n entries are the layer thicknesses in km and the last n entries
     * are the S-wave velocities in km/s. Densities and P-Wave velocities are calculated from S-Velocities by hard-coded relationships.
     */
    class C1DRecObjective: public PlottableObjective
      {
    private:
      //! The object holding the calculated synthetic data
      SeismicDataComp RecSynthData;
      //! The slowness used in the calculation
      double slowness;
      //! The object holding the 1D model for forward calculation
      ResPkModel Model;
      //! The object used to calculate the synthetics
      RecCalc RecCalculator;
      //! The relative errorfloor
      double errorlevel;
      //! The absolute errorfloor is calculated from the relative errorfloor
      double errorvalue;
      //! Poisson's ratio vp/vs, this might become part of the model
      double poisson;
      //! We might not want to use the whole receiver function for misfit calculation, the startpoint is calculated from the starttime in SetTimeWindow
      int startpoint;
      //! We might not want to use the whole receiver function for misfit calculation, the endpoint is calculated from the endtime in SetTimeWindow
      int endpoint;
      //! The measured data is stored in a shared pointer.
      /*! For parallel implementations we often work with several instances of this
       * class that all work with the same ObservedData. To save memory we use a shared_pointer
       * and to avoid collisions SeismicDataComp is const */
      boost::shared_ptr<const SeismicDataComp> ObservedData;
    protected:
      const SeismicDataComp &GetObservedData()
        {
          return *ObservedData;
        }
    public:
      //! return a pointer to a copy of the current object
      virtual C1DRecObjective *clone() const
        {
          return new C1DRecObjective(*this);
        }
      //! Set the time window used for misfit calculations, start and end are in seconds
      void SetTimeWindow(const double start, const double end)
      {
        //calculate the startpoint corresponding to the starttime
        //if the values do not make sense, we use the the minimum
        // and maximum possible indices respectively
        startpoint = max(boost::numeric_cast<size_t>(0), boost::numeric_cast<
            size_t>((start - ObservedData->GetB()) / ObservedData->GetDt()));
        // calculate datapoint corresponding to the endtime
        endpoint = min(boost::numeric_cast<size_t>((end - ObservedData->GetB())
            / ObservedData->GetDt()), ObservedData->GetData().size());
        //the only thing that remains to be checked is whether the start is before the end
        if (endpoint < startpoint)
          throw FatalException("Start index " + stringify(startpoint)
              + " and end index " + stringify(endpoint)
              + " do not make sense !");
      }
      //! Set the errorlevel for fit, this is relative to the maximum amplitude, not for each individual data point
      void SetErrorLevel(const double level)
        {
          errorlevel = level;
          const double recmaxamp = *std::max_element(
              ObservedData->GetData().begin(), ObservedData->GetData().end());
          // we specify the error relative to the maximum amplitude
          //this is usually the initial correlation peak
          // here we calculate its value
          errorvalue = errorlevel * recmaxamp;
        }
      //! Set poisson's ratio, at the moment the same for all layers, used for calculating P-velocity
      void SetPoisson(const double ratio)
        {
          poisson = ratio;
        }
      //! Write the synthetic data to a sac file with name filename, makes only sense after calculating the misfit
      virtual void WriteData(const std::string &filename)
        {
          RecSynthData.WriteAsSac(filename);
        }
      //! Write the current model to ascii file for calculations
      void WriteModel(const std::string &filename)
        {
          Model.WriteModel(filename);
        }
      //! Write the current model to ascii file for plotting
      void WritePlot(const std::string &filename)
        {
          Model.WritePlot(filename);
        }
      //! We have to write runfiles before parallel execution
      virtual void PreParallel(const ttranscribed &member)
      {
        const unsigned int nfulllayers = member.size() / 2; //The model vector contains thickness and SVel, so we have size/2 layers

        Model.SetSlowness(slowness); //copy slowness
        ttranscribed thickness(nfulllayers), velocity(nfulllayers);
        copy(member.begin(), member.begin() + nfulllayers, thickness.begin()); //copy values
        copy(member.begin() + nfulllayers, member.begin() + 2 * nfulllayers,
            velocity.begin());
        CollapseModel(thickness, velocity);//reduce to minimum number of different layers
        const unsigned int ncolllayers = velocity.size();
        Model.Init(ncolllayers); //initialize model with number of reduced layers
        copy(thickness.begin(), thickness.end(), Model.SetThickness().begin());
        copy(velocity.begin(), velocity.end(), Model.SetSVelocity().begin());
        transform(velocity.begin(), velocity.end(), Model.SetDensity().begin(),
            CalcDensity());
        transform(velocity.begin(), velocity.end(), //PVelocity is calculated by multiplication of SVel by poisson's ratio
            Model.SetPVelocity().begin(), boost::bind(multiplies<double> (),
                _1, poisson));
        Model.SetDt(ObservedData->GetDt()); // set dt
        Model.SetNpts(ObservedData->GetData().size()); //set number of points
        RecCalculator.SynthPreParallel(GetParallelID(), Model, RecSynthData,
            true);
      }
      //! We also clean up files serially
      virtual double PostParallel(const ttranscribed &member)
      {
        RecCalculator.SynthPostParallel(GetParallelID(), Model, RecSynthData,
            true);
        SetMisfit().resize(endpoint - startpoint);//we need vectors of the right size for misfit
        SetSynthData().resize(endpoint - startpoint);//and  data
        double returnvalue = 0.0;//init returnvalue
        //go through the receiver function from the starttime to the endtime point by point
        for (int i = startpoint; i < endpoint; ++i)

          {
            //calculate the misfit for each point and add up
            //the relative errorlevel is 0. as it does not make sense for receiver functions
            //therefore always errorvalue will be used as an absolue error
            returnvalue += CalcMisfit(ObservedData->GetData().at(i),
                RecSynthData.GetData().at(i), errorvalue, 0.0, i - startpoint);
          }
        //copy the head information from the observed receiver function
        RecSynthData.CopyHeader(*ObservedData.get());
        SetRMS(std::pow(returnvalue / (endpoint - startpoint), 1.0
            / GetFitExponent())); //store misfit in local class
        return GetRMS(); //return misfit calculated by SafeParallel
      }

      //! Calculate the misfit between the data calculated from model vector member and measured data given in the constructor.
      virtual void SafeParallel(const ttranscribed &member)
      {
        RecCalculator.SynthSafeParallel(GetParallelID(), Model, RecSynthData,
            true); // Calculate forward model
      }
      C1DRecObjective(const C1DRecObjective &Old) :
          PlottableObjective(Old), RecSynthData(Old.RecSynthData), slowness(
              Old.slowness), Model(Old.Model), RecCalculator(Old.RecCalculator),
              errorlevel(Old.errorlevel), errorvalue(Old.errorvalue), poisson(
                  Old.poisson), startpoint(Old.startpoint), endpoint(Old.endpoint),
              ObservedData(Old.ObservedData)
          {
          }

      C1DRecObjective& operator=(const C1DRecObjective& source)
      {
        if (this == &source)
          return *this;
        PlottableObjective::operator=(source);
        RecSynthData = source.RecSynthData;
        slowness = source.slowness;
        Model = source.Model;
        RecCalculator = source.RecCalculator;
        poisson = source.poisson;
        errorlevel = source.errorlevel;
        errorvalue = source.errorvalue;
        startpoint = source.startpoint;
        endpoint = source.endpoint;
        ObservedData = source.ObservedData;
        return *this;
      }
      //! The constructor needs a few essential parameters
      /*! @param TheRecData   Shared pointer to the measured receiver function
       *  @param myshift    the time shift used for calculating the measured receiver function
       *  @param mysigma sigma used for calculating the measured receiver function
       *  @param myc water level used for calculating the measured receiver function
       *  @param myslowness slowness used for calculating the measured receiver function
       * @param method The method used to calculate the observed data. Can be specdiv or iterdecon
       * @param normalized Is the measured data normalized to an initial correlation peak of 1
       */
      C1DRecObjective(boost::shared_ptr<const SeismicDataComp> TheRecData,
          const int myshift, const double mysigma, const double myc,
          const double myslowness, const RecCalc::trfmethod method =
              RecCalc::specdiv, const bool normalized = true) :
          RecCalculator(myshift, mysigma, myc, true, method), ObservedData(
              TheRecData)
          {
            slowness = myslowness; //copy parameter value
            poisson = sqrt(3.); //set some default values
            //we specify a default errorlevel of 1%
            SetErrorLevel(0.01);
            //by default we fit the complete receiver function
            startpoint = 0;
            endpoint = ObservedData->GetData().size();
            // we determine the maximum amplitude of the receiver function

            const double recmaxamp = *max_element(ObservedData->GetData().begin(),
                ObservedData->GetData().end());
            const bool isone = fcmp(recmaxamp, 1.0, 1e-4) == 0;
            if (isone && !normalized)
              throw FatalException(
                  "Input data has maximum amplitude of 1, but no normalization used");
            if (!isone && normalized)
              throw FatalException(
                  "Input data does not have an amplitude of 1, but normalization is used");
            RecCalculator.SetNormalize(normalized);// we can choose we want to model normalized data
          }

      virtual ~C1DRecObjective();
      friend class AbsVelRecObjective;
      };
  }
#endif // C1DRECOBJECTIVE_H
