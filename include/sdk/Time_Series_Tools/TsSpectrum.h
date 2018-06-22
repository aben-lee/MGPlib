#ifndef TSSPECTRUM_H
#define TSSPECTRUM_H

#include "FatalException.h"
#include <fftw3.h>
#include "types.h"
#include <boost/bind.hpp>
#include <algorithm>

using namespace std;

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    //! The class CTsSpectrum is used to calculate spectra from (real) time series data
    /*! CTsSpectrum is basically a wrapper for the fftw3 functionality for real data
     * it manages both the plans and the local data needed by fftw3. This class is not
     * thread-safe. DO NOT use it within an openmp parallelized loop or any kind of threaded program.
     */
    class TsSpectrum
      {
    private:
      //! FFTW3 provides facilities to speed up multiple calculations of similar data, MultiCalc determines whether we want to use this or just a simple fftw
      bool MultiCalc;
      //! If we called CalcSpectrum before this will be true, a fftw3 calculation plan exists that we might have to take care of
      bool ExistsPlanForward;
      //! If we called CalcTimeSeries before this will be true, a previous plan exists
      bool ExistsPlanReverse;
      //! What was the size of the last calculation
      int oldsize;
      //! fftw3 wants a raw C-array, one for the timedomain
      double *timedomain;
      //! the raw C-array fftw uses for the frequency domain
      fftw_complex *freqdomain;
      //! p_forward holds the plan for forward calculations
      fftw_plan p_forward;
      //! p_reverse holds the plan for reverse calculations
      fftw_plan p_reverse;
      //! A helper function that does some stuff to prepare  calculations
      void Prepare_Calculation(const int size)
      {
        if (size != oldsize) // if the size changed
          {
            AssignMem(size); //reassign memory

            if (MultiCalc) // generate a new plan
              {
                p_reverse = fftw_plan_dft_c2r_1d(size, freqdomain, timedomain,
                    FFTW_MEASURE);
                p_forward = fftw_plan_dft_r2c_1d(size, timedomain, freqdomain,
                    FFTW_MEASURE);
              }
            else
              {
                p_reverse = fftw_plan_dft_c2r_1d(size, freqdomain, timedomain,
                    FFTW_ESTIMATE);
                p_forward = fftw_plan_dft_r2c_1d(size, timedomain, freqdomain,
                    FFTW_ESTIMATE);
              }
            ExistsPlanReverse = true; // we will have to deallocate at some point
            ExistsPlanForward = true;
          }
      }
      //! finish up after time series calculations
      void Finish_Calculation(const int size)
      {
        oldsize = size; // The size of the (next) last calculation is the size of this calculation
      }

      //! We have to Assign memory for the raw c-arrays of fftw3 in the beginning and when the layout/size changes
      void AssignMem(const int size)
      {
        DestroyMem(); // destroy possible earlier instances
        timedomain = (double *) fftw_malloc(sizeof(double) * size); // reallocate with the required sizes
        freqdomain = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (size
            / 2 + 1));
      }
      //! When we reassign Memory and on exit we have to destroy the old memory structure
      void DestroyMem()
      {
        if (ExistsPlanForward || ExistsPlanReverse) // if we did some calculations before
          {
            if (ExistsPlanForward)
              fftw_destroy_plan(p_forward); // we destroy the old plans
            if (ExistsPlanReverse)
              fftw_destroy_plan(p_reverse);
            fftw_free(timedomain); // and free the memory allocated
            fftw_free(freqdomain);
            ExistsPlanForward = false; // now there is no plan anymore, so we don't double deallocate
            ExistsPlanReverse = false;
          }
      }
    public:
      //! The constructor is explicit to prohibit conversion from bool
      /*! The construtor takes an optional boolean value as an argument, that determines whether we want to use fftw's multiple calculation
       *  This makes only sense if we do a lot of calculations in the same direction and with the same length
       */
      explicit TsSpectrum(bool WantMultiCalc = false)
      {
        MultiCalc = WantMultiCalc;
        ExistsPlanForward = false;
        ExistsPlanReverse = false;
        oldsize = 0;
        timedomain = NULL;
        freqdomain = NULL;
      }
      virtual ~TsSpectrum()
      {
        DestroyMem();
      }
      //! The member function to calculate a spectrum from a time series
      /*! Takes three iterators for input: beginning of input, end of input and beginning of output
       *  Make sure the structure pointed to by freqbegin can hold at least (tsend -tsbegin)/2 +1 elements
       */
      template<typename _InputIterator, typename _OutputIterator>
      void CalcSpectrum(_InputIterator tsbegin, _InputIterator tsend,
          _OutputIterator freqbegin, _OutputIterator freqend);
      //! The member function to calculate a time series from (complex) spectra
      /*! Takes three iterators for input: beginning of input, end of input and beginning of output
       *  Make sure the structure pointed to by tsbegin can hold at least (freqend -freqbegin)*2 - 2 elements
       */
      template<typename _InputIterator, typename _OutputIterator>
      void CalcTimeSeries(_InputIterator freqbegin, _InputIterator freqend,
          _OutputIterator tsbegin, _OutputIterator tsend);
      };

    //! Calculate a spectrum from the input range given by tsbegin and tsend and write to output range given by freqbegin,freqend
    /*! Calculate the fourier transform of a real valued time series. We specify the start and the end of both structures
     * to be able to check that the output structure can hold enough elements.
     * @param tsbegin The iterator to the start of the time series segment
     * @param tsend The iterator to the end of the time series segment
     * @param freqbegin The iterator to the start of the output structure, this has to be able to hold (tsend - tsbegin)/2 + 1 values
     * @param freqend The iterator to the end of the output structure, this has to be able to hold (tsend - tsbegin)/2 + 1 values
     */
    template<typename _InputIterator, typename _OutputIterator>
    void TsSpectrum::CalcSpectrum(_InputIterator tsbegin, _InputIterator tsend,
        _OutputIterator freqbegin, _OutputIterator freqend)
      {
        const int size = distance(tsbegin, tsend); // We calculate the size of the time series
        if (size < 0) // if negative we probably swapped iterators, throw error message
          throw FatalException("Negative size of input in CalcSpectrum !");
        if (distance(freqbegin, freqend) != size / 2 + 1)
          throw FatalException(
              "Time Series and Spectrum have incompatible size !");
        Prepare_Calculation(size); // Do the necessary preparations for Spectra calculations
        copy(tsbegin, tsend, timedomain); //copy data to ftw3 data structure
        fftw_execute(p_forward); // do the calculation
        for (int i = 0; i < size / 2 + 1; ++i, ++freqbegin)
          //copy back, considering the different layout
          *freqbegin = freqdomain[i][0] + I * freqdomain[i][1];
        Finish_Calculation(size); // finish up
      }
    //! Calculate a times series from the input range given by freqbegin and freqend and write to output range given by tsbegin,tsend
    /*! Calculate the inverse fourier transfrom from a given complex array/vector. We specify the start and the end of both structures
     * to be able to check that the output structure can hold enough elements.
     * @param freqbegin The iterator to the start of the structure holding the spectral elements
     * @param freqend The iterator to the end of the structure holding the spectral elements
     * @param tsbegin The iterator to the start of the output time series structure
     * @param tsend The iterator to the end of the output time series structure
     */
    template<typename _InputIterator, typename _OutputIterator>
    void TsSpectrum::CalcTimeSeries(_InputIterator freqbegin,
        _InputIterator freqend, _OutputIterator tsbegin, _OutputIterator tsend)
      {
        if (freqbegin > freqend || tsbegin > tsend) // if beginning after end, there is something wrong, throw error
          throw FatalException("Negative size of input in CalcTimeSeries !");
        const int size = distance(tsbegin, tsend); // the logical size for fftw3 is the length of the time series, for us too
        if (distance(freqbegin, freqend) != size / 2 + 1)
          throw FatalException(
              "Time Series and Spectrum have incompatible size !");
        Prepare_Calculation(size); // prepare stuff for calculation
        for (int i = 0; freqbegin != freqend; ++freqbegin, ++i) // copy frequency data into fftw3 c-array
          {
            freqdomain[i][0] = (*freqbegin).real();
            freqdomain[i][1] = (*freqbegin).imag();
          }
        fftw_execute(p_reverse); // do calculation
        double factor = 1. / double(size); // we have to normalize, so that back-and forward transformation yields the same result
        //copy to output and multiply each element by factor
        std::transform(timedomain, timedomain + size, tsbegin, boost::bind<
            double>(std::multiplies<double>(), factor, _1));
        Finish_Calculation(size); // finish up
      }
  /* @} */
  }
#endif // CTSSPECTRUM_H
