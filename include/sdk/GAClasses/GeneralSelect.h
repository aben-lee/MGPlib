#ifndef CGENERALSELECT_H
#define CGENERALSELECT_H
#include "gentypes.h"
#include "FatalException.h"
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //!GeneralSelect is the abstract base class for any selection mechanism in genetic algorithms
    /*!GeneralSelect defines to abstract functions: Init and GetOne. Init has to be called once per iteration
     * and sets all the necessary parameters depending on probabilities and crowding distance
     * GetOne then returns the index of a selected population member and is called every time a population
     * member has to be selected by a selection operator.
     * There is no default implementation ! */

    class GeneralSelect
      {
    private:
      bool initialized;
      //! The abstract definition of the Init function, has to overriden
      virtual void DoInit()= 0;
      //! The abstract definition of GetOne, has to be overriden
      virtual size_t DoGetOne()=0;
    public:
      void Init()
        {
          DoInit();
          initialized = true;
        }
      size_t GetOne()
      {
        if (!initialized)
          throw FatalException(
              "Trying to use Select::GetOne without initializing !");
        return DoGetOne();
      }
      GeneralSelect();
      virtual ~GeneralSelect();
      };
  /* @} */
  }
#endif // CGENERALSELECT_H
