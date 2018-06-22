#ifndef LSSOFILTER_H_
#define LSSOFILTER_H_

#include "AdaptiveFilter.h"
#include <iostream>

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    //! Base class for least squares filter with a single output value
    /*!*****************************************************
     * Base class for Least-Square filters with a single output value
     * currently used for LMS and RLS filters, implements all virtual
     * functions from AdaptiveFilters apart from AdaptFilter, which
     * depends on the functionality of the individual filter
     *
     *
     * *****************************************************/
    class LSSOFilter: public AdaptiveFilter
      {
        const int maxoutputchannels = 1;
    private:
      //! For single output values the weights can be stored in a vector
      gplib::rvec Weights;
    protected:
      gplib::rvec &SetWeights()
        {
          return Weights;
        }
    public:
      //! The way to calculate the output is the same for all single output filters, we implement it here
      virtual void CalcOutput(const gplib::rvec &Input, gplib::rvec &Output)
      {
        //for a single output value the filter output is
        //simply the inner product of the input with the filter weigths
        Output(0) = ublas::prec_inner_prod(Input, Weights);
        SetOutput(Output);
      }
      //! For single channel output we can also just return the output as a double
      double CalcOutput(const gplib::rvec &Input)
        {
          gplib::rvec temp;
          CalcOutput(Input, temp);
          return temp(0);
        }
      //! Return the current set of weights
      const gplib::rvec &GetWeights()
        {
          return Weights;
        }
      //! Implement the abstract function from adaptive filter, in this case just another name for GetWeights
      virtual const gplib::rvec &GetWeightsAsVector()
        {
          return Weights;
        }
      //! Print the weights to output stream
      virtual void PrintWeights(std::ostream &output)
      {
        //print all filter weights to a single line
        std::copy(Weights.begin(), Weights.end(),
            std::ostream_iterator<double>(output, " "));
        output << std::endl;
      }

      //! The constructor only needs the filter length, outputsize for Adaptive filter is 1
      LSSOFilter(const int filterlength):
          AdaptiveFilter(filterlength, maxoutputchannels), Weights(filterlength)
          {
            //set all weights to zero
            Weights.clear();
          }
      virtual ~LSSOFilter();
      //! We declare friend classes for easier access to the Weight vector
      };
  /* @} */
  }
#endif /*CLSSOFILTER_H_*/
