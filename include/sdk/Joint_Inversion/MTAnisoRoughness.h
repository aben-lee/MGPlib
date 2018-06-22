#ifndef MANISOTROUGHNESS_H_
#define MANISOTROUGHNESS_H_
#include "GeneralObjective.h"
#include <cmath>
namespace gplib
  {
    //! Caclulate the roughness for anisotropic MT models
    class MTAnisoRoughness: public GeneralObjective
      {
    private:
      double conddiffweight;
      double anisotropyweight;
      double strikediffweight;
    public:
//! Get read-only access to the vector of anisotropy coefficients for each layer
      void SetCondDiffWeight(const double w)
        {
          conddiffweight = w;
        }
      void SetAnisotropyWeight(const double w)
       {
         anisotropyweight = w;
        }
      void SetStrikeDiffWeight(const double w)
        {
          strikediffweight = w;
        }
      virtual MTAnisoRoughness *clone() const
        {
          return new MTAnisoRoughness(*this);
        }
      virtual void SafeParallel(const ttranscribed &member)
      {
        const unsigned int length = member.size() / 4; //we have 4 parameters in the model, so size/4 layers
        double roughness = std::abs(member(2 * length)); // the loop starts at 1, so we skip this value in the 2nd summation
        const int fitexp = GetFitExponent();
        const double anglescale = 90.; //value if phi varies from 0 to 180
        for (unsigned int i = 1; i < length; ++i) // for all layers except the top
          {
            roughness += conddiffweight * std::pow((member(i) - member(i - 1)),
                fitexp); //minimize difference in conductivity between layers
            roughness += anisotropyweight * std::pow(std::abs(member(i + 2
                * length)), fitexp); //minimize anisotropy factor in each layer
            roughness += strikediffweight * std::pow((member(i + 3 * length))
                / anglescale, fitexp); //minimize strike within each layer
          }
        SetRMS(std::pow(roughness, 1. / fitexp));
      }
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      MTAnisoRoughness(const MTAnisoRoughness &Old):
          GeneralObjective(Old), conddiffweight(Old.conddiffweight),
              anisotropyweight(Old.anisotropyweight), strikediffweight(
                  Old.strikediffweight)
          {
          }
      MTAnisoRoughness& operator=(const MTAnisoRoughness& source)
      {
        if (this == &source)
          return *this;
        GeneralObjective::operator=(source);
        conddiffweight = source.conddiffweight;
        anisotropyweight = source.anisotropyweight;
        strikediffweight = source.strikediffweight;
        return *this;
      }
      MTAnisoRoughness():
          conddiffweight(), anisotropyweight(), strikediffweight()
          {
          }

      virtual ~MTAnisoRoughness();
      };
  }
#endif /*MTANISOROUGHNESS_H_*/
