#ifndef CSIGMOIDALNEURON_H
#define CSIGMOIDALNEURON_H
#include "GeneralLinearCombiner.h"
#include "GeneralActivationFunction.h"
#include "GeneralNeuron.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "BipolarActivationFunction.h"
#include "IdentityActivationFunction.h"

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! SigmoidalNeuron implements the main functionality of neurons in a neural network
    class SigmoidalNeuron: public GeneralNeuron
      {
    public:
      //! At the moment there are two types of neurons: bipolar and identity, they differ in their activation function
      enum tneurontype
        {
        bipolar, identity
        };
    private:
      //! The old weight correction for momentum adaptation
      std::vector<double> OldDelta;
      //! A pointer to the linear combiner used
      boost::shared_ptr<GeneralLinearCombiner> Combiner;
      //! Pointer to the activation function
      boost::shared_ptr<GeneralActivationFunction> Function;
      //! The Output, only updated in CalcOutput
      double Output;
      //! Correction term in the adaptation stage
      double Delta;
      //! The result from the linear combiner, only updated in CalcOutput to avoid multiple calculations
      double Net;
      //! Do we want the linear combiner to cache its output
      bool cachedoutput;
      //! The core routine that calculates the output of the neuron
      virtual double CalcOutput()
      {
        Net = Combiner->CalcOutput();
        Output = Function->CalcOutput(Net);
        return Output;
      }
    public:
      //! Get the last weight correction for momentum adaptation
      virtual const std::vector<double> &GetOldDelta()
        {
          return OldDelta;
        }
      virtual std::vector<double> &SetOldDelta()
        {
          return OldDelta;
        }
      //! Return the derivative of the activation function
      virtual double CalcDeriv(const double input)
        {
          return Function->CalcDeriv(input);
        }
      //! Get the raw output of the linear combiner
      virtual double GetNet()
        {
          return Net;
        }
      //! Get the delta term of the weight correction formula
      virtual double GetDelta()
        {
          return Delta;
        }
      //! Set the delta term of the weight correction formula
      virtual void SetDelta(const double d)
        {
          Delta = d;
        }
      //! Set the bias of the linear combiner, the following functions are mostly for convenience access
      virtual void SetBias(const double b)
        {
          Combiner->SetBias(b);
        }
      //! Get the bias of the linear combiner
      virtual double GetBias()
        {
          return Combiner->GetBias();
        }
      //! Get the weights
      virtual const std::vector<double> &GetWeights()
        {
          return Combiner->GetWeights();
        }
      //! Set the weights
      virtual std::vector<double> &SetWeights()
        {
          return Combiner->SetWeights();
        }
      //! Get the input neurons
      virtual const GeneralLinearCombiner::tinvector &GetInput()
        {
          return Combiner->GetInput();
        }
      //! Set the input neurons
      virtual void SetInput(const GeneralLinearCombiner::tinvector &input)
      {
        Combiner->SetInput(input);
      }

      //! Set the type of neuron, determines the activation function
      virtual void SetType(tneurontype type)
      {
        switch (type)
          {
        case bipolar:
          Function = boost::shared_ptr<GeneralActivationFunction>(
              new BipolarActivationFunction);
          break;
        case identity:
          Function = boost::shared_ptr<GeneralActivationFunction>(
              new IdentityActivationFunction);
          break;
          }
        Combiner = boost::shared_ptr<GeneralLinearCombiner>(
            new GeneralLinearCombiner(cachedoutput));
      }
      //! Construct neuron with a known type
      explicit SigmoidalNeuron(tneurontype type, bool wantcached = false) :
          Output(0.0), Delta(0.0), Net(0.0), cachedoutput(wantcached)
          {
            SetType(type);
          }
      virtual ~SigmoidalNeuron();
      };
  /* @} */
  }
#endif // CSIGMOIDALNEURON_H
