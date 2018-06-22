#ifndef CGENERALNEURON_H
#define CGENERALNEURON_H
#include "GeneralLinearCombiner.h"

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! The base class for all neurons in a neural network

    /*! GeneralNeuron implements some common functionality, but mostly abstract base classes
     * to define a common interface for all neurons*/
    class GeneralNeuron
      {
    private:
      //! We have to store the last output, because during adaption stage the weights might be changed but we want the original value
      double LastOutput;
      //! The function that calculates the output of the neuron, has to be overriden and is executed by GetOutput in this class
      virtual double CalcOutput() = 0;
    public:
      //! Calculate the derivative of the activation function, at point input
      virtual double CalcDeriv(const double input) = 0;
      //! Get the net output before application of the activation function
      virtual double GetNet() = 0;
      //! Get delta for the weight correction formula
      virtual double GetDelta() = 0;
      //! Set delta
      virtual void SetDelta(const double d) = 0;
      //! Set the bias
      virtual void SetBias(const double b) = 0;
      //! Get the bias
      virtual double GetBias() = 0;
      //! Access function for the weights
      virtual const std::vector<double> &GetWeights() = 0;
      virtual std::vector<double> &SetWeights() = 0;
      //! Vector valued delta for the momentum adaptation scheme
      virtual const std::vector<double> &GetOldDelta() = 0;
      virtual std::vector<double> &SetOldDelta() = 0;
      //! Get the pointers to the input neurons
      virtual const GeneralLinearCombiner::tinvector &GetInput() = 0;
      //! Get the output given the current weights
      double GetOutput()
        {
          LastOutput = CalcOutput();
          return LastOutput;
        }
      //! Get the last result from calling GetOutput, needed during adaptation
      double GetLastOutput()
        {
          return LastOutput;
        }
      //! Set pointers to the input
      virtual void SetInput(const GeneralLinearCombiner::tinvector &input);

      GeneralNeuron()
        {
        }
      virtual ~GeneralNeuron()
        {
        }
      };
  /* @} */
  }
#endif // CGENERALNEURON_H
