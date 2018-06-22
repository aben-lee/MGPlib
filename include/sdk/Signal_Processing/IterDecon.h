#ifndef ITERDECON_H_
#define ITERDECON_H_
#include "AdaptiveFilter.h"
#include "TsSpectrum.h"
#include "miscfunc.h"
#include <boost/algorithm/minmax_element.hpp>
#include <iostream>
#include <cmath>

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    //! The iterative deconvolution algorithm, mainly used for receiver function computation
    /*! Implements iterative deconvolution used for receiver function calculations
     * but it is basically just another adaptive filter
     */
    class IterDecon: public AdaptiveFilter
      {
    private:
      //! The weights are in toeplitz matrix form, so we can store them in a vector
      gplib::rvec Weights;
      TsSpectrum &Spectrum;
    public:
      //! return the Weights as a vector, in this case the same as GetWeights
      virtual const gplib::rvec &GetWeightsAsVector()
        {
          return Weights;
        }
      //! return the Weights
      const gplib::rvec &GetWeights()
        {
          return Weights;
        }
      //! print weights to a file
      virtual void PrintWeights(std::ostream &output)
      {
        std::copy(Weights.begin(), Weights.end(),
            std::ostream_iterator<double>(output, "\n"));
      }
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        typedef gplib::rvec::const_iterator iterator;
        gplib::rvec Corr(Desired.size());
        Correl(Desired, Input, Corr, Spectrum); //calculate the correlation between desired and input
        const double power = ublas::prec_inner_prod(Input, Input);
        std::pair<iterator, iterator> MinMaxPos(boost::minmax_element(
            Corr.begin(), Corr.begin() + Corr.size() / 2)); //find minimum and maximum
        int MaxIndex = MinMaxPos.second - Corr.begin(); //index of maximum
        int MinIndex = MinMaxPos.first - Corr.begin(); //index of minimum

        if (std::abs(*MinMaxPos.second) > std::abs(*MinMaxPos.first)) //if max has higher absolute value than min
          Weights(MaxIndex) += *MinMaxPos.second / power; //update weight for max
        else
          Weights(MinIndex) += *MinMaxPos.first / power; //update weight for min
      }
      virtual void CalcOutput(const gplib::rvec &Input, gplib::rvec &Output)
      {
        Convolve(Input, Weights, Output, Spectrum);//multiplication with a toeplitz matrix is the same as cyclic convolution
        SetOutput(Output);
      }
      //! Input and output length have to be the same, so only one parameter for the constructor
      IterDecon(const int inputsize, TsSpectrum &Spec) :
          AdaptiveFilter(inputsize, inputsize), Weights(inputsize), Spectrum(Spec)
          {
            for (int i = 0; i < inputsize; ++i)
              Weights(i) = 0;
          }
      virtual ~IterDecon();
      };
  /* @} */
  }
#endif /*ITERDECON_H_*/
