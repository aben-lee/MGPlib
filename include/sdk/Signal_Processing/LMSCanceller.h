/** \addtogroup sigproc Signal processing methods */
/* @{ */

#ifndef LMSCANCELLER_H
#define LMSCANCELLER_H

#include "types.h"
#include "LSSOFilter.h"
#include "FatalException.h"
#include <iostream>
#include <iterator>
using namespace std;


namespace gplib
  {
    //! Implements a LMS adaptive filter
    /*!*********************************************
     * LMSCanceller implements the Normalized Adaptive LMS Filter
     * as described in Haykin, p. 324 , it only supports a single
     * output channel an mutliple input channels have to be concatenated
     * at the input side
     */
    class LMSCanceller: public LSSOFilter
      {
    private:
      double mu;
    public:
      void SetMu(const double Mymu)
        {
          mu = Mymu;
        }
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        if (Input.size() != GetInputLength() || Input.size() != GetWeights().size()
            || Desired.size() != GetOutputLength())
          throw FatalException("Input or Desired do not have expected size !");

        SetEpsilon(Desired - GetFilterOutput()); //Calculate the last prediction error
        double step = ublas::prec_inner_prod(Input, Input); //the power of the input data
        const double delta = 0.0001; // We introduce delta to improve stability for small values
        step = mu / (step + delta); //here see Haykin, p 323
        SetWeights() += 2.0 * step * GetEpsilon()(0) * Input; //update Filter based on prediction error
      }
      LMSCanceller(const int inputsize) :
          LSSOFilter(inputsize), mu(1)
          {
          }
      LMSCanceller(const int inputsize, const double Mymu):
          LSSOFilter(inputsize), mu(Mymu)
          {
          }
      virtual ~LMSCanceller();
      };
  /* @} */
  }
#endif // LMSCANCELLER_H
