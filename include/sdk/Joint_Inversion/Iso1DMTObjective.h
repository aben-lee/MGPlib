#ifndef ISO1DMTOBJECTIVE_H_
#define ISO1DMTOBJECTIVE_H_
#include "C1DMTObjective.h"
#include "C1DMTSynthData.h"
#include "Adaptors.h"

namespace gplib
  {
    //! This class implements the forward calculation for a 1D isotropic MT model
    /*! Here we implement the specific calls to generate data for a 1D isotropic
     * model, the misfit and the type of data to fit are all set and calculated
     * in the base class C1DMTObjective
     */
    class Iso1DMTObjective: public C1DMTObjective
      {
    private:
      //! This is the only function that implements some real functionality
      /*! This function implements the forward calculation of the data,
       * the base class uses the access function GetMTSynth to access this data
       * for misfit calculations etc.
       */
      virtual void CalcSynthData(const ttranscribed &member)
        {
          const int nlayers = member.size() / 2; //the model has the format resistivity/thickness
          // so the actual numer of layers is half the length
          trealdata res(nlayers, 0);
          trealdata thick(nlayers, 0);
          transform(member.begin(), member.begin() + nlayers, res.begin(),
              boost::bind(gplib::fopow<double, double>(), 10., _1)); //member contains log resistivity
          // transform to normal resistivity
          copy(member.begin() + nlayers, member.end(), thick.begin()); //copy thickness values
          IsoMTSynth.SetThicknesses(thick); //set them in the MTSynth object for forward calculation
          IsoMTSynth.SetResistivities(res);
          IsoMTSynth.CalcSynthetic(); // do forward calculation
        }
      C1DMTSynthData IsoMTSynth;
      virtual MTStation &GetMTSynth()
        {
          return IsoMTSynth;
        }
    public:
      explicit Iso1DMTObjective(const MTStation &LocalMTData):
          C1DMTObjective(LocalMTData)
          {
          }
      Iso1DMTObjective& operator=(const Iso1DMTObjective& source)
      {
        if (this == &source)
          return *this;
        C1DMTObjective::operator=(source);
        IsoMTSynth = source.IsoMTSynth;
        return *this;
      }
      Iso1DMTObjective(const Iso1DMTObjective &Old) :
          C1DMTObjective(Old), IsoMTSynth(Old.IsoMTSynth)
          {

          }
      virtual ~Iso1DMTObjective();
      //! clone clones the current object, derived from GeneralObjective
      virtual Iso1DMTObjective *clone() const
        {
          return new Iso1DMTObjective(*this);
        }
      //! write the current model to a file
      virtual void WriteModel(const std::string &filename)
        {
          IsoMTSynth.WriteModel(filename);
        }
      //! write the current model for plotting to a file
      virtual void WritePlot(const std::string &filename)
        {
          IsoMTSynth.WritePlot(filename);
        }
      //! Write current data to a file
      virtual void WriteData(const std::string &filename)
        {
          IsoMTSynth.WriteAsMtt(filename);
        }
      };
  }
#endif /*ISO1DMTOBJECTIVE_H_*/
