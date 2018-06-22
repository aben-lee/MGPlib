#ifndef CGENERALPROPAGATION_H
#define CGENERALPROPAGATION_H
#include "GeneralSelect.h"
#include "GeneralPopulation.h"
#include "GeneralRNG.h"
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! The base class for genetic algorithm propagation methods
    /*! This class defines the common functionality that is necessary
     * to generate a new population from the current generation. The implementation
     * details depend on the type of GA and Population encoding and those classes
     * have to match to do anything useful.
     */
    class GeneralPropagation
      {
    protected:
      virtual void Crossover(tpopmember &father, tpopmember &mother)
        {
          if (Random->GetNumber() < CrossoverProb)
            {
              tpopmember tempstore(father);
              int crosspoint = Random->GetNumber(father.size() - 2) + 1;
              //cout << "Crosspoint: " << crosspoint << endl;
              copy(mother.begin() + crosspoint, mother.end(), father.begin()
                  + crosspoint);
              copy(tempstore.begin() + crosspoint, tempstore.end(),
                  mother.begin() + crosspoint);
            }
        }
      virtual void Mutation(tpopmember &child)
        {
          for (unsigned int i = 0; i < child.size(); ++i)
            {
              if (Random->GetNumber() < MutationProb)
                {
                  child(i) = !(child(i));
                }

            }
        }
      GeneralSelect* const Select;
      GeneralPopulation* const Population;
      GeneralRNG* const Random;
      double MutationProb;
      double CrossoverProb;
    public:
      virtual void NextGeneration() = 0;
      void SetParams(const double mutation, const double crossover)
        {
          MutationProb = mutation;
          CrossoverProb = crossover;
        }
      ;
      GeneralPropagation(GeneralSelect* const LocalSelect,
          GeneralPopulation* const LocalPopulation,
          GeneralRNG* const LocalRandom):
          Select(LocalSelect), Population(LocalPopulation), Random(LocalRandom)
          {
            MutationProb = 0.001;
            CrossoverProb = 0.5;
          }
      virtual ~GeneralPropagation();
      GeneralPropagation(GeneralPropagation &Old):
          Select(Old.Select), Population(Old.Population), Random(Old.Random)
          {
            MutationProb = Old.MutationProb;
            CrossoverProb = Old.CrossoverProb;
          }
      };
  /* @} */
  }
#endif // CGENERALPROPAGATION_H
