#ifndef PCA_H_
#define PCA_H_

#include "VecMat.h"
#include "statutils.h"
#include "Cov.h"

namespace ublas = boost::numeric::ublas;

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    /*! /file
     *  This file contains function connected to Principal Component Analysis
     */

    //! This template function calculates the principal component rotation matrix from a matrix of observations
    /*! The input matrix observations has the different channels (or datasets) as rows and corresponding samples as columns
     * the parameter pcatrans will contain the matrix of principal component vectors, at the moment in no particular order
     */
    template<typename UblasMatrix>
    void PCA(const UblasMatrix &observations, gplib::cmat &evectors,
        gplib::cvec &evalues)
      {
        UblasMatrix loc_obs(observations);
        for (unsigned int i = 0; i < loc_obs.size1(); ++i)
          SubMean(row(loc_obs, i).begin(), row(loc_obs, i).end());
        UblasMatrix covariance = Cov(loc_obs);

        const int nchannels = covariance.size1();

        gplib::rvec s(nchannels);
        gplib::cmat vl(nchannels, nchannels), vr(nchannels, nchannels), in(
            nchannels, nchannels);
//        boost::numeric::bindings::lapack::geev(covariance, evalues, &vl,
//            &evectors, boost::numeric::bindings::lapack::optimal_workspace());
      }

    //! Calculate the Whitening Matrix
    /*! Given the complex matrix of eigenvectors evectors
     *  and the complex vector of eigenvalues as calculated by PCA,
     * calculate the Whitening Matrix and return it*/
    gplib::cmat WhiteMat(gplib::cmat &evectors, gplib::cvec &evalues)
      {
        gplib::cmat result(evectors);
        for (unsigned int i = 0; i < evectors.size2(); ++i)
          ublas::column(result, i) /=  std::sqrt(evalues(i));
        return trans(result);
      }

    //! Calculate the Dewhitening Matrix
    /*! Given the complex matrix of eigenvectors evectors
     *  and the complex vector of eigenvalues as calculated by PCA,
     * calculate the DeWhitening Matrix that reverses the effect of the Whitening Matrix
     * and return it. */
    gplib::cmat DeWhiteMat(gplib::cmat &evectors, gplib::cvec &evalues)
      {
        gplib::cmat result(evectors);
        for (unsigned int i = 0; i < evectors.size2(); ++i)
          ublas::column(result, i) *= std::sqrt(evalues(i));
        return result;
      }
  /* @} */
  }
#endif /*PCA_H_*/
