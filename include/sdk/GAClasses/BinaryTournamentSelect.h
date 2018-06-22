#ifndef CBINARYTOURNAMENTSELECT_H_
#define CBINARYTOURNAMENTSELECT_H_

#include "GeneralSelect.h"
#include "GeneralRNG.h"
#include <cmath>
#include "BinaryTranscribe.h"
#include "FatalException.h"
#include "NumUtil.h"
#include <iostream>
#include <algorithm> // for swap
using namespace std;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! Implements binary tournament selection for genetic algorithms
    class BinaryTournamentSelect: public GeneralSelect
      {
    private:
      //! The number of members that have been selected because of the crowding distance, purely for monitoring
      size_t distancecount;
      //! Storage for shuffled indices of the population, set up during DoInit and used to get pairs of member in DoGetOne
      std::vector<unsigned int> PopulationIndex;
      //! Local storage for the probabilities of the population
      tprobabilityv localprobabilities;
      //! Local storage for the crowding distance
      tcrowddistv localdistances;
      //! The random number generator to shuffle the population
      GeneralRNG &Random;
      //! Pointer to a function that returns the probabilities of the population
      tProbabilityFunction ProbabilityFunction;
      //! Pointer to a function that returns the crowding distances of the population
      tDistanceFunction DistanceFunction;
      //! The current index within the population
      int ReturnIndex;
      //! Initialize PopulationIndex and the local storage fields
      virtual void DoInit()
      {
        if (ProbabilityFunction().size() != DistanceFunction().size())
          throw FatalException(
              "Probabilities and Crowding distances do not have the same size !");
        //Get Probabiliteis and crowding distances
        localprobabilities = ProbabilityFunction();
        localdistances = DistanceFunction();
        const size_t popsize = localdistances.size();
        PopulationIndex.assign(popsize * 2, 0); // we need every member index twice
        for (size_t i = 0; i < popsize; ++i)
          {
            PopulationIndex.at(i) = i;
            PopulationIndex.at(i + popsize) = i;
          }
        for (size_t i = 0; i < popsize; ++i)//shuffle the indices
          {
            int CurrentIndex = Random.GetNumber(popsize - i); //select an index for the first half
            swap(PopulationIndex.at(popsize - i - 1), PopulationIndex.at(
                CurrentIndex)); //swap indices
            CurrentIndex = Random.GetNumber(popsize - i); //generate a new index
            swap(PopulationIndex.at(2 * popsize - i - 1), PopulationIndex.at(
                popsize + CurrentIndex)); //swap indices in the secondhalf
          }
        ReturnIndex = 0;
      }
      //! Return the index to a population member
      virtual size_t DoGetOne()
      {
        const double tolerance = 1e-5;
        //get two indices from the randomized PopulationIndex
        const int fatherindex = PopulationIndex.at(ReturnIndex);
        const int motherindex = PopulationIndex.at(ReturnIndex + 1);
        //increase index for next call
        ReturnIndex += 2;
        //compare within numerical precision
        const int comparison = fcmp(localprobabilities(fatherindex),
            localprobabilities(motherindex), tolerance);
        switch (comparison)
          {
        case 1:
          return fatherindex; //father has higher fitness
        case -1:
          return motherindex; //mother has higher fitness
        case 0:
          distancecount++; //have same fitness, decision based on crowding distance
          if (localdistances(fatherindex) >= localdistances(motherindex))
            return fatherindex;
          else
            return motherindex;
        default:
          throw FatalException(
              "Something went very wrong in CBinaryTournamentSelect::GetOne");
          }
      }
    public:
      //! The constructor requires a random number generator and access functions for probabilities and crowding distances
      BinaryTournamentSelect(GeneralRNG &LocalRandom,
          tProbabilityFunction myPF, tDistanceFunction myDF):
          distancecount(0), Random(LocalRandom), ProbabilityFunction(myPF),
              DistanceFunction(myDF), ReturnIndex(0)
          {

          }
      virtual ~BinaryTournamentSelect()
      {
        cout << "Distance Count: " << distancecount << endl;
      }

      };
  /* @} */
  }
#endif /*CBINARYTOURNAMENTSELECT_H_*/
