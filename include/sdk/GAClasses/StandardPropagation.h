#ifndef CSTANDARDPROPAGATION_H
#define CSTANDARDPROPAGATION_H

#include "GeneralPropagation.h"
#include <algorithm>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

using namespace std;
namespace ublas = boost::numeric::ublas;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! This is the standard propagation class that generates a new population from the old one
    /*! This class implements the standard propagation schemes for genetic algorithms, selection,
     * crossover and mutation. Each of these steps is performed by a class that we can choose
     * in the constructor.
     */
    class StandardPropagation: public GeneralPropagation
      {
    public:
      virtual void NextGeneration()
        {
          const int popsize = Population->GetPopulation().size1();
          const int genesize = Population->GetPopulation().size2();
          tpopulation NewPopulation(popsize, genesize);

          //first we initialize the selection object so that
          //it has the right probabilities etc.
          Select->Init();
          //we go through the whole population
          //because we go in pairs we have to treat the last elements specially
          for (int i = 0; i < popsize - 1; i += 2)
            {
              //select a "father" and a "mother" that will produce twins
              const int fatherindex = Select->GetOne();
              const int motherindex = Select->GetOne();
              //first take a local copy to work on
              tpopmember Son(ublas::row(Population->GetPopulation(), fatherindex));
              tpopmember Daughter(ublas::row(Population->GetPopulation(), motherindex));
              //then we do mutation and crossover
              Crossover(Son, Daughter);
              Mutation(Son);
              Mutation(Daughter);
              //then we assign to the new population
              ublas::row(NewPopulation, i) = Son;
              ublas::row(NewPopulation, i + 1) = Daughter;
            }
          //if we have an odd population sixze and therefore an extra member
          if ((popsize % 2) != 0)
            {
              //we just have a father that replicates and maybe mutates
              const int fatherindex = Select->GetOne();
              tpopmember Son(ublas::row(Population->GetPopulation(), fatherindex));
              Mutation(Son);
              ublas::row(NewPopulation, popsize - 1) = Son;
            }
          //The new population becomes the "main" population
          Population->SetPopulation(NewPopulation);
        }
      //! The constructor takes pointers to various base classes that configure the behaviour of the selection process.
      /*! This class is basically just a skeleton that uses the objects that implement Selection, Crossover and Mutation
       * in the right order.
       * @param LocalSelect A pointer to an object that implements a selection scheme for the genetic algorithm
       * @param LocalPopulation A pointer to a population object
       * @param LocalRandom A pointer to a random number generator
       */
      StandardPropagation(GeneralSelect* const LocalSelect,
          GeneralPopulation* const LocalPopulation,
          GeneralRNG* const LocalRandom) :
          GeneralPropagation(LocalSelect, LocalPopulation, LocalRandom)
          {
          }
      virtual ~StandardPropagation();
      };
  /* @} */
  }
#endif // CSTANDARDPROPAGATION_H
