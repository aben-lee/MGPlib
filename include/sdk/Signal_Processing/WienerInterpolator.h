#ifndef WIENERINTERPOLATOR_H_
#define WIENERINTERPOLATOR_H_
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "LSSOFilter.h"
#include <iostream>
#include <iterator>
#include <algorithm>

namespace gplib
  {

    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    /*!*********************************************
     * WienerInterpolator implements a linear prediction filter
     * as described in Numerical Recipes, p. 566 , it uses the autocorrelation
     * structure of the input data to predict the next sample
     * Although it  does not work exactly like the adaptive filters it is part of
     * the class hierachy for now. The prediction coefficients are stored as Weights, but
     * in opposite order to NR memcof, so they can be immediately used for prediction
     */

    class WienerInterpolator: public LSSOFilter
      {
    private:
      //! The prediction error within the window used to calculate the filter coefficients
      double xms;
    public:
      //! Return the prediction error
      double GetXms() const
        {
          return xms;
        }
      //! Calculate the prediction coefficients, the contents of Desired are ignored, this function has to be implemented in the filter class hieraychy
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        const int size = Input.size();
        const int filterlength = GetWeights().size();
        gplib::rvec wk1(size);
        gplib::rvec wk2(size);
        gplib::rvec wkm(filterlength);
        double power = inner_prod(Input, Input);
        xms = power / size;
        std::fill_n(wkm.begin(), filterlength, 0.0);

        wk1(0) = Input(0);
        wk2(size - 2) = Input(size - 1);
        for (int i = 1; i < size - 1; ++i)
          {
            wk1(i) = Input(i);
            wk2(i - 1) = Input(i);
          }
        for (int j = 0; j < filterlength; ++j)
          {
            double num = 0.0;
            double denom = 0.0;
            for (int k = 0; k < (size - j - 1); ++k)
              {
                num += wk1(k) * wk2(k);
                denom += wk1(k) * wk1(k) + wk2(k) * wk2(k);
              }
            SetWeights()(j) = 2.0 * num / denom;
            xms *= (1.0 - GetWeights()(j) * GetWeights()(j));
            for (int k = 0; k < j; ++k)
              {
                SetWeights()(k) = wkm(k) - GetWeights()(j) * wkm(j - k - 1);
              }
            if (j == filterlength - 1)
              {
                reverse(SetWeights().begin(), SetWeights().end());
                return;
              }
            for (int k = 0; k <= j; ++k)
              wkm(k) = GetWeights()(k);
            for (int k = 0; k < size - j - 2; ++k)
              {
                wk1(k) -= wkm(j) * wk2(k);
                wk2(k) = wk2(k + 1) - wkm(j) * wk1(k + 1);
              }
          }
      }
      //! A more convenient method to get the prediction coefficients, but unique to this class
      gplib::rvec CalcCoefficients(const gplib::rvec &Input)
        {
          AdaptFilter(Input, Input);
          return GetWeights();
        }
      //! The constructor needs to know the filterlength
      WienerInterpolator(const int filterlength) :
          LSSOFilter(filterlength), xms(0.0)
          {
          }
      virtual ~WienerInterpolator();
      };
  /* @} */
  }
#endif /*WIENERINTERPOLATOR_H_*/
