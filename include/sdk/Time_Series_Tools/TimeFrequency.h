#ifndef TIMEFREQUENCY_H_
#define TIMEFREQUENCY_H_
#include <complex>
#include "TsSpectrum.h"
#include "statutils.h"
#include "VecMat.h"
#include "FatalException.h"

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    //! Calculate a sliding windowed fourier transform for a time series and store the results for each segment in a matrix
    /*! This function returns the time-frequency matrix for a real time series
     *  \param tsbegin iterator to the start of the input time series
     *  \param tsend iterator to the end of the input time series
     *  \param length of segments used for fourier transform in points, if the last segment is longer than the time-series it is discarded
     *  \param Function object for windowing the segments before fourier transform \see WFunc.h for a selection of provided function objects
     */
    template<typename InputIterator, typename WindowFunctype>
    gplib::cmat TimeFrequency(InputIterator tsbegin, InputIterator tsend,
        const size_t seglength, WindowFunctype WFunc)
      {
        const size_t insize = distance(tsbegin, tsend);
        if (insize < seglength)
          throw FatalException(
              "Time Series shorter than requested segment length");
        const unsigned int nsegments = insize / seglength; //we do integer division, so the last (not full) segment will be discarded
        const unsigned int speclength = seglength / 2 + 1;
        TsSpectrum SpecEst(false);
        gplib::cmat output(nsegments, speclength);
        typedef std::vector<
            typename std::iterator_traits<InputIterator>::value_type> tinvector;

        InputIterator currstart = tsbegin; //the start of the current segment
        InputIterator currend = tsbegin;
        advance(currend, seglength);

        std::vector<std::complex<double> > segspec(speclength);
        for (unsigned int i = 0; i < nsegments; ++i)
          {
            tinvector currseg(currstart, currend); //temporary copy of time series
            SubMean(currseg.begin(), currseg.end());
            ApplyWindow(currseg.begin(),currseg.end(),currseg.begin(),WFunc);
            SpecEst.CalcSpectrum(currseg.begin(), currseg.end(),
                segspec.begin(), segspec.end());
            copy(segspec.begin(), segspec.end(), row(output, i).begin());
            advance(currstart, seglength); //shift the boundaries of current segment
            advance(currend, seglength);
          }
        return output;
      }
  /* @} */
  }
#endif /*TIMEFREQUENCY_H_*/
