#ifndef TYPES_H
#define TYPES_H
#include <vector>
#include <complex>


namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    /*! types.h defines some fundamental types that are used
     *  in several classes and programs. In addition some constants are
     * defined
     */

    typedef std::complex<double> tcomp;
    //! ttsdata is used for all time-series type data
    typedef std::vector<double> ttsdata;
    //! trealdata is used for all real data that is not a time series
    typedef std::vector<double> trealdata;
    //! A vector that stores indices for other vectors
    typedef std::vector<int> tindexvector;
    //! tcompdata is the complex counterpart to trealdata
    typedef std::vector<tcomp> tcompdata;
    //! Various classes need pointer to data types these are also defined
    typedef ttsdata *ptsdata;
    //! pointer types are marked by a prefix p instead of t for the basic data type
    typedef trealdata *prealdata;
    typedef tcompdata *pcompdata;
    //! ttimedata is used to store the time information in seconds for time series data
    typedef unsigned int ttime;
    typedef std::vector<double> ttimedata;
    //! In some instances iterators are used, this is not consistent yet !
    typedef ttsdata::iterator titdata;
    //! For spike analysis the index of the data point is stored in a tvspikeindex
    typedef std::vector<int> tvspikeindex;
    typedef tvspikeindex::iterator titspikeindex;
    //! For use in function it is convenient to give complex double another name
    typedef std::complex<double> dcomp;
    //! The physical constant \f$\mu_0\f$
    const double mu = 1.256637E-6;
    //! The mathematical constant \f$\pi\f$
    const double PI = std::acos(-1.0);
    //! For complex math we need \f$i = \sqrt{-1}\f$
    const std::complex<double> I(0.0, 1.0);
  /* @} */
  }
#endif
