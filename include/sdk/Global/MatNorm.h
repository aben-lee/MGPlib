#ifndef MATNORM_H_
#define MATNORM_H_
#include "VecMat.h"
#include <algorithm>

/** \addtogroup genfunc General functions from various areas */
/* @{ */

namespace gplib
  {
    //! Calculate the spectral norm of a matrix
    double SpectralNorm(const gplib::rmat &M)
      {
        gplib::rmat temp1(M);
        gplib::rmat u(M.size1(), M.size2());
        gplib::rmat vt(M.size2(), M.size2());
        gplib::rvec s(M.size2());
        boost::numeric::bindings::lapack::gesvd(temp1, s, u, vt);
        return *max_element(s.begin(), s.end());
      }
    //! Calculate the Frobenius norm of a matrix
    double FrobeniusNorm(const gplib::rmat &M)
      {
        gplib::rmat temp1(M);
        gplib::rmat u(M.size1(), M.size2());
        gplib::rmat vt(M.size2(), M.size2());
        gplib::rvec s(M.size2());
        boost::numeric::bindings::lapack::gesvd(temp1, s, u, vt);
        return sum(s);
      }
  }
/* @} */
#endif /*MATNORM_H_*/
