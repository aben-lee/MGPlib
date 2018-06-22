#ifndef SURFACEWAVEOBJECTIVE_H_
#define SURFACEWAVEOBJECTIVE_H_

#include "PlottableObjective.h"
#include "SurfaceWaveData.h"
#include "SurfaceWaveSynthetic.h"
#include <string>
#include <boost/bind.hpp>
#include "SeisTools.h"
#include <numeric>
#include <boost/shared_ptr.hpp>
#include "Sdisp96Model.h"

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class calculates the misfit between observed surface wave dispersion data and the data calculated from a seismic model
    class SurfaceWaveObjective: public PlottableObjective
      {
    private:
      //! The data that has been measured
      SurfaceWaveData MeasuredData;
      //! The synthetic data that corresponds to the current model
      SurfaceWaveData SynthData;
      //! The object used to calculate the synthetic data
      SurfaceWaveSynthetic Synthetic;
      //! The relative error of the measurements
      double errorlevel;
      //! Poisson's ratio Vp/Vs
      double poisson;
    public:
      //! Set Poisson's ratio Vp/Vs
      void SetPoisson(const double p)
        {
          poisson = p;
        }
      //! Set the relative error for each measurement
      void SetErrorLevel(const double level)
        {
          errorlevel = level;
        }
      //! We need clone and create for building an array of derived objects, see FAQ lite 20.8, the return type depends on the derived class
      virtual GeneralObjective *clone() const
        {
          return new SurfaceWaveObjective(*this);
        }
      ;
      //! Some operations cannot be done in parallel, these are done before
      virtual void PreParallel(const ttranscribed &member)
      {
        const unsigned int nfulllayers = member.size() / 2;
        Sdisp96Model Model;
        ttranscribed thickness(nfulllayers), velocity(nfulllayers);
        copy(member.begin(), member.begin() + nfulllayers, thickness.begin()); //copy values
        copy(member.begin() + nfulllayers, member.begin() + 2 * nfulllayers,
            velocity.begin());
        //The model object has been newly created above, so it is safe to use back_inserter to fill the vectors
        copy(thickness.begin(), thickness.end(), back_inserter(
            Model.SetThicknesses()));
        //Sh velocities and Sv velocities are the same
        copy(velocity.begin(), velocity.end(), back_inserter(
            Model.SetShVelocities()));
        copy(velocity.begin(), velocity.end(), back_inserter(
            Model.SetSvVelocities()));
        //We calculate density from S-Velocity
        transform(velocity.begin(), velocity.end(), back_inserter(
            Model.SetDensities()), CalcDensity());
        //PVelocity is calculated by multiplication of SVel by poisson's ratio
        transform(velocity.begin(), velocity.end(), back_inserter(
            Model.SetPhVelocities()), boost::bind(multiplies<double> (), _1,
            poisson));
        copy(Model.GetPhVelocities().begin(), Model.GetPhVelocities().end(),
            back_inserter(Model.SetPvVelocities()));
        //We give some fixed values to the attenuation parameters
        fill_n(back_inserter(Model.SetEta()), nfulllayers, 1.0);
        fill_n(back_inserter(Model.SetQmu()), nfulllayers, 100.0);
        fill_n(back_inserter(Model.SetQkappa()), nfulllayers, 99999.00);

        Synthetic.SetModel(Model);
        if (Synthetic.GetCalculationPeriods().empty())
          {
            Synthetic.SetCalculationPeriods(MeasuredData.GetPeriods());
          }
        Synthetic.PreParallel(GetParallelID());
      }
      //! Some operations cannot be done in parallel, these are done after, returns the misfit value
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();

      }

      //! The core performance calculation, has to be safe to be done in parallel
      virtual void SafeParallel(const ttranscribed &member)
      {
        //We can safely calculate the synthetic data in parallel
        SynthData = Synthetic.SafeParallel(GetParallelID());
        assert(errorlevel > 1e-4);
        // an errorlevel < 0.01% is absolutely unrealistic
        const unsigned int ndata = min(SynthData.GetPhaseVelocities().size(),
            MeasuredData.GetPhaseVelocities().size());
        SetMisfit().resize(ndata); // we need vectors of the right size for misfit
        SetSynthData().resize(ndata); // and  data
        double returnvalue = 0; // init returnvalue
        // this loop calculates the misfit for each datum
        for (unsigned int i = 0; i < ndata; ++i)
          {
            returnvalue += CalcMisfit(MeasuredData.GetPhaseVelocities().at(i),
                SynthData.GetPhaseVelocities().at(i), 0.0, errorlevel, i);

          }

        SetRMS(std::pow(returnvalue / ndata, 1.0 / GetFitExponent())); //return misfit
      }
      //! Write the synthetic data to a sac file with name filename
      virtual void WriteData(const std::string &filename)
        {
          SynthData.WriteAscii(filename);
        }
      //! Write the current model to ascii file for calculations
      virtual void WriteModel(const std::string &filename)
        {
          Synthetic.GetModel().WriteModel(filename);
        }
      //! Write the current model to ascii file for plotting
      virtual void WritePlot(const std::string &filename)
        {
          Synthetic.GetModel().WritePlot(filename);
        }
      SurfaceWaveObjective& operator=(const SurfaceWaveObjective& source)
      {
        if (this == &source)
          return *this;
        PlottableObjective::operator=(source);
        MeasuredData = source.MeasuredData;
        SynthData = source.SynthData;
        Synthetic = source.Synthetic;
        errorlevel = source.errorlevel;
        poisson = source.poisson;
        return *this;
      }

      SurfaceWaveObjective(const SurfaceWaveObjective &Old):
          PlottableObjective(Old), MeasuredData(Old.MeasuredData), SynthData(
              Old.SynthData), Synthetic(Old.Synthetic)
          {
            errorlevel = Old.errorlevel;
            poisson = Old.poisson;
          }
      SurfaceWaveObjective(const SurfaceWaveData &Data):
          MeasuredData(Data)
          {
            poisson = sqrt(3.);
            errorlevel = 0.02;
          }
      virtual ~SurfaceWaveObjective();
      };
  /* @} */
  }
#endif /*SURFACEWAVEOBJECTIVE_H_*/
