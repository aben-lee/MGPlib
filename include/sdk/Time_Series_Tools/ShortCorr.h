#ifndef SHORTCORR_H_
#define SHORTCORR_H_
#include "FatalException.h"
#include "statutils.h"
#include <algorithm>
#include <numeric>

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    //! Calculate the correlation between a short time series and a master time series
    /*! The short time series will be shifted along the master and the corresponding correlation will be stored in
     * the structure referenced by outpebegin, make sure that structure can hold enough data*/
    template<typename _InputIterator, typename _OutputIterator>
    void ShortCorr(_InputIterator masterbegin, _InputIterator masterend,
        _InputIterator shortbegin, _InputIterator shortend,
        _OutputIterator outbegin)
      {
        //check the length of both time series, the "short" time series has to be shorter than the master
        if (distance(shortbegin, shortend) > distance(masterbegin, masterend))
          throw FatalException("Short time series longer than master !");

        typedef std::vector<
            typename std::iterator_traits<_InputIterator>::value_type>
            tinvector;
        _InputIterator currstart = masterbegin;
        _OutputIterator currout = outbegin;
        const int shortsize = distance(shortbegin, shortend);

        // create a local copy of the short time series, so we can do some manipulation
        tinvector shortts(shortbegin, shortend);
        SubMean(shortts.begin(), shortts.end());
        //calculate the zero lag autocorrelation of the short time series
        tinvector shortauto(shortts.begin(), shortts.end());
        std::transform(shortauto.begin(), shortauto.end(), shortauto.begin(),
            shortauto.begin(), std::multiplies<double>());
        const double shortpower = std::accumulate(shortauto.begin(),
            shortauto.end(),
            typename std::iterator_traits<_OutputIterator>::value_type());
        // go through the time series and calculate the correlation
        while (currstart + shortsize < masterend)
          {
            tinvector currmul(currstart, currstart + shortsize);

            SubMean(currmul.begin(), currmul.end());
            tinvector currauto(currmul.begin(), currmul.end());
            std::transform(currauto.begin(), currauto.end(), currauto.begin(),
                currauto.begin(), std::multiplies<double>());
            double currpower = std::accumulate(currauto.begin(),
                currauto.end(),
                typename std::iterator_traits<_OutputIterator>::value_type());

            std::transform(currmul.begin(), currmul.end(), shortts.begin(),
                currmul.begin(), std::multiplies<double>());
            *currout = std::accumulate(currmul.begin(), currmul.end(),
                typename std::iterator_traits<_OutputIterator>::value_type());
            *currout /= sqrt(shortpower * currpower);
            ++currout;
            ++currstart;
          }
      }
  /* @} */
  }
#endif /*SHORTCORR_H_*/
