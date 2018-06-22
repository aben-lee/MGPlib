#ifndef CNEURALNETWORK_H
#define CNEURALNETWORK_H
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "SigmoidalNeuron.h"
#include "InputNeuron.h"
#include "AdaptiveFilter.h"
#include "UniformRNG.h"
#include "Adaptors.h"
#include "FatalException.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

namespace gplib
  {
    /** \addtogroup neuralnet Neural Network filtering */
    /* @{ */

    //! The class NeuralNetwork manages the network output calculation, neuron storage and weight adaptation
    //! Derived from AdaptiveFilter so we can use the Filter functionality
    class NeuralNetwork: public AdaptiveFilter
      {
    public:
      typedef std::vector<boost::shared_ptr<GeneralNeuron> > tNeuralLayer;
      typedef std::vector<tNeuralLayer> tNeuralArray;
      typedef std::vector<SigmoidalNeuron::tneurontype> ttypeVector;
      typedef std::vector<ttypeVector> ttypeArray;
    private:
      //! Calculate the output for the whole network
      std::vector<double> &CalcOutput()
      {
        gplib::rvec temp(LocOutput.size());
        for (size_t i = 0; i < Layers.back().size(); ++i)
          {
            LocOutput.at(i) = Layers.back().at(i)->GetOutput();
          }
        return LocOutput;
      }
      //! In some cases (plotting etc.) we want all the network weights as a single vector
      gplib::rvec WeightsAsVector;
      //! The multiplier for the momentum term
      double alpha;
      //! The adaptation stepsize
      double mu;
      //! The storage of the individual neurons
      tNeuralArray Layers;
      //! The last input to the network, this is the place the input neurons point to
      std::vector<double> LocInput;
      //! The output of the network
      std::vector<double> LocOutput;
      //! The reference values for the current iteration
      std::vector<double> LocDesired;
      //! Adapt the network weights given the current values
      void AdaptWeights()
      {
        tNeuralArray::iterator previouslayer = (Layers.end() - 2);
        tNeuralArray::iterator currlayer = (Layers.end() - 1);
        double correction = 0.0;
        for (size_t i = 0; i < previouslayer->size(); ++i)
          previouslayer->at(i)->SetDelta(0.0);
        for (size_t j = 0; j < currlayer->size(); ++j)
          {
            // Delta for the last layer depends on the difference between output and reference
            currlayer->at(j)->SetDelta(Layers.back().at(j)->CalcDeriv(
                Layers.back().at(j)->GetNet()) * (LocDesired.at(j)
                - LocOutput.at(j)));
            //follow all the weights to update delta for the previous layer
            for (size_t i = 0; i < currlayer->at(j)->GetWeights().size(); ++i)
              {
                currlayer->at(j)->GetInput().at(i)->SetDelta(
                    currlayer->at(j)->GetInput().at(i)->GetDelta()
                        + currlayer->at(j)->GetWeights().at(i) * currlayer->at(
                            j)->GetDelta());
                //calculate the correction for the last layer
                correction = alpha * currlayer->at(j)->GetOldDelta().at(i) + mu
                    * (previouslayer->at(i)->GetLastOutput())
                    * Layers.back().at(j)->GetDelta();
                currlayer->at(j)->SetWeights().at(i) += correction;
                currlayer->at(j)->SetOldDelta().at(i) = correction;
              }
            currlayer->at(j)->SetBias(Layers.back().at(j)->GetBias() + mu
                * Layers.back().at(j)->GetDelta());
          }
        //for all layers but the last and the first one
        for (size_t i = Layers.size() - 2; i >= 1; --i)
          {
            //initialize delta for previous layer
            for (size_t j = 0; j < Layers.at(i - 1).size(); ++j)
              Layers.at(i - 1).at(j)->SetDelta(0.0);
            //for all neurons in the current layer
            for (tNeuralLayer::iterator currneuron = Layers.at(i).begin(); currneuron
                < Layers.at(i).end(); ++currneuron)
              {
                //multiply delta of current neuron by derivative of activation function
                currneuron->get()->SetDelta(currneuron->get()->GetDelta()
                    * currneuron->get()->CalcDeriv(currneuron->get()->GetNet()));
                //for all weights of the current neuron
                for (size_t k = 0; k < currneuron->get()->GetWeights().size(); ++k)
                  {
                    //propagate delta along the weight to the previous layer
                    currneuron->get()->GetInput().at(k)->SetDelta(
                        currneuron->get()->GetInput().at(k)->GetDelta()
                            + currneuron->get()->GetWeights().at(k)
                                * currneuron->get()->GetDelta());
                    //calculate the correction for the current layer
                    correction
                        = alpha * currneuron->get()->GetOldDelta().at(k)
                            + mu
                                * currneuron->get()->GetInput().at(k)->GetLastOutput()
                                * currneuron->get()->GetDelta();
                    //apply weight correction
                    currneuron->get()->SetWeights().at(k) += correction;
                    //store weight correction for feedback loop
                    currneuron->get()->SetOldDelta().at(k) = correction;
                  }

                currneuron->get()->SetBias(currneuron->get()->GetBias() + mu
                    * currneuron->get()->GetDelta());
              }
          }
        //we do not have to consider the first layer, it only gets the input
      }
    public:
      //! Set the momentum multiplier
      void SetAlpha(const double a)
        {
          alpha = a;
        }
      //! Set the adaptation stepsize
      void SetMu(const double m)
        {
          mu = m;
        }
      //! Configure the layers of the network according to the types in typeArray
      void SetLayers(ttypeArray typeArray, bool cachedoutput = false)
      {
        tNeuralLayer CurrentLayer;
        GeneralLinearCombiner::tinvector inputvector;

        const size_t nlayers = typeArray.size();
        LocOutput.assign(typeArray.back().size(), 0);
        LocDesired.assign(typeArray.back().size(), 0);
        for (size_t i = 0; i < LocInput.size(); ++i)
          CurrentLayer.push_back(boost::shared_ptr<GeneralNeuron>(
              new InputNeuron(LocInput.at(i))));
        Layers.push_back(CurrentLayer);
        CurrentLayer.clear();
        cout << "Nlayers: " << nlayers << endl;
        for (size_t i = 0; i < nlayers; ++i)
          {
            for (size_t j = 0; j < typeArray.at(i).size(); ++j)
              {
                CurrentLayer.push_back(boost::shared_ptr<GeneralNeuron>(
                    new SigmoidalNeuron(typeArray.at(i).at(j), cachedoutput)));
              }
            Layers.push_back(CurrentLayer);
            CurrentLayer.clear();
          }
        for (size_t i = 1; i < nlayers + 1; ++i)
          {
            inputvector.clear();
            const size_t prevsize = Layers.at(i - 1).size();
            cout << "Previous layer size: " << prevsize << endl;
            for (size_t j = 0; j < prevsize; ++j)
              {
                inputvector.push_back(Layers.at(i - 1).at(j));
              }
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              {
                Layers.at(i).at(j)->SetInput(inputvector);
                Layers.at(i).at(j)->SetOldDelta().assign(prevsize, 0.0);
              }
          }
      }
      //! Initialize the weights with random values with the specified maxima
      void InitWeights(const double MaxWeight, const double MaxBias)
      {
        UniformRNG Random;
        for (size_t i = 1; i < Layers.size(); ++i)
          for (size_t j = 0; j < Layers.at(i).size(); ++j)
            {
              for (size_t k = 0; k < Layers.at(i).at(j)->GetWeights().size(); ++k)
                {
                  Layers.at(i).at(j)->SetWeights().at(k) = Random.GetNumber(
                      -MaxWeight, MaxWeight);
                  Layers.at(i).at(j)->SetOldDelta().at(k) = 0.0;
                }
              Layers.at(i).at(j)->SetBias(Random.GetNumber(-MaxBias, MaxBias));
            }
      }
      //! Print the topology and weights of the network for plotting with the dot program
      void PrintTopology(std::string filename)
      {
        gplib::rvec WeightVector = GetWeightsAsVector();
        const double maxpower = std::abs(*max_element(WeightVector.begin(),
            WeightVector.end(), gplib::absLess<double, double>()));
        std::ofstream output(filename.c_str());
        output << "digraph network {" << endl;
        for (size_t i = 0; i < Layers.front().size(); ++i)
          {
            output << "node [shape=point];" << std::endl;
            output << "i" << i << " -> input" << i << ";" << std::endl;
            output << "input" << i << " [shape=circle];" << std::endl;
            for (size_t j = 0; j < Layers.at(1).size(); ++j)
              {
                output << "input" << i << " -> n1" << j;
                //output <<  "[label =\" " << Layers.at(1).at(j)->GetWeights().at(i) << " \"]";
                output << "[color =\" 0.7 1.0 " << 0.1 + std::abs(
                    Layers.at(1).at(j)->GetWeights().at(i)) / maxpower
                    << " \"]";
                output << ";" << std::endl;
              }
          }
        for (size_t i = 1; i < Layers.size() - 1; ++i)
          {
            output << "{ rank=same;" << std::endl;
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              {
                output << "n" << i << j << " [shape=circle];" << std::endl;
                //output << "b" << i << j << " [shape=point];"<<std::endl;
                //output << "b" << i << j << " -> n" << i << j;
                //output << "[label =\" " << Layers.at(i).at(j)->GetBias() << " \"] ";
                //output <<  "[color =\" " << Layers.at(1).at(j)->GetBias()/maxpower << " 1.0 1.0\"]";
                //output << ";" << std::endl;
              }
            output << "};" << std::endl;
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              for (size_t k = 0; k < Layers.at(i + 1).size(); ++k)
                {
                  output << "n" << i << j << " -> n" << i + 1 << k;
                  //output <<  "[label =\" " << Layers.at(i+1).at(k)->GetWeights().at(j) << " \"]";
                  output << "[color =\" 0.7 1.0 " << 0.1 + std::abs(
                      Layers.at(i + 1).at(k)->GetWeights().at(j)) / maxpower
                      << " \"]";
                  output << ";" << std::endl;
                }
          }
        output << "{ rank=same;" << std::endl;
        for (size_t i = 0; i < Layers.back().size(); ++i)
          {
            output << "n" << Layers.size() - 1 << i << " [shape=circle];"
                << std::endl;
            //output << "b" << Layers.size()-1 << i << " -> n" << Layers.size()-1 << i;
            //output <<  "[color =\" " << Layers.at(Layers.size()-1).at(i)->GetBias()/maxpower << " 1.0 1.0\"]";
            //output <<  "[label =\" " << Layers.at(Layers.size()-1).at(i)->GetBias() << " \"]";
            //output << ";" << std::endl;
          }
        output << "};" << std::endl;
        for (size_t i = 0; i < Layers.back().size(); ++i)
          {
            output << "output" << i << " [shape=point];" << std::endl;
            for (size_t j = 0; j < Layers.at(Layers.size() - 1).size(); ++j)
              {
                output << "n" << Layers.size() - 1 << j << " -> output" << i
                    << ";" << std::endl;
              }
          }
        output << "}";
      }
      //! Print the weights of the network to the specified output stream
      virtual void PrintWeights(std::ostream &output)
      {
        for (size_t i = 1; i < Layers.size(); ++i)
          {
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              {
                copy(Layers.at(i).at(j)->GetWeights().begin(), Layers.at(i).at(
                    j)->GetWeights().end(), ostream_iterator<double> (output,
                    " "));
              }
          }
        output << endl;
      }
      //! Return the network weights as a single vector
      virtual const gplib::rvec &GetWeightsAsVector()
      {
        size_t size = 0;
        for (size_t i = 1; i < Layers.size(); ++i)
          {
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              size += Layers.at(i).at(j)->GetWeights().size();
          }
        gplib::rvec temp(size);
        size_t currstart = 0;
        for (size_t i = 1; i < Layers.size(); ++i)
          {
            for (size_t j = 0; j < Layers.at(i).size(); ++j)
              {
                for (size_t k = 0; k < Layers.at(i).at(j)->GetWeights().size(); ++k)
                  temp(currstart + k) = Layers.at(i).at(j)->GetWeights().at(k);
                currstart += Layers.at(i).at(j)->GetWeights().size();
              }
          }
        WeightsAsVector = temp;
        return WeightsAsVector;
      }

      //! Adapt the Filter with the current input and desired
      virtual void AdaptFilter(const gplib::rvec &Input,
          const gplib::rvec &Desired)
      {
        if (Desired.size() != LocDesired.size())
          throw FatalException("Input does not match network geometry !");
        copy(Desired.begin(), Desired.end(), LocDesired.begin());
        AdaptWeights();
        SetEpsilon(Desired - GetFilterOutput());
      }
      //! Calculate the output with the given input
      virtual void CalcOutput(const gplib::rvec &Input, gplib::rvec &Output)
      {
        if (Input.size() != LocInput.size())
          throw FatalException("Input does not match network geometry !");
        copy(Input.begin(), Input.end(), LocInput.begin());
        CalcOutput();
        if (Output.size() != LocOutput.size())
          throw FatalException("Output does not match network geometry !");
        copy(LocOutput.begin(), LocOutput.end(), Output.begin());
        SetOutput(Output);
      }

      //! The minium values for the network are the length of the input and output
      NeuralNetwork(const int inputsize, const int outputsize) :
          AdaptiveFilter(inputsize, outputsize), alpha(0.0), mu(0.0), LocInput(
              inputsize, 0.0), LocOutput(outputsize, 0.0), LocDesired(outputsize,
              0.0)
          {
          }

      //! Extended constructor with most of the necessary values
      NeuralNetwork(const int inputsize, const int outputsize,
          const double mu_, const ttypeArray Layersetup,
          const double maxinit, bool cachedoutput = false) :
          AdaptiveFilter(inputsize, outputsize), alpha(0.0), mu(mu_), LocInput(
              inputsize, 0.0), LocOutput(outputsize, 0.0), LocDesired(outputsize,
              0.0)
          {
            SetLayers(Layersetup, cachedoutput);
            InitWeights(maxinit, maxinit);
          }
      virtual ~NeuralNetwork();
      };
  /* @} */
  }
#endif // CNEURALNETWORK_H
