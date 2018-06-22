#ifndef VECMAT_H_
#define VECMAT_H_

  /** \addtogroup genfunc General functions from various areas */
  /* @{ */
  
/*! \file This file provides the basic includes for all matrix and vector operations. We store the matrices in column major format to
 * enable interfacing with fortran codes for blas, lapack etc.
 */

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#ifdef HAVEUBLASTRAITS
#include <boost/numeric/bindings/lapack/lapack.hpp>
#include <boost/numeric/bindings/lapack/geev.hpp>
#include <boost/numeric/bindings/traits/ublas_matrix.hpp>
#include <boost/numeric/bindings/traits/ublas_vector.hpp>
#include <boost/numeric/bindings/traits/vector_traits.hpp>
#include <boost/numeric/ublas/lu.hpp>
#endif
#include <complex>

namespace gplib
  {
    //! A matrix with complex valued entries
    typedef boost::numeric::ublas::matrix<std::complex<double>,boost::numeric::ublas::column_major> cmat;
    //! A matrix with real valued entries
    typedef boost::numeric::ublas::matrix<double,boost::numeric::ublas::column_major> rmat;
    //! A vector with complex valued entries
    typedef boost::numeric::ublas::vector<std::complex<double> > cvec;
    //! A vector with real valued entries
    typedef boost::numeric::ublas::vector<double> rvec;
  }
/* @} */
#endif /*VECMAT_H_*/
