#ifndef STATUTILS_H_
#define STATUTILS_H_
#include <numeric>
#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include "FatalException.h"

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    /*! /file This header contains some simple statistical routines. All all templates for widest
     * possible use */

    //! Calculate the mean for a given range
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type Mean(InputIterator begin, InputIterator end)
      {
        return std::accumulate(begin, end,
            typename std::iterator_traits<InputIterator>::value_type())
            / boost::numeric_cast<double>(distance(begin, end));
      }

    //! Calculate the Variance and give the mean as a third input parameter
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type Variance(InputIterator begin,
        InputIterator end,
        typename std::iterator_traits<InputIterator>::value_type mv)
      {
        typename std::iterator_traits<InputIterator>::value_type var = 0.0;
        for (InputIterator it = begin; it != end; ++it)
          var += (*it - mv) * (*it - mv);
        return var / boost::numeric_cast<double>(distance(begin, end) - 1);
      }

    //! Calculate the Variance for a given range when the mean is not known and has to be calculated as well
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type Variance(InputIterator begin,
        InputIterator end)
      {
        return Variance(begin, end, Mean(begin, end));
      }

    //! Calculate the Mean Error for a given input range
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type MeanErr(InputIterator begin,
        InputIterator end)
      {
        return MeanErr(begin, end, Mean(begin, end));
      }

    //! Calculate the Mean Error for a given input range when the mean is known and passed as a third parameter
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type MeanErr(InputIterator begin,
        InputIterator end,
        typename std::iterator_traits<InputIterator>::value_type mv)
      {
        return sqrt(Variance(begin, end, mv) / boost::numeric_cast<double>(
            distance(begin, end)));
      }

    //! Calculate the Standard deviation with a given mean
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type StdDev(InputIterator begin,
        InputIterator end,
        typename std::iterator_traits<InputIterator>::value_type mv)
      {
        return sqrt(Variance(begin, end, mv));
      }

    //! Calculate the Standard Deviation
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type StdDev(InputIterator begin,
        InputIterator end)
      {
        return StdDev(begin, end, Mean(begin, end));
      }

    //! Substract the mean from each element in the container, mean is passed as a parameter
    template<typename InputIterator> inline
    void SubMean(InputIterator begin, InputIterator end,
        typename std::iterator_traits<InputIterator>::value_type mean)
      {
        std::transform(begin, end, begin, boost::bind(std::minus<
            typename std::iterator_traits<InputIterator>::value_type>(), _1,
            mean));
      }

    //! Substract the mean from each element in the container, mean is calculated
    template<typename InputIterator> inline
    void SubMean(InputIterator begin, InputIterator end)
      {
        SubMean(begin, end, Mean(begin, end));
      }

    //! Calculate the median for a vector style container
    template<typename InputIterator> inline typename std::iterator_traits<
        InputIterator>::value_type Median(InputIterator begin,
        InputIterator end)
      {
        std::vector<typename std::iterator_traits<InputIterator>::value_type>
            localcopy(begin, end); // we have to create a local copy, because nth_element changes the order
        const unsigned int sortposition = localcopy.size() / 2 + 1;
        if (sortposition > localcopy.size() - 1)
          throw FatalException("Vector too small ! Median not defined !");
        nth_element(localcopy.begin(), localcopy.begin() + sortposition,
            localcopy.end());
        if ((localcopy.size() % 2) == 0)
          return ((localcopy.at(localcopy.size() / 2) + localcopy.at(
              sortposition)) / 2.);
        else
          return (localcopy.at(sortposition));
      }
  /* @} */
  }
#endif /*STATUTILS_H_*/
