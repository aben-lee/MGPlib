#ifndef CJACKNIFE_H_
#define CJACKNIFE_H_
#include <numeric>
#include "StatErrEst.h"
#include "statutils.h"

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    //! Implements the Jacknifing method of error estimation
    /*! This class implements the Jacknifing mehtod for error estimation,
     * at this point the implementation is purely geared towards simple mean
     * and variance calculation and not easily extensible, should be changed in
     * the future
     */
    template<class SampleGenerator>
    class Jacknife: public StatErrEst<SampleGenerator>
      {
    private:
      //! The implementation of the Jacknife
      virtual void CalcErrors_Imp(double &m, double &v);
    public:
      //! The constructor just passes all its arguments to the base class
      Jacknife(const int nrea, SampleGenerator TheGenerator) :
        StatErrEst<SampleGenerator>(nrea, TheGenerator)
        {
        }
      virtual ~Jacknife()
        {
        }
      };
    /* @} */

    //! The implementation of the Jacknife, has to be in the header file, as it is a template class
    template<class SampleGenerator>
    void Jacknife<SampleGenerator>::CalcErrors_Imp(double &m, double &v)
      {
        m = Mean(this->Samples.begin(), this->Samples.end()); //Calculate the mean
        if (this->nrealizations < 2) // check for values, that can cause overflow of variance calculation
          {
            v = 0;
            return;
          }
        v = Variance(this->Samples.begin(), this->Samples.end(), m); //calculate the variance with the given mean
      }
  }
#endif /*CJACKNIFE_H_*/
