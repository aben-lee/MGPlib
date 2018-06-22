#ifndef INPUTNEURON_H_
#define INPUTNEURON_H_
#include "GeneralNeuron.h"
#include "FatalException.h"

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! The iput neuron class provides the bridge between the network input and the other neurons,
    //! a lot of base class functionality does not make sense here and throws an exception, should think of a better way
    class InputNeuron: public GeneralNeuron
      {
    private:
      //! A reference to a double that is used as input for the neural network
      double &In;
      //! There are no weights or bias, so we just return the input value as output
      virtual double CalcOutput()
        {
          return In;
        }
    public:
      virtual const std::vector<double> &GetOldDelta()
        {
          throw FatalException("Not implemented");
        }
      virtual std::vector<double> &SetOldDelta()
        {
          throw FatalException("Not implemented");
        }
      virtual double CalcDeriv(const double input)
        {
          return 1.0;
        }
      virtual double GetNet()
        {
          return In;
        }
      virtual double GetDelta()
        {
          return 0.0;
        }
      virtual void SetDelta(const double d)
        {
        }
      virtual void SetBias(const double b)
        {
        }
      virtual double GetBias()
        {
          return 0.0;
        }
      virtual const std::vector<double> &GetWeights()
        {
          throw FatalException("Not implemented");
        }
      virtual std::vector<double> &SetWeights()
        {
          throw FatalException("Not implemented");
        }
      virtual const GeneralLinearCombiner::tinvector &GetInput()
        {
          throw FatalException("Not implemented");
        }
      InputNeuron(double &Infield) :
        In(Infield)
        {
        }
      virtual ~InputNeuron()
        {
        }
      };
  /* @} */
  }
#endif /*INPUTNEURON_H_*/
