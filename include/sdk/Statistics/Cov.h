#ifndef COV_H_
#define COV_H_

#include "VecMat.h"

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    //! Calculate the NxN covariance matrix for a NxM matrix of observations with 0 mean
    template<typename UblasMatrix>
    UblasMatrix Cov(const UblasMatrix &observations)
      {
        const size_t nobservations = observations.size1();
        const size_t nsamples = observations.size2();
        UblasMatrix result(nobservations, nobservations);

        for (size_t i = 0; i < nobservations; ++i)
          {
            for (size_t j = 0; j <= i; ++j)
              {
                result(i, j) = 0;
                for (size_t k = 0; k < nsamples; ++k)
                  {
                    result(i, j) += observations(i, k) * observations(j, k);
                  }
                result(j, i) = result(i, j);
              }
          }
        result /= (nsamples - 1);
        return result;
      }
  /* @} */
  }
#endif /*COV_H_*/
