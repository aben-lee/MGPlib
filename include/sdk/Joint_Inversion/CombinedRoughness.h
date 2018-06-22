#ifndef _CCOMBINEDROUGHNESS_H_
#define _CCOMBINEDROUGHNESS_H_
#include "GeneralObjective.h"
#include <iostream>

namespace gplib
  {
    //! CombinedRoughness calculates the roughness of a joint MT- receiver functions model without consideration for different parameter ranges
    class CombinedRoughness: public GeneralObjective
      {
    private:
      double refcond;
      double refvel;
    public:
      //! Clone the object
      virtual CombinedRoughness *clone() const
        {
          return new CombinedRoughness(*this);
        }
      //! Set reference conductivity for roughness calculation, changes weighting between velocity and conductivity
      void SetRefCond(const double cond)
        {
          refcond = cond;
        }
      //! Set reference velcoity for roughness calculation, changes weighting between velocity and conductivity
      void SetRefVel(const double vel)
        {
          refvel = vel;
        }
      virtual void SafeParallel(const ttranscribed &member)
      {
        const unsigned int length = member.size() / 3; //we have 3 parameters in the model, so size/3 layers
        double roughness = 0; // init returnvalue
        const int fitexp = GetFitExponent();

        for (unsigned int i = 1; i < length; ++i) // for all layers except the top
          {
            roughness += pow((member(i) - member(i - 1)) / refcond,
                fitexp); // add the squared difference of the values divided by reference
            roughness += pow((member(i + 2 * length) - member(i - 1 + 2
                * length)) / refvel, fitexp);
          }
        SetRMS(roughness);
      }
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      CombinedRoughness(const CombinedRoughness &Old) :
          GeneralObjective(Old), refcond(Old.refcond), refvel(Old.refvel)
          {
          }
      CombinedRoughness& operator=(const CombinedRoughness& source)
      {
        if (this == &source)
          return *this;
        GeneralObjective::operator=(source);
        refcond = source.refcond;
        refvel = source.refvel;
        return *this;
      }
      CombinedRoughness() :
          refcond(2.0), refvel(2.0)
          {
          }

      virtual ~CombinedRoughness();
      };
  }
#endif /*_CCOMBINEDROUGHNESS_H_*/
