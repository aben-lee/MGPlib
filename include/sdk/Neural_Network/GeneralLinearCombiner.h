#ifndef CGENERALLINEARCOMBINER_H
#define CGENERALLINEARCOMBINER_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include "GeneralLinearCombiner.h"
#include "GeneralNeuron.h"
#include <algorithm>

namespace gplib
  {
    class GeneralNeuron;

    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! A linear combiner as a component of a neural network
    /*! It can cache the last output for faster calculation within the network, but this assumes that between every output calculation
     the weights are updated.
     */
    class GeneralLinearCombiner
      {
    public:
      typedef std::vector<boost::shared_ptr<GeneralNeuron> > tinvector;
    private:
      //! The weight for each input channel
      std::vector<double> Weights;
      //! The current output
      double Output;
      //! A vector of pointers to other neurons, that provide the input for this combiner
      tinvector Input;
      //! The bias weight
      double Bias;
      //! have the weights changed since the last calculation ?
      bool wchanged;
      //! has the bias changed since the last calculation ?
      bool bchanged;
      //! do we want to cache the output or recalculate it every time
      bool cachedoutput;
    public:
      //! Set the bias weigth
      void SetBias(const double b)
        {
          bchanged = true;
          Bias = b;
        }
      //! Get the current value for the bias
      double GetBias() const
        {
          return Bias;
        }
      //! Get the values of the Weight vector
      const std::vector<double> &GetWeights() const
        {
          return Weights;
        }
      //! change the values of the Weight vector
      std::vector<double> &SetWeights()
        {
          wchanged = true;
          return Weights;
        }
      //! Calculate the output given the current configuration
      virtual double CalcOutput()
      {
        //if we do not want cached output or the weights or the bias has changed
        if (!cachedoutput || wchanged || bchanged)
          {
            // we calculate the output from bias, weights and input values
            Output = Bias;
            const size_t size = Weights.size();
            for (unsigned int i = 0; i < size; ++i)
              Output += (Input.at(i)->GetOutput()) * Weights.at(i);
            // the next call will return the stored results, unless the weights or the bias have changed
            wchanged = false;
            bchanged = false;
          }
        return Output;
      }

      //! connect the input channels to the neurons given in LocalInput
      virtual void SetInput(const tinvector &LocalInput)
      {
        const int size = LocalInput.size();
        // initialize the weights
        Weights.assign(size, 0);
        // we reassigned the input, so we have to recalculate the output in any case
        wchanged = true;
        bchanged = true;
        // initialize the Bias
        Bias = 0.0;
        // if we had some input before, clear it
        if (!Input.empty())
          Input.clear();
        //copy the parameter values to the local property
        copy(LocalInput.begin(), LocalInput.end(), back_inserter(Input));
      }
      //! get the input channel configuration
      const tinvector &GetInput() const
        {
          return Input;
        }
      explicit GeneralLinearCombiner(bool wantcached = false):
          wchanged(true), bchanged(true), cachedoutput(wantcached)
          {
          }
      virtual ~GeneralLinearCombiner();
      };
  /* @} */
  }
#endif // CGENERALLINEARCOMBINER_H
