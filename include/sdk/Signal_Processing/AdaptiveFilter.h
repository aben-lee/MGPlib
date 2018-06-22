#ifndef ADAPTIVEFILTER_H
#define ADAPTIVEFILTER_H

#include "types.h"
#include "VecMat.h"

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    /*!
     * \file AdaptiveFilter.h
     * Basic class for adaptive filtering of time series data
     * \author Max Moorkamp
     * $Id: AdaptiveFilter.h 1845 2010-04-12 11:55:22Z mmoorkamp $
     *
     * The class AdaptiveFilter provides the generic interface for all types of adaptive Filters
     */

    namespace ublas = boost::numeric::ublas;
    //! A generic base class for all types of adaptive filters
    /*! The class AdaptiveFilter provides a unified interface for various types
     * of adaptive filters and storage for some quantities that are common to all
     * of them. Ideally this should facilitate transparent use of all filters in
     * any program or routine. See, for example, mtuadaptive.cpp. We assume that the filter length
     * and number of output points is constant for the life of the object.
     */
    class AdaptiveFilter
      {
    private:
      //! The vector holding the last filter output calculated
      gplib::rvec FilterOutput;
      //! The vector holding the last estimation error
      gplib::rvec Epsilon;
      //! length of the input vector to the filter, this is not the time-series length, but the segment the filter operates on
      const unsigned int inputlength;
      //! length of the filter output
      const unsigned int outputlength;
    protected:
      //! Access function for derived classes for the inputlength
      unsigned int GetInputLength()
        {
          return inputlength;
        }
      //! Access function for derived classes for the outputlength
      unsigned int GetOutputLength()
        {
          return outputlength;
        }
      //! Possibility for derived classes to set estimation error
      void SetEpsilon(const gplib::rvec &MyEps)
        {
          Epsilon = MyEps;
        }
      //! Possibility for derived classes to set output
      void SetOutput(const gplib::rvec &Out)
        {
          FilterOutput = Out;
        }
    public:
      //! Access to the last calculated output (not sure if needed)
      const gplib::rvec &GetFilterOutput() const
        {
          return FilterOutput;
        }
      //! Return the last estimation error
      const gplib::rvec &GetEpsilon() const
        {
          return Epsilon;
        }
      //! Print the current set of weights to the output stream, has to be implemented in derived class
      virtual void PrintWeights(std::ostream &output) =0;
      //! We can always convert the weights to some sort of vector, the details have to be implemented in the derived class
      virtual const gplib::rvec &GetWeightsAsVector() = 0;
      //! Adapt the filter weights given the Input and Desired vectors
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired) = 0;
      //! Calculate the filter output given Input
      virtual void CalcOutput(const gplib::rvec &Input, gplib::rvec &Output) = 0;
      //! The constructor needs to know the length of the input and output vectors for memory allocation
      AdaptiveFilter(const int inputsize, const int outputsize):
          FilterOutput(outputsize), Epsilon(outputsize), inputlength(inputsize),
              outputlength(outputsize)
          {
          }
      virtual ~AdaptiveFilter();
      friend class ApplyFilter;
      };
  /* @} */
  }
#endif // ADAPTIVEFILTER_H
