#ifndef CSTANDARDPOPULATION_H
#define CSTANDARDPOPULATION_H

#include "GeneralPopulation.h"
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! A population that is encoded as a simple binary string
    class BinaryPopulation: public GeneralPopulation
      {
    private:
      GeneralRNG &Random;
    public:
      virtual void InitPop();
    {
      const size_t popsize = Population.size1();
      const size_t genesize = Population.size2();
      for (size_t i = 0; i < popsize; ++i)
        for (size_t j = 0; j < genesize; ++j)
          Population(i, j) = (Random.GetNumber() > 0.5);
    }
      BinaryPopulation(const int popsize, const int genesize,
          GeneralRNG &LocalRandom, const bool init = false);
      virtual ~BinaryPopulation();
      using GeneralPopulation::operator=;
      virtual BinaryPopulation& operator=(const BinaryPopulation &source);
      };
  /* @} */
  }
#endif // CSTANDARDPOPULATION_H
