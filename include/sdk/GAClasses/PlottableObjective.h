#ifndef PLOTTABLEOBJECTIVE_H_
#define PLOTTABLEOBJECTIVE_H_
#include "GeneralObjective.h"

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! This only adds a few plotting functions to GeneralObjective to define a common interface
    class PlottableObjective: public GeneralObjective
      {
    public:
      //! write the current model to a file
      virtual void WriteModel(const std::string &filename)
        {
        }
      //! write the current model for plotting to a file
      virtual void WritePlot(const std::string &filename)
        {
        }
      //! Write current data to a file
      virtual void WriteData(const std::string &filename)
        {
        }
      PlottableObjective();
      PlottableObjective(const PlottableObjective &Old) :
        GeneralObjective(Old)
        {
        }
      PlottableObjective& operator=(const PlottableObjective& source)
      {
        if (this == &source)
          return *this;

        GeneralObjective::operator=(source);
        return *this;

      }
      virtual ~PlottableObjective();
      };
  /* @} */
  }
#endif /*PLOTTABLEOBJECTIVE_H_*/
