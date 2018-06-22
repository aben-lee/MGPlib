#ifndef KHL_H_
#define KHL_H_

#include "miscfunc.h"
#include "VecMat.h"
#include <iostream>

namespace ublas = boost::numeric::ublas;

namespace gplib
  {
    void KHLExpand(const rvec &input, rmat &v, rvec &a)
      {
        //rvec autocorr(input);
        //Correl(input,input,autocorr);
        rmat corrmat(input.size(), input.size());
        for (int i = 0; i < input.size(); ++i)
          for (int j = 0; j < input.size(); ++j)
            corrmat(i, j) = input((i + j) % input.size());
        cmat vl(input.size(), input.size()), vr(input.size(), input.size());
        cvec evalues(input.size());
        boost::numeric::bindings::lapack::geev(corrmat, evalues, &vl, &vr,
            boost::numeric::bindings::lapack::optimal_workspace());
        v = real(vr);
        noalias(a) = prod(trans(v), input);

      }
  }
#endif /*KHL_H_*/
