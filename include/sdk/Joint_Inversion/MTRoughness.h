#ifndef MTROUGHNESS_H_
#define MTROUGHNESS_H_
#include "GeneralObjective.h"
namespace gplib
  {
//! Calculate the roughness for the MT part of a joint MT-seismic model as used by 1dinvga
class MTRoughness: public GeneralObjective
{
public:
	virtual MTRoughness *clone() const {return new MTRoughness(*this);}
        virtual void SafeParallel(const ttranscribed &member)
    {
      const unsigned int length = member.size() / 3; //we have 3 parameters in the model, so size/3 layers
      double roughness = 0; // init returnvalue
      const int fitexp = GetFitExponent();

      for (unsigned int i = 1; i < length; ++i) // for all layers except the top
        {
          roughness += std::pow((member(i) - member(i - 1)), fitexp); // add the squared difference of the values divided by reference
        }
      SetRMS(roughness);
    }
        virtual double PostParallel(const ttranscribed &member)
    {
      return GetRMS();
    }
        MTRoughness(const MTRoughness &Old):
            GeneralObjective(Old)
            {

            }

        MTRoughness& operator=(const MTRoughness& source)
        {
          if (this == &source)
            return *this;
          GeneralObjective::operator=(source);
          return *this;
        }
	MTRoughness();
	virtual ~MTRoughness();
};
  }
#endif /*MTROUGHNESS_H_*/
