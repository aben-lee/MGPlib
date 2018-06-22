#ifndef MEMBER2ANISO_H_
#define MEMBER2ANISO_H_

#include "C1DAnisoMTSynthData.h"
#include "Adaptors.h"
#include <algorithm>
namespace gplib
  {
    //! This function sets the properties for the 1D MT anisotropic forward calculation, from the variable member as used in the genetic algorithm
    void inline Member2Aniso(const ttranscribed &member,
        C1DAnisoMTSynthData &Synth)
      {
        const int nlayers = member.size() / 4; //the model has the format resistivity/thickness/anisotropy/strike
        // so the actual numer of layers is quarter the length
        trealdata rho1(nlayers, 0);
        trealdata rho2(nlayers, 0);
        trealdata zeros(nlayers, 0);
        trealdata strike(nlayers, 0);
        trealdata thick(nlayers, 0);

        transform(member.begin(), member.begin() + nlayers, rho1.begin(),
            boost::bind(gplib::fopow<double, double>(), 10., _1)); //member contains log resistivity
        // transform to normal resistivity
        copy(member.begin() + nlayers, member.begin() + 2 * nlayers,
            thick.begin()); //copy thickness values
        //anisotropy factors are stored in logarithmic form, we first copy them into rho2
        transform(member.begin() + 2 * nlayers, member.begin() + 3 * nlayers,
            rho2.begin(), boost::bind(gplib::fopow<double, double>(), 10., _1));
        //and then multiply the anisotropy factor by the resistivity rho1, to get the second resistivity
        transform(rho2.begin(), rho2.end(), rho1.begin(), rho2.begin(),
            std::multiplies<double>());
        //the strike angles are taken directly from member
        copy(member.begin() + 3 * nlayers, member.end(), strike.begin());
        Synth.SetThicknesses(thick); //set them in the MTSynth object for forward calculation
        Synth.SetRho1(rho1);
        Synth.SetRho2(rho2);
        Synth.SetRho3(rho1); //we only have horizontal anisotropy => Rho3 has no influence
        Synth.SetStrikes(strike);
        Synth.SetSlants(zeros); //we only care about strike,slant and dip are all 0
        Synth.SetDips(zeros);
      }
  }
#endif /*MEMBER2ANISO_H_*/
