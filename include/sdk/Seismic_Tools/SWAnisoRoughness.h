#ifndef SWANISOTROUGHNESS_H_
#define SWANISOTROUGHNESS_H_
#include "GeneralObjective.h"

namespace gplib
  {
//! Calculate the roughness for anisotropic SW models
class SWAnisoRoughness: public GeneralObjective
{
private:
	double veldiffweight;
	double anisovelweight;
	double strikediffweight;
	double deltastrikediffweight;
public:
        //! Regularize the velocity change across the layers. This is zero by default
	void SetVelDiffWeight(const double w){veldiffweight =w;}
	//! Regularize the anisotropy of the velocities. This is 1 by default
	void SetAnisovelWeight(const double w){anisovelweight = w;}
	//! Regularize the difference in anisotropy strike across layers. This is zero by default
	void SetStrikeDiffWeight(const double w){strikediffweight =w;}
	//! Regularize the difference between the seismic and electric strike. This is zero by default
	void SetDeltaStrikeDiffWeight(const double w){deltastrikediffweight = w;}
	virtual SWAnisoRoughness *clone() const {return new SWAnisoRoughness(*this);}
        virtual void SafeParallel(const ttranscribed &member)
        {
          const unsigned int length = member.size() / 6; //we have 6 parameters in the model, so size/6 layers
          double roughness = std::abs(member(2 * length)); // the loop starts at 1, so we skip this value in the 2nd summation
          const int fitexp = GetFitExponent();
          const double anglescale = 90.; //value for phi from 0 to 180
          for (unsigned int i = 1; i < length; ++i) // for all layers except the top
            {
              roughness += veldiffweight * std::pow((member(i + 1 * length)
                  - member(i - 1 + 1 * length)), fitexp); //minimize difference in S velocity between layers
              roughness += anisovelweight * std::pow(std::abs(member(i + 5
                  * length)), fitexp); //minimize anisovel factor in each layer
              roughness += strikediffweight * std::pow((member(i + 2 * length))
                  / anglescale, fitexp); //minimize strike within each layer
              roughness += deltastrikediffweight * std::pow(std::abs(member(i + 3
                  * length) / 30), fitexp); //minimize deltaangle in each layer (for a range :-60/ 60)
            }
          SetRMS(std::pow(roughness, 1. / fitexp));
        }
        virtual double PostParallel(const ttranscribed &member)
        {
          return GetRMS();
        }

        SWAnisoRoughness(const SWAnisoRoughness &Old):
            GeneralObjective(Old), veldiffweight(Old.veldiffweight), anisovelweight(
                Old.anisovelweight), strikediffweight(Old.strikediffweight),
                deltastrikediffweight(Old.deltastrikediffweight)
            {

            }
        SWAnisoRoughness& operator=(const SWAnisoRoughness& source)
        {
          if (this == &source)
            return *this;
          GeneralObjective::operator=(source);
          veldiffweight = source.veldiffweight;
          anisovelweight = source.anisovelweight;
          strikediffweight = source.strikediffweight;
          deltastrikediffweight = source.deltastrikediffweight;
          return *this;
        }
        SWAnisoRoughness():
            veldiffweight(0.0), anisovelweight(1.0), strikediffweight(0.0),
                deltastrikediffweight(0.0)
            {
            }

	virtual ~SWAnisoRoughness();
};
}
#endif /*SWANISOROUGHNESS_H_*/
