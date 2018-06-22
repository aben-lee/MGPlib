#ifndef ANISO1DMTOBJECTIVE_H_
#define ANISO1DMTOBJECTIVE_H_
#include "C1DMTObjective.h"
#include "C1DAnisoMTSynthData.h"
#include "Member2Aniso.h"

namespace gplib
  {
    class Aniso1DMTObjective: public C1DMTObjective
      {
    private:
      virtual void CalcSynthData(const ttranscribed &member)
        {
          Member2Aniso(member, AnisoMTSynth); //setup forward model with parameter given in member
          AnisoMTSynth.GetData(); //do forward calculation
        }
      C1DAnisoMTSynthData AnisoMTSynth;
      virtual MTStation &GetMTSynth()
        {
          return AnisoMTSynth;
        }
    public:
      Aniso1DMTObjective& operator=(const Aniso1DMTObjective& source) {
          if (this == &source)
            return *this;
          C1DMTObjective::operator=(source);
          AnisoMTSynth = source.AnisoMTSynth;
          return *this;
        }

      Aniso1DMTObjective(const Aniso1DMTObjective &Old) :
          C1DMTObjective(Old), AnisoMTSynth(Old.AnisoMTSynth)
          {

          }
      explicit Aniso1DMTObjective(const MTStation &LocalMTData) :
          C1DMTObjective(LocalMTData)
          {
          }

      virtual ~Aniso1DMTObjective();
      virtual Aniso1DMTObjective *clone() const
        {
          return new Aniso1DMTObjective(*this);
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
      };
  }
#endif /*ANISO1DMTOBJECTIVE_H_*/
