#ifndef WFUNC_H_
#define WFUNC_H_
#include "types.h"
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <functional>

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    /*! \file WFunc.h
     *  This file defines several function objects to be used as windowing functions for spectral calculations
     * They all take one input parameter, the relative position in the time window, as a double between 0 and 1
     * and output the corresponding weighting factor. For efficiency reasons no checking is performed on the
     * input parameter. So make sure it is between 0 and 1, or you will get strange results. The easiest way
     * to apply the window function to some time series is to use the provided function ApplyWindow in this header file
     */
    //! This functor returns the weighting factor for the Hamming window, given the relative position relpos [0..1] in the time series
    struct Hamming: public std::unary_function<double, double>
      {
      double operator()(const double relpos)
        {
          return 0.54 - 0.46 * cos(2 * PI * relpos);
        }
      };
    //! This functor returns the weighting factor for the Hanning window, given the relative position (0..1) in the time series
    struct Hanning: public std::unary_function<double, double>
      {
      double operator()(const double relpos)
        {
          return 0.5 - 0.5 * cos(2 * PI * relpos);
        }
      };
    //! A functor for the simple Boxcar function
    struct Boxcar: public std::unary_function<double, double>
      {
      double operator()(const double relpos)
        {
          if (relpos >= 0.0 && relpos <= 1.0)
            return 1.0;
          else
            return 0.0;
        }
      };

    //! This functor rises steeply at the edges and then has a wide range where it is unity
    struct Steep: public std::unary_function<double, double>
      {
      double operator()(const double relpos)
        {
          const double startrange = 0.1;
          if (relpos < startrange)
            return 0.5 - 0.5 * cos(PI * relpos / startrange);
          else if (relpos > (1.0 - startrange))
            return 0.5 - 0.5 * cos(PI * ((1.0 - startrange) - relpos)
                / startrange + PI);
          else
            return 1.0;
        }
      };

    //! The cosine squared windows of fixed width
    struct CosSq: public std::unary_function<double, double>
      {
      double operator()(const double relpos)
        {
          double val = cos(PI * relpos / 2);
          return val * val;
        }
      };

    //! A variable width cosine squared window that is zero outside
    class TruncCosSq: public std::unary_function<double, double>
      {
    private:
      double width;
    public:
      TruncCosSq(double w = 1) :
        width(w)
        {
        }
      double operator()(const double relpos)
        {
          if (std::abs(relpos) > width)
            return 0.0;

          double val = cos(PI * relpos / (2 * width));
          return val * val;
        }
      };

    //! Apply one of the above window functions to a range
    /*!Apply one of the above window functions to a range
     * given by the iterators inbegin and outbegin and write the result into a structure through
     * the iterator outbegin, make sure the datastructure can hold enough elements. Input and output structures
     * can be the same.
     * */
    template<typename InputIterator, typename OutputIterator,
        typename WindowFunctype> inline
    void ApplyWindow(InputIterator inbegin, InputIterator inend,
        OutputIterator outbegin, WindowFunctype WFunc, double relshift = 0.0)
      {
        const double length = inend - inbegin;
        for (InputIterator it = inbegin; it != inend; ++it, ++outbegin)
          *outbegin = (*it) * WFunc(boost::numeric_cast<double>(std::distance(
              inbegin, it)) / length - relshift);

        //std::transform(inbegin,inend,outbegin,
        //	boost::bind(std::multiplies<typename std::iterator_traits<InputIterator>::value_type>(),_1,
        //		boost::bind(WFunc,boost::bind<double>(std::divides<typename std::iterator_traits<InputIterator>::value_type >(),_1,length))));
      }
  /* @} */
  }
#endif /*WFUNC_H_*/
