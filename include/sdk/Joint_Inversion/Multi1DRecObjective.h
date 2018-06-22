#ifndef MULTI1DRECOBJECTIVE_H_
#define MULTI1DRECOBJECTIVE_H_

#include "PlottableObjective.h"
#include <vector>
#include "C1DRecObjective.h"
#include "AbsVelRecObjective.h"
#include <boost/shared_ptr.hpp>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>
#include "FatalException.h"
#include "convert.h"
#include <iostream>

namespace gplib
  {
    //! This class is used to model several receiver functions simultaneously
    class Multi1DRecObjective: public PlottableObjective
      {
    private:
      std::vector<boost::shared_ptr<C1DRecObjective> > Objectives;
    public:
      //! return a pointer to a copy of the current object
      virtual Multi1DRecObjective *clone() const
        {
          return new Multi1DRecObjective(*this);
        }
      //! Set the start and end time in s for the part we want to fit
      void SetTimeWindow(const double start, const double end)
      {
        for_each(Objectives.begin(), Objectives.end(), boost::bind(
            &C1DRecObjective::SetTimeWindow, _1, start, end));
      }
      //! Set Poisson's ratio to calculate P velocities from S-Velocities
      void SetPoisson(const double ratio)
      {
        for_each(Objectives.begin(), Objectives.end(), boost::bind(
            &C1DRecObjective::SetPoisson, _1, ratio));
      }
      //! Add another reciever function to fit
      void AddRecFunction(boost::shared_ptr<const SeismicDataComp> TheRecData,
          const int myshift, const double mysigma, const double myc,
          const double myslowness, const RecCalc::trfmethod method,
          const double errorlevel, const bool normalized)
      {
        boost::shared_ptr<C1DRecObjective> Obj(new C1DRecObjective(TheRecData,
            myshift, mysigma, myc, myslowness, method, normalized));
        Obj->SetErrorLevel(errorlevel);
        Objectives.push_back(Obj);

      }
      //! Add another receiver function with absolute velocity transformation
      void AddAbsVelFunction(
          boost::shared_ptr<const SeismicDataComp> TheRecData,
          SurfaceWaveData &AbsVel, const int myshift, const double mysigma,
          const double myc, const double myslowness,
          const RecCalc::trfmethod method, const double errorlevel,
          const bool normalized, const double absvelweight,
          const double recweight)
      {
        boost::shared_ptr<AbsVelRecObjective> Obj(new AbsVelRecObjective(
            TheRecData, AbsVel, myshift, mysigma, myc, myslowness, method,
            normalized));
        Obj->SetErrorLevel(errorlevel);
        Obj->SetAbsVelWeight(absvelweight);
        Obj->SetRecWeight(recweight);
        Objectives.push_back(Obj);
      }
      //! The operations that have to be done before the parallel part
      virtual void PreParallel(const ttranscribed &member)
      {
        if (Objectives.empty())
          throw FatalException(
              "In Multi1DRecObjective: No Objective functions set !");
        const size_t nobjs = Objectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            Objectives.at(i)->SetParallelID(GetParallelID() + stringify(i));

          }
        for_each(Objectives.begin(), Objectives.end(), boost::bind(
            &C1DRecObjective::PreParallel, _1, member));
      }
      //! The operations that have to be done after the parallel part
      virtual double PostParallel(const ttranscribed &member)
      {

        std::vector<double> values;
        const size_t nobjs = Objectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            Objectives.at(i)->SetParallelID(GetParallelID() + stringify(i));

          }
        transform(Objectives.begin(), Objectives.end(), back_inserter(values),
            boost::bind(&C1DRecObjective::PostParallel, _1, member));
        double sumsquares = inner_product(values.begin(), values.end(),
            values.begin(), 0.0);
        //copy(values.begin(),values.end(),ostream_iterator<double>(cout," "));
        //cout << " " << sqrt(sumsquares/values.size()) << endl;
        return sqrt(sumsquares / values.size());
      }
      //! The operations that safely can be done in parallel
      virtual void SafeParallel(const ttranscribed &member)
      {
        const size_t nobjs = Objectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            Objectives.at(i)->SetParallelID(GetParallelID() + stringify(i));

          }
        for_each(Objectives.begin(), Objectives.end(), boost::bind(
            &C1DRecObjective::SafeParallel, _1, member));
      }
      //! Write out all the data, endings will be appended automatically
      virtual void WriteData(const std::string &filename)
      {
        const size_t nobjs = Objectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            Objectives.at(i)->WriteData(filename + stringify(i));

          }
        //for_each(Objectives.begin(), Objectives.end(), boost::bind(
        //       &C1DRecObjective::WriteData, _1, filename));
      }
      //! Write the current model to ascii file for calculations
      void WriteModel(const std::string &filename)
      {
        Objectives.front()->WriteModel(filename); //all models are the same, so we only write the first
      }
      //! Write the current model to ascii file for plotting
      void WritePlot(const std::string &filename)
      {
        Objectives.front()->WritePlot(filename); //all models are the same, so we only plot the first
      }
      Multi1DRecObjective(const Multi1DRecObjective &Old)
      {
        const size_t nobjs = Old.Objectives.size();
        Objectives.clear();
        for (size_t i = 0; i < nobjs; ++i)
          {
            boost::shared_ptr<C1DRecObjective> Obj(
                Old.Objectives.at(i)->clone());
            Objectives.push_back(Obj);
          }
      }
      Multi1DRecObjective& operator=(const Multi1DRecObjective& source)
      {
        if (this == &source)
          return *this;
        const size_t nobjs = source.Objectives.size();
        Objectives.clear();
        for (size_t i = 0; i < nobjs; ++i)
          {
            boost::shared_ptr<C1DRecObjective> Obj(
                source.Objectives.at(i)->clone());
            Objectives.push_back(Obj);
          }
        return *this;
      }
      Multi1DRecObjective();
      virtual ~Multi1DRecObjective();
      };
  }
#endif /*MULTI1DRECOBJECTIVE_H_*/
