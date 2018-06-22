#ifndef FILTERFUNC_H_
#define FILTERFUNC_H_

#include "types.h"
#include <complex>
#include <algorithm>
#include <iostream>
#include <iterator>
namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    /*! \file FilterFunc.h
     * This file defines several function objects to be used as filters
     *  to Filter time series data in the time domain.
     * They can be used in conjunction with Convolve.
     */

    //! Transform from frequency domain to w-domain
    double FreqToW(const double f)
      {
        std::complex<double> compexp = exp(
            std::complex<double>(0.0, 2 * PI * f));
        return -((-compexp + 1.0) / (compexp + 1.0)).imag();
      }

    //! A simple low pass

    /*! This class defines a simple IIR low pass filter as described in Numerical Recipes p. 562.
     * The filter coefficients are calculated by a bilinear transformation method. The corner frequency
     * in the constructor has to be given in terms of the Nyquist frequency, i.e. in the range \f$ 0 \ldots 0.5 \f$.
     */
    class SimpleLp: public std::unary_function<double, double>
      {
    private:
      double tsvalues[2];
      double filtervalues[3];
    public:
      //! The constructor takes the dimensionless corner frequency, i.e. the corner frequency in Hz times the sampling rate
      SimpleLp(const double cornerfreq)
        {
          // transform the corner frequency
          double b = FreqToW(cornerfreq);
          // calculate the filter coefficients
          filtervalues[0] = -b / (1.0 + b);
          filtervalues[1] = -b / (1.0 + b);
          filtervalues[2] = (1.0 - b) / (1.0 + b);
          // initialize the storage of previous input and output values
          std::fill_n(tsvalues, 2, 0.0);
        }
      //! This version of the operator is suitable for use with std::transform, it returns a filtered value for each call with the current value
      double operator()(const double currvalue)
        {
          // calculate the output and store it
          tsvalues[1] = filtervalues[0] * currvalue + filtervalues[1]
              * tsvalues[0] + filtervalues[2] * tsvalues[1];
          // store the last input
          tsvalues[0] = currvalue;
          return tsvalues[1];
        }
      };

    /*! This class defines a simple IIR band pass filter as described in Numerical Recipes p. 562.
     * The filter coefficients are calculated by a bilinear transformation method. The upper and lower corner frequencies
     * in the constructor have to be given in terms of the Nyquist frequency, i.e. in the range $\f 0 \ldots 0.5 \f$.
     */
    class SimpleBp: public std::unary_function<double, double>
      {
    private:
      double tsvalues[4];
      double filtervalues[4];
    public:
      //! The constructor takes the dimensionless corner frequencies, i.e. the corner frequencies in Hz times the sampling rate
      SimpleBp(const double lowercornerfreq, const double uppercornerfreq)
        {
          // transform the corner frequencies
          double b = FreqToW(uppercornerfreq);
          double a = FreqToW(lowercornerfreq);
          // calculate the filter coefficients
          filtervalues[0] = -b / ((1.0 + a) * (1.0 + b));
          filtervalues[1] = b / ((1.0 + a) * (1.0 + b));
          filtervalues[2] = ((1.0 + a) * (1.0 - b) + (1.0 - a) * (1.0 + b))
              / ((1.0 + a) * (1.0 + b));
          filtervalues[3] = -(1.0 - a) * (1.0 - b) / ((1.0 + a) * (1.0 + b));
          // initialize the storage of previous input and output values
          std::fill_n(tsvalues, 4, 0.0);
        }
      //! This version of the operator is suitable for use with std::transform, it returns a filtered value for each call with the current value
      double operator()(const double currvalue)
        {
          //save the output old value
          double tmp = tsvalues[2];
          // calculate the output and store it, we don't need tsvalues[0] here
          tsvalues[2] = filtervalues[0] * currvalue + filtervalues[1]
              * tsvalues[1] + filtervalues[2] * tsvalues[2] + filtervalues[3]
              * tsvalues[3];
          tsvalues[3] = tmp;
          // store the last two inputs
          tsvalues[1] = tsvalues[0];
          tsvalues[0] = currvalue;
          return tsvalues[2];
        }
      };
  }
#endif /*FILTERFUNC_H_*/
