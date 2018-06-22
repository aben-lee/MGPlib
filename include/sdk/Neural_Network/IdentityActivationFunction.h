#ifndef CIDENTITYACTIVATIONFUNCTION_H
#define CIDENTITYACTIVATIONFUNCTION_H

#include "GeneralActivationFunction.h"
#include <iostream>

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */
    //! This activation function simply outputs its input
    class IdentityActivationFunction: public GeneralActivationFunction
      {
    public:
      virtual double CalcOutput(const double input)
        {
          return input;
        }
      virtual double CalcDeriv(const double input)
        {
          return 1.0;
        }
      IdentityActivationFunction();
      virtual ~IdentityActivationFunction();
      };
  /* @} */
  }
#endif // CIDENTITYACTIVATIONFUNCTION_H
