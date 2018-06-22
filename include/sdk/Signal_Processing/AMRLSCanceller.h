#ifndef AMRLSCANCELLER_H
#define AMRLSCANCELLER_H

#include "RLSCanceller.h"
#include "VecMat.h"
#include <algorithm>
namespace ublas = boost::numeric::ublas;

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    //! An implementation of the Recursive Least Squares filter with adptive memory as described in Hakin, p. 663
    class AMRLSCanceller: public RLSCanceller
      {
        const double maxlambda = 1.0 - 1e-6;
    private:
      double Lambdaplus;
      double Lambdaminus;
      gplib::rmat S;
      gplib::rvec Psi;
      double Alpha;
      gplib::rmat factor1;
      gplib::rmat factor2;
      ublas::identity_matrix<double> I;
    public:
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        RLSCanceller::AdaptFilter(Input, Desired);
        SetLambda(GetLambda() + Alpha * GetEpsilon()(0) * prec_inner_prod(Psi,
            Input));
        SetLambda(std::min(GetLambda(), Lambdaplus));
        SetLambda(std::max(GetLambda(), Lambdaminus));

        factor1 = I - ublas::outer_prod(GetK(), Input);
        factor2 = I - ublas::outer_prod(Input, GetK());
        rmat temp1(ublas::prec_prod(factor1, S));
        S = ublas::prec_prod(temp1, factor2);
        S += ublas::outer_prod(GetK(), GetK());
        S -= GetP();
        S /= GetLambda();

        Psi = prec_prod(factor1, Psi) + prec_prod(S, Input) * GetEpsilon()(0);
      }
      AMRLSCanceller(const int inputsize, const double MyDelta,
          const double MyLambda, const double MyAlpha) :
          RLSCanceller(inputsize, MyDelta, MyLambda), Lambdaplus(maxlambda),
              Lambdaminus(MyLambda / 2.0), S(inputsize, inputsize), Psi(inputsize),
              Alpha(MyAlpha), factor1(inputsize, inputsize), factor2(inputsize,
                  inputsize), I(inputsize)
          {
            std::fill_n(S.data().begin(), inputsize * inputsize, 0.0);
            std::fill_n(Psi.begin(), inputsize, 0.0);
          }
      virtual ~AMRLSCanceller();
      };
  /* @} */
  }
#endif // RLSCANCELLER_H
