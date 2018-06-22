#ifndef C1DMTOBJECTIVE_H
#define C1DMTOBJECTIVE_H

#include "PlottableObjective.h"
#include "MTStation.h"
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cassert>
#include <boost/numeric/ublas/io.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "miscfunc.h"
#include "Adaptors.h"
#include "FatalException.h"
namespace gplib
  {
    //! C1DMTObjective is the base class for MT misfit calculations from 1D models, it provides common functionality to calculate the misfit of various MT parameters
    class C1DMTObjective: public PlottableObjective
      {
    public:
      // We have to declare some public typedefs that are needed below
      //! A function that returns a real valued quantity calculated from an MT impedance tensor
      typedef boost::function<double(const MTTensor* const )> datafunc_t;
      //! A vector of MT data functions. This is used to store the types of data to fit
      typedef std::vector<datafunc_t> datafuncvector_t;
    private:
      //! A vector of member functions to MTTensor that return the data to fit
      datafuncvector_t DataFunctions;
      //! A vector of member functions that return the errors associated with the functions in DataFunctions
      datafuncvector_t ErrorFunctions;
      //! A vector of doubles that cotains the errorlevels associated with the functions in DataFunctions
      std::vector<double> ErrorLevels;
      //! have the fit parameters been set or do we use default values
      bool FitparametersSet;
      //! A copy of the data to fit
      MTStation MTData;
      //! This abstract function has to calculate the Synthetic data and fill the MTSynth object with it
      virtual void CalcSynthData(const ttranscribed &member) = 0;
    protected:
      virtual MTStation &GetMTSynth() = 0;
    public:
      //! function to set the parameters that determine the type of fit
      void SetFitParameters(const datafuncvector_t TheDataV,
          const datafuncvector_t TheErrorV,
          const std::vector<double> TheErrLevel)
      {
        //we have to make sure all vectors have the same size
        if (TheDataV.size() != TheErrorV.size() || TheDataV.size()
            != TheErrLevel.size())
          throw FatalException(
              "Vectors of fit parameters have incompatible size !");
        if (TheDataV.empty())
          throw FatalException("Cannot work with empty vectors !");
        //we resize and copy, so we overwrite anything that was in the vector before
        DataFunctions.resize(TheDataV.size());
        ErrorFunctions.resize(TheErrorV.size());
        ErrorLevels.resize(TheErrLevel.size());
        copy(TheDataV.begin(), TheDataV.end(), DataFunctions.begin());
        copy(TheErrorV.begin(), TheErrorV.end(), ErrorFunctions.begin());
        copy(TheErrLevel.begin(), TheErrLevel.end(), ErrorLevels.begin());
        FitparametersSet = true; //signal that the parameters have been selected by the user
      }
      void AppendFitParameters(const datafunc_t TheDataFunc,
          const datafunc_t TheErrorFunc, const double TheErrLevel)
      {
        if (!FitparametersSet) // if we didn't set anything before
          {
            DataFunctions.clear();
            ErrorFunctions.clear();
            ErrorLevels.clear();
            DataFunctions.push_back(TheDataFunc); //we overwrite the defaults
            ErrorFunctions.push_back(TheErrorFunc);
            ErrorLevels.push_back(TheErrLevel);
            FitparametersSet = true;
          }
        else //if we have set something before
          {
            DataFunctions.push_back(TheDataFunc); // we append the new values
            ErrorFunctions.push_back(TheErrorFunc);
            ErrorLevels.push_back(TheErrLevel);
          }
      }
      //! Calc misfit for a model given by member
      virtual void SafeParallel(const ttranscribed &member)
      {

        double returnvalue = 0; // init misfit value

        if (!FitparametersSet)
          {
            FitparametersSet = true; // we only issue this warning once
            cerr
                << "Warning errorlevel and Fitparameters not set, using hardcoded default ! "
                << endl;
            cerr << "You should change your program !" << endl;
          }
        //if we didn't set the frequencies before
        if (GetMTSynth().GetFrequencies().empty())
          {
            //make sure the modelled frequencies match the data frequencies
            GetMTSynth().SetFrequencies(MTData.GetFrequencies());
          }
        //calculate the synthetic data for the model
        CalcSynthData(member);

        //the number of data we fit, depends on which aspects of the tensor we fit
        unsigned int datacount = 0;
        double currdata = 0.0;
        typedef vector<MTTensor>::const_iterator tensorit_t; // local convenience typedef
        typedef datafuncvector_t::iterator funcit_t;
        //we have to step through all types of data to fit
        //we achieve this vectors of function that return the necessary quantities and their errors
        //for each tensor element we call those two functions
        funcit_t dfuncit = DataFunctions.begin();
        funcit_t efuncit = ErrorFunctions.begin();
        //we can have a different error floor for every type of data
        std::vector<double>::const_iterator elevelit = ErrorLevels.begin();
        const unsigned int ndata = DataFunctions.size()
            * MTData.GetMTData().size();
        SetMisfit().resize(ndata); //make sure Misfit in base class can hold enough elements
        SetSynthData().resize(ndata); // and same for data

        //for all types of parameters to calculate misfit for
        //step through the frequencies and add up the misfit
        for (/* init done above*/; dfuncit != DataFunctions.end(); ++dfuncit, ++efuncit, ++elevelit)
          {
            for (tensorit_t datait = MTData.GetMTData().begin(), synthit =
                GetMTSynth().GetMTData().begin(); datait
                < MTData.GetMTData().end(); ++datait, ++synthit) // go through the frequencies
              {
                //calculate the current parameter using the function pointer in the vector DataFunctions
                //the function calls through iterators with elements that are referenced by iterators
                //are cryptic so we store them in temporary variables with better names
                currdata = (*dfuncit)(&*datait);
                const double currpredicted = (*dfuncit)(&*synthit);
                const double currerror = (*efuncit)(&*datait);
                const double errorlevel = *elevelit;
                returnvalue += CalcMisfit(currdata, currpredicted, currerror,
                    errorlevel, datacount);
                ++datacount;
              }
          }
        SetRMS(std::pow(returnvalue / datacount, 1.0 / GetFitExponent()));
      }

      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      //! return a vector with pointers to the functions used to calculate the errors
      const datafuncvector_t &GetErrorFunctions() const
        {
          return ErrorFunctions;
        }
      //! write the current model to a file
      virtual void WriteModel(const std::string &filename)=0;
      //! write the current model for plotting to a file
      virtual void WritePlot(const std::string &filename)=0;
      //! Write current data to a file
      virtual void WriteData(const std::string &filename)=0;
      //! We need data to fit for any objective function, so we want it as constructor parameter, but no implicit conversion
      C1DMTObjective(const MTStation &LocalMTData) :
          // we always need a reference to the data to fit and an object to calculate synthetic data
              MTData(LocalMTData)
          {
            // if nothing will be set in SetFitParameters
            // we use the xy phase by default
            DataFunctions.push_back(&MTTensor::GetPhixy);
            ErrorFunctions.push_back(&MTTensor::GetdPhixy);
            ErrorLevels.push_back(0.01);
            FitparametersSet = false; //but we want to know whether the fit parameters have been set to issue a warning
          }
      C1DMTObjective(const C1DMTObjective &Old)
          :
               PlottableObjective(Old), DataFunctions(Old.DataFunctions),
                   ErrorFunctions(Old.ErrorFunctions), ErrorLevels(Old.ErrorLevels),
                   FitparametersSet(Old.FitparametersSet), MTData(Old.MTData)
               {
               }
      virtual ~C1DMTObjective();
      C1DMTObjective& operator=(const C1DMTObjective& source)
      {
        if (this == &source)
          return *this;
        PlottableObjective::operator=(source);
        DataFunctions.resize(source.DataFunctions.size());
        ErrorFunctions.resize(source.ErrorFunctions.size());
        ErrorLevels.resize(source.ErrorLevels.size());
        copy(source.DataFunctions.begin(), source.DataFunctions.end(),
            DataFunctions.begin());
        copy(source.ErrorFunctions.begin(), source.ErrorFunctions.end(),
            ErrorFunctions.begin());
        copy(source.ErrorLevels.begin(), source.ErrorLevels.end(),
            ErrorLevels.begin());
        MTData = source.MTData;
        FitparametersSet = source.FitparametersSet;
        return *this;
      }
      };
  }
#endif
