#ifndef CSTACKEDSPECTRUM_H
#define CSTACKEDSPECTRUM_H
#include "TsSpectrum.h"
#include "FatalException.h"
#include <functional>
#include <iterator>
#include "statutils.h"
#include <boost/bind.hpp>

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    //! This template is used to calculate stacked spectra for example for power spectrum estimation
    /*! The template StackedSpectrum calculates stacked spectra from an input time series. Two input iterators
     * define the input range, one output iterator the start of the output range, we have to provide the length
     * of individual segments and a windowing function. Make sure the container the output is stored in can hold at least seglength/2+1.
     * The Windowing function gets the relative position within the segment and should therefore be defined on the interval 0..1
     */
    template<typename InputIterator, typename OutputIterator,
        typename WindowFunctype>
    void StackedSpectrum(InputIterator tsbegin, InputIterator tsend,
        OutputIterator freqbegin, const size_t seglength, WindowFunctype WFunc)
      {
        //some convenience type definitions for the vectors that hold the input and output values
        typedef std::vector<
            typename std::iterator_traits<OutputIterator>::value_type>
            toutvector;
        typedef std::vector<
            typename std::iterator_traits<InputIterator>::value_type> tinvector;
        const size_t insize = distance(tsbegin, tsend);
        if (insize < seglength)
          throw FatalException(
              "Time Series shorter than requested segment length");
        const unsigned int nsegments = insize / seglength; //we do integer division, so the last (not full) segment will be discarded
        TsSpectrum SpecEst(false); //we do not want to perform multiple calculations
        std::fill_n(freqbegin, seglength / 2 + 1,
            typename std::iterator_traits<OutputIterator>::value_type()); // fill output with 0
        toutvector segspec(seglength / 2 + 1); //the spectrum of the current segment

        InputIterator currstart = tsbegin; //the start of the current segment
        InputIterator currend = tsbegin;
        advance(currend, seglength);
        for (unsigned int i = 0; i < nsegments; ++i)
          {
            tinvector currseg(currstart, currend); //temporary copy of time series

            SubMean(currseg.begin(), currseg.end());

            for (typename tinvector::iterator it = currseg.begin(); it
                != currseg.end(); ++it)
              {
                //multiply the current segment with the windowing function
                *it *= WFunc(
                    static_cast<double> (distance(currseg.begin(), it))
                        / seglength); //by passing the relative position to the windowing function
              }

            //calculate the fourier transform for the current segment
            SpecEst.CalcSpectrum(currseg.begin(), currseg.end(),
                segspec.begin(), segspec.end());
            //add the spectral values to the output vector
            std::transform(segspec.begin(), segspec.end(), freqbegin,
                freqbegin, std::plus<typename std::iterator_traits<
                    OutputIterator>::value_type>());
            advance(currstart, seglength); //shift the boundaries of current segment
            advance(currend, seglength);
          }
      }
  /* @} */
  }
#endif // CSTACKEDSPECTRUM_H
