#ifndef CBIPOLARACTIVATIONFUNCTION_H
#define CBIPOLARACTIVATIONFUNCTION_H

#include "GeneralActivationFunction.h"
#include <cmath>
#include "NumUtil.h"
#include <iostream>

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */
    //! The bipolar activation function is a common function in NN applications
    /*! The output is \f$ \tanh (0.5 x) \f$ and can assume values between \f$ -1 \ldots 1 \f$.
     */
    class BipolarActivationFunction: public GeneralActivationFunction
      {
    public:
      virtual double CalcOutput(const double input)
        {
          return (tanh(0.5 * input));
        }
      virtual double CalcDeriv(const double input)
        {
          return (0.5 * 1. / pow2(cosh(input)));
        }
      BipolarActivationFunction();
      virtual ~BipolarActivationFunction();
      };
  /* @} */
  }
#endif // CBIPOLARACTIVATIONFUNCTION_H
