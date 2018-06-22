#ifndef CGENERALOBJECTIVE_H
#define CGENERALOBJECTIVE_H
#include "gentypes.h"
#include <string>
#include <numeric>
#include <cmath>

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! The basic object for any objective function, mainly an interface class and some storage
    /*! All objective functions should be derived from this class to be usable with the genetic algorithms.
     * Also the linearized classes use this base class to access objective functions.
     * The main functionality is implemented in the three functions PreParallel, SafeParallel and PostParallel.
     * This division is ncessary to account for various types of computations in a parallel environment.
     * In addition derived classes have to implement the clone function and a copy constructor and operator.
     */
    class GeneralObjective
      {
    private:
      //! when calculating the misfit the difference is taken to the power of this exponent (d_i - s_i)^FitExponent
      int FitExponent;
      //! the single RMS value
      double RMS;
      //! The levmar library wants the whole misfit vector
      tmisfit Misfit;
      //! The current synthetic data for the levmar algorithm
      tdata SynthData;
      //! Some forward calculations involve writing files, we use ParallelId as a unique identifier for parallel calculations
      std::string ParallelId;
    protected:
      double CalcMisfit(const double measured, const double predicted,
          const double measerror, const double errorlevel, const int index)
      {
        const double absolutemin = 1e-6;
        double currvalue = std::abs(measured - predicted);
        double absoluteerror = std::max(measerror, std::abs(measured * errorlevel));
        currvalue /= std::max(absolutemin, absoluteerror);
        currvalue = std::pow(currvalue, GetFitExponent());
        SetMisfit()(index) = currvalue; //set the misfit vector
        SetSynthData()(index) = measured;
        return currvalue;

      }
      void SetRMS(const double x)
        {
          RMS = x;
        }
      //! Only derived classes can write access the Misfit
      tmisfit &SetMisfit()
        {
          return Misfit;
        }
      void SetMisfit(const tmisfit &LocalMisfit)
        {
          Misfit = LocalMisfit;
        }
      //! Only derived classes can write access the Synthetic data
      tdata &SetSynthData()
        {
          return SynthData;
        }
      ;
      void SetSynthData(const tdata &LocalSynthData)
        {
          SynthData = LocalSynthData;
        }
    public:
      //! Set the Fit exponent
      void SetFitExponent(const int x)
        {
          FitExponent = x;
        }
      //! Get the Fit exponent
      int GetFitExponent()
        {
          return FitExponent;
        }
      //! Get the current RMS
      double GetRMS()
        {
          return RMS;
        }
      //! Derived classes need to read the ParallelId for their forward calculations
      const std::string &GetParallelID()
        {
          return ParallelId;
        }
      //! We need to set the parallel ID outside the Objective function object
      void SetParallelID(const std::string &s)
        {
          ParallelId = s;
        }
      //! Return the misfit vector
      const tmisfit &GetMisfit()
        {
          return Misfit;
        }
      //! Return the current synthetic data
      const tdata &GetSynthData()
        {
          return SynthData;
        }
      //! We need clone and create for building an array of derived objects, see FAQ lite 20.8, the return type depends on the derived class
      virtual GeneralObjective *clone() const = 0;
      //! Some operations cannot be done in parallel, these are done before
      virtual void PreParallel(const ttranscribed &member);
      //! Some operations cannot be done in parallel, these are done after, returns the misfit value
      virtual double PostParallel(const ttranscribed &member) = 0;
      //! The core performance calculation, has to be safe to be done in parallel
      virtual void SafeParallel(const ttranscribed &member);
      //! For serial execution CalcPerformance calls the three Parallel functions for more convenient use
      double CalcPerformance(const ttranscribed &member)
      {
        PreParallel(member);
        SafeParallel(member);
        return PostParallel(member);
      }

      GeneralObjective() :
          FitExponent(2), RMS(0.0), ParallelId("single")
          {
          }
      GeneralObjective(const GeneralObjective &Old) :
          FitExponent(Old.FitExponent), RMS(Old.RMS), Misfit(Old.Misfit),
              SynthData(Old.SynthData), ParallelId(Old.ParallelId)
          {
          }
      GeneralObjective &operator=(const GeneralObjective &source)
      {
        if (this != &source)
          {
            FitExponent = source.FitExponent;
            RMS = source.RMS;
            Misfit = source.Misfit;
            SynthData = source.SynthData;
            ParallelId = source.ParallelId;
          }
        return *this;
      }

      virtual ~GeneralObjective();
      };
  /* @} */
  }
#endif // CGENERALOBJECTIVE_H
