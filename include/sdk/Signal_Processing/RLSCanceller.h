#ifndef RLSCANCELLER_H
#define RLSCANCELLER_H

#include "LSSOFilter.h"
#include "VecMat.h"

namespace ublas = boost::numeric::ublas;

#include <boost/numeric/ublas/operation.hpp>
//#include <boost/numeric/bindings/atlas/cblas3.hpp>
//#include <boost/numeric/bindings/atlas/cblas2.hpp>
#include <iostream>

namespace gplib
  {

    /** \addtogroup sigproc Signal processing methods */
    /* @{ */
    //! Implements a recursive least-squares adaptive filter, as described in Haykin, p. 443
    /*! The RLS filter is a more eeffective, but computationally much more expensive version
     * of the LMS filter.
     */
    class RLSCanceller: public LSSOFilter
      {
    private:
      double delta;
      double lambda;
      gplib::rmat P;
      gplib::rvec pi;
      gplib::rvec k;
    protected:
      const gplib::rmat &GetP()
        {
          return P;
        }
      const gplib::rvec &GetPi()
        {
          return pi;
        }
      const gplib::rvec &GetK()
        {
          return k;
        }
    public:
      //! Set the forgetting factor \f$ \lambda \f$, usually \f$ \lambda \ll 1 \f$
      void SetLambda(const double Mylambda)
        {
          lambda = Mylambda;
        }
      //! Get the current forgetting factor
      double GetLambda()
        {
          return lambda;
        }
      //! Set the regularization factor
      void SetDelta(const double Mydelta)
        {
          delta = Mydelta;
        }
      double GetDelta()
        {
          return delta;
        }
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        SetEpsilon(Desired - GetFilterOutput());
        ublas::axpy_prod(P,Input,pi,true);
        //atlas::gemv(P, Input, pi);
        k = pi / (lambda + ublas::prec_inner_prod(Input, pi));
        SetWeights() += k * GetEpsilon()(0);
        gplib::rmat temp1(P);
        ublas::noalias(temp1) -= ublas::prec_prod(ublas::outer_prod(k,Input),P);
        //gplib::rmat temp1(P);
        //atlas::ger(k,Input,kiouter);  // ublas::outer_prod(k,Input); has replaced this line
        //gplib::rmat temp2(ublas::outer_prod(k, Input));

        //atlas::gemm(-1.0 / lambda, temp2, temp1, 1.0 / lambda, P);
        P = temp1 / lambda;
      }
      RLSCanceller(const int inputsize):
          LSSOFilter(inputsize), delta(0.9999999), lambda(1), P(inputsize,
              inputsize), pi(inputsize), k(inputsize)
          {
            P = 1. / delta * ublas::identity_matrix<double>(inputsize);
          }

      RLSCanceller(const int inputsize, const double MyDelta,
          const double MyLambda):
          LSSOFilter(inputsize), delta(MyDelta), lambda(MyLambda), P(inputsize,
              inputsize), pi(inputsize), k(inputsize)
          {
            P = 1. / delta * ublas::identity_matrix<double>(inputsize);
          }
      virtual ~RLSCanceller();
      };
  /* @} */
  }
#endif // RLSCANCELLER_H
