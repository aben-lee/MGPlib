#ifndef ADAPTORS_H_
#define ADAPTORS_H_
#include <complex>
#include <functional>
#include <cmath>
#include "types.h"
namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    //! General template to determine whether the absolute value is less
    template <class N1, class N2> struct absLess :
      public std::binary_function<N1, N2, bool>
      {
      bool operator()(N1 number1, N2 number2) const
        {
          return std::abs(number1) < std::abs(number2);
        }
      };


    template <class T1, class T2> struct fopow :
      public std::binary_function<T1, T2, T1>
      {
      T1 operator()(T1 base, T2 exp) const
        {
          return std::pow(base, exp);
        }
      };

    template <typename T> T inline nomod(T parm)
      {
        return parm;
      }

    struct absangle : public std::unary_function<const double,double>
      {
      double operator()(const double parm)
        {
          return std::abs(parm)*180./PI;
        }
      };

    struct real : public std::unary_function<const std::complex<double>,double>
      {
      double operator()(const std::complex<double> arg) const
        {
          return arg.real();
        }
      };

    struct imag : public std::unary_function<const std::complex<double>,double>
      {
      double operator()(const std::complex<double> arg) const
        {
          return arg.imag();
        }
      };

    struct getabs : public std::unary_function<const std::complex<double>,double>
      {
      double operator()(const std::complex<double> parm)
        {
          return abs(parm);
        }
      };

  }//end of namespace
  /* @} */
#endif /*ADAPTORS_H_*/
