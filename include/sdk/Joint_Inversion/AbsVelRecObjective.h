#ifndef ABSVELRECOBJECTIVE_H_
#define ABSVELRECOBJECTIVE_H_

#include "C1DRecObjective.h"
#include "RFVelCalc.h"
#include "SurfaceWaveData.h"

namespace gplib
  {
    //! This objective function calculates the weighted misfit for a receiver function and the corresponding absolute velocity transformation
    class AbsVelRecObjective: public C1DRecObjective
      {
    private:
      //! The object to perform absolute velocity estimation
      RFVelCalc CalcAbsVel;
      SurfaceWaveData MeasuredAbsVel;
      SurfaceWaveData SynthAbsVel;
      double absvelweight;
      double recweight;
    public:
      //! return a pointer to a copy of the current object
      virtual AbsVelRecObjective *clone() const
        {
          return new AbsVelRecObjective(*this);
        }
      //! Set the relative weight for the absolute velocity information
      void SetAbsVelWeight(const double w)
        {
          absvelweight = w;
        }
      //! Set the relative weight for the pure receiver function
      void SetRecWeight(const double w)
        {
          recweight = w;
        }
      //! Write out the receiver function and absolute velocity data, the absolute velocity data gets .vel appended
      virtual void WriteData(const std::string &filename)
        {
          if (recweight > 0.0)
            C1DRecObjective::WriteData(filename);
          if (absvelweight > 0.0)
            SynthAbsVel.WriteAscii(filename + ".vel");
        }
      virtual double PostParallel(const ttranscribed &member)
      {
        //call inherited version to calculate receiver function misfit
        C1DRecObjective::PostParallel(member);
        // calculate raw misfit from RMS
        double returnvalue = std::pow(GetRMS(), GetFitExponent())
            * GetMisfit().size();
        // and multiply by weight
        returnvalue *= recweight;
        //if we include absolute velocity information and have data
        if (absvelweight > 0.0 && !MeasuredAbsVel.GetPhaseVelocities().empty())
          {
            //calculate synthetic absolute velocity data
            SynthAbsVel.SetPeriods() = MeasuredAbsVel.GetPeriods();
            SeismicDataComp Rad(RecCalculator.GetRadComp()), Ver(
                RecCalculator.GetVerComp());
            CalcAbsVel.CalcRFVel(slowness, Rad, Ver,
                SynthAbsVel.SetPhaseVelocities());

            assert(SynthAbsVel.GetPhaseVelocities().size() == MeasuredAbsVel.GetPhaseVelocities().size());
            const unsigned int nvel = SynthAbsVel.GetPhaseVelocities().size();
            const unsigned int nrec = GetMisfit().size(); // the number of previous receiver function points

            //we have to copy the old misfit values from the base class
            //so we create local copties
            tmisfit LocalMisfit(nrec + nvel); // we need vectors of the right size for misfit, this is for levmarq
            tdata LocalData(nrec + nvel); // and  data, levmarq needs to know the size before, so we do not consider weights for the size
            copy(GetMisfit().begin(), GetMisfit().end(), LocalMisfit.begin());
            copy(GetSynthData().begin(), GetSynthData().end(),
                LocalData.begin());
            //after reserving the right amount of memory, we can copy back
            SetMisfit(LocalMisfit);
            SetSynthData(LocalData);

            for (unsigned int i = 0; i < nvel; ++i)
              {
                //we add up the misfit for each velocity estimate
                //we have not stored any measurement error, so we only
                //use the relative error floor, we store the misfit and data after the normal receiver function
                returnvalue += CalcMisfit(
                    MeasuredAbsVel.GetPhaseVelocities().at(i),
                    SynthAbsVel.GetPhaseVelocities().at(i), 0.0, errorlevel, i
                        + nrec);
              }

            unsigned int ndata = 0;
            double divisor = 1.0;
            if (recweight > 0) // we have to divide by the right amount of datapoints
              {
                ndata = nrec + nvel;
                divisor = nrec * recweight + nvel * absvelweight;
              }
            else
              {
                ndata = nvel;
                divisor = ndata * absvelweight;
              }
            SetRMS(std::pow(returnvalue / divisor, 1.0 / GetFitExponent())); //store new misfit in local class
          }
        return GetRMS();
      }
      AbsVelRecObjective& operator=(const AbsVelRecObjective& source)
      {
        if (this == &source)
          return *this;
        C1DRecObjective::operator=(source);
        CalcAbsVel = source.CalcAbsVel;
        MeasuredAbsVel = source.MeasuredAbsVel;
        SynthAbsVel = source.SynthAbsVel;
        recweight = source.recweight;
        absvelweight = source.absvelweight;
        return *this;
      }
      AbsVelRecObjective(const AbsVelRecObjective &Old):
          C1DRecObjective(Old), CalcAbsVel(Old.CalcAbsVel), MeasuredAbsVel(
              Old.MeasuredAbsVel), SynthAbsVel(Old.SynthAbsVel)
          {
            recweight = Old.recweight;
            absvelweight = Old.absvelweight;
          }
      virtual ~AbsVelRecObjective();
      //! This constructor is used for calculating absolute velocity information
      /*! @param TheRecData  Object containing the measured receiver function as from call RFVelCalc
       * @param AbsVel Object containing the measured absolute velocity information
       * @param myshift    the shift used for calculating the measured receiver function
       *  @param mysigma sigma used for calculating the measured receiver function
       *  @param myc water level used for calculating the measured receiver function
       *  @param myslowness slowness used for calculating the measured receiver function
       * @param normalized Is the measured data normalized to an initial correlation peak of 1
       */
      AbsVelRecObjective(boost::shared_ptr<const SeismicDataComp> TheRecData,
          SurfaceWaveData &AbsVel, const int myshift, const double mysigma,
          const double myc, const double myslowness,
          const RecCalc::trfmethod method = RecCalc::specdiv,
          const bool normalized = true):
      C1DRecObjective(TheRecData, myshift, mysigma, myc, myslowness, method,
          normalized), CalcAbsVel(mysigma, myc, method), MeasuredAbsVel(AbsVel)
      {
        recweight = 1;
        absvelweight = 1;
      }
  }
#endif /*ABSVELRECOBJECTIVE_H_*/
