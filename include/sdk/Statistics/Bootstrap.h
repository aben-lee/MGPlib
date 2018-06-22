#ifndef CBOOTSTRAP_H_
#define CBOOTSTRAP_H_
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <ctime>
#include "StatErrEst.h"
#include "statutils.h"

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    //! Implementation of the Bootstrap error estimation method
    template<class SampleGenerator>
    class Bootstrap: public StatErrEst<SampleGenerator>
      {
    private:
      //! The place of the actual implementation
      virtual void CalcErrors_Imp(double &TheMean, double &TheVar);
    public:
      //! The constructor passes everything to the base
      Bootstrap(const int nrea, SampleGenerator TheGenerator) :
        StatErrEst<SampleGenerator>::StatErrEst(nrea, TheGenerator)
        {
        }
      virtual ~Bootstrap()
        {
        }
      };
    /* @} */

    template<class SampleGenerator>
    void Bootstrap<SampleGenerator>::CalcErrors_Imp(double &TheMean,
        double &TheVar)
      {
        //first check whether the procedure is trivial
        if (this->nrealizations < 2)
          {
            TheMean = Mean(this->Samples.begin(), this->Samples.end()); //we have at most one, but maybe no values
            TheVar = 0;
            return;
          }
        std::vector<double> Pseudo;
        Pseudo.reserve(this->nrealizations);
        std::vector<double> BootSample(this->nrealizations);
        boost::lagged_fibonacci607 generator(
            static_cast<unsigned int> (std::time(0))); //we have to create random subsamples
        boost::uniform_int<> int_dist(0, this->nrealizations - 1); //so we need random numbers between 0 and size-1
        boost::variate_generator<boost::lagged_fibonacci607&,
            boost::uniform_int<> > randomindex(generator, int_dist); //this object generates them
        for (int i = 0; i < this->nrealizations; ++i) //for the required number of realizations
          {
            for (int j = 0; j < this->nrealizations; j++) //create a new subsample with replacement of the same size
              {
                BootSample.at(j) = this->Samples.at(randomindex()); //by copying random elements into the sample
              }
            Pseudo.push_back(Variance(BootSample.begin(), BootSample.end())); //calculate the variance of the current subsample
          }
        TheMean = Mean(Pseudo.begin(), Pseudo.end()); //Calculate the statistics of the Pseudo Values
        TheVar = Variance(Pseudo.begin(), Pseudo.end(), TheMean);
      }
  }
#endif /*CBOOTSTRAP_H_*/
