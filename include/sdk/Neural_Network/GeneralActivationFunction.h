#ifndef CGENERALACTIVATIONFUNCTION_H
#define CGENERALACTIVATIONFUNCTION_H

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! The base class for all activation functions in neural network

    /*! The activation function in a neural network node determines the type of
     * non-linearity between input and output. We have to implement the activation function
     * and its derivative.
     */
    class GeneralActivationFunction
      {
    public:
      //! The function that maps between the weighted sum that's the input of the neuron and the output
      virtual double CalcOutput(const double input) = 0;
      //! The derivative of the function defined in CalcOutput
      virtual double CalcDeriv(const double input) = 0;
      GeneralActivationFunction();
      virtual ~GeneralActivationFunction();
      };
  /* @} */
  }
#endif // CGENERALACTIVATIONFUNCTION_H
