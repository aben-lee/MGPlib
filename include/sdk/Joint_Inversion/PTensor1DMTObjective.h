#ifndef PTENSOR1DMTOBJECTIVE_H_
#define PTENSOR1DMTOBJECTIVE_H_

#include "C1DAnisoMTSynthData.h"
#include "PTensorMTStation.h"
#include "PlottableObjective.h"
#include "Member2Aniso.h"
#include <cassert>
#include <numeric>

namespace gplib
  {
    //! This is a special objective function to fit phase tensor MT data
    /*! We don't have analytical expression for the error of phase tensor elements yet/
     * Recalculating them all the time with Jacknife or bootstrap methods is too expensive
     * so we calculate them once for the measured data, store it in a special file
     * and use this objective function to read the file and fit this data.
     */
    class PTensor1DMTObjective: public PlottableObjective
      {
    private:
      double errorlevel;
      PTensorMTStation MeasuredData;
      C1DAnisoMTSynthData AnisoMTSynth;
    public:
      //! Set the minimum relative error
      void SetErrorLevel(const double e)
        {
          errorlevel = e;
        }
      //! Calc misfit for a model given by member
      virtual void SafeParallel(const ttranscribed &member)
      {
        if (AnisoMTSynth.GetFrequencies().empty()) //if we didn't set the frequencies before
          {
            AnisoMTSynth.SetFrequencies(MeasuredData.GetFrequencies());
          }
        Member2Aniso(member, AnisoMTSynth);
        AnisoMTSynth.GetData();

        double returnvalue = 0; // init misfit value

        const unsigned int nelements = 4;
        const unsigned int ndata = nelements * MeasuredData.GetTensor().size(); //we fit 4 real phase tensor elements
        SetMisfit().resize(ndata); //make sure Misfit in base class can hold enough elements
        SetSynthData().resize(ndata); // and same for data

        for (unsigned int i = 0; i < ndata; i += nelements) //we do the 4 elements in one block
          {
            returnvalue += CalcMisfit(
                MeasuredData.at(i / nelements).GetPhi11(), AnisoMTSynth.at(i
                    / nelements).GetPhi11(),
                MeasuredData.at(i / nelements).GetdPhi11(), errorlevel, i);
            returnvalue += CalcMisfit(
                MeasuredData.at(i / nelements).GetPhi12(), AnisoMTSynth.at(i
                    / nelements).GetPhi12(),
                MeasuredData.at(i / nelements).GetdPhi12(), errorlevel, i + 1);
            returnvalue += CalcMisfit(
                MeasuredData.at(i / nelements).GetPhi21(), AnisoMTSynth.at(i
                    / nelements).GetPhi21(),
                MeasuredData.at(i / nelements).GetdPhi21(), errorlevel, i + 2);
            returnvalue += CalcMisfit(
                MeasuredData.at(i / nelements).GetPhi22(), AnisoMTSynth.at(i
                    / nelements).GetPhi22(),
                MeasuredData.at(i / nelements).GetdPhi22(), errorlevel, i + 3);
          }
        SetRMS(std::pow(returnvalue / ndata, 1.0 / GetFitExponent()));
      }
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      //! write the current model to a file
      virtual void WriteModel(const std::string &filename)
        {
          AnisoMTSynth.WriteModel(filename);
        }
      //! write the current model for plotting to a file
      virtual void WritePlot(const std::string &filename)
        {
          AnisoMTSynth.WritePlot(filename);
        }
      //! Write current data to a file
      virtual void WriteData(const std::string &filename)
        {
          AnisoMTSynth.WriteAsMtt(filename);
        }
      virtual PTensor1DMTObjective *clone() const
        {
          return new PTensor1DMTObjective(*this);
        }
      PTensor1DMTObjective(const PTensorMTStation &LocalMTData);
      PTensor1DMTObjective(const PTensor1DMTObjective &Old) :
          PlottableObjective(Old), errorlevel(Old.errorlevel), MeasuredData(
              Old.MeasuredData), AnisoMTSynth(Old.AnisoMTSynth)
          {
          }
      virtual ~PTensor1DMTObjective();
      PTensor1DMTObjective& operator=(const PTensor1DMTObjective& source)
      {
        if (this == &source)
          return *this;
        PlottableObjective::operator=(source);
        errorlevel = source.errorlevel;
        MeasuredData = source.MeasuredData;
        AnisoMTSynth = source.AnisoMTSynth;
        return *this;
      }
      };
  }
#endif /*PTENSOR1DMTOBJECTIVE_H_*/
