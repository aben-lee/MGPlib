#ifndef CSIMPLESELECT_H
#define CSIMPLESELECT_H

#include "GeneralSelect.h"
#include "GeneralRNG.h"
#include <boost/function.hpp>
#include <cmath>
#include <iostream>
using namespace std;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! This is a relatively simple selection scheme for the genetic algorithms
    /*! This class implements a relatively simple, but efficient selection scheme.
     * Each member is assigned the expected count from the probabilities returned by
     * the Probability function rounded to full integers. The difference between the
     * assigned count and the expected count without rounding is used as a probability
     * to have an additional member in the new population.
     */
    class SimpleSelect: public GeneralSelect
      {
    private:
      //! The vector of indices for the new population member
      tindexv indices;
      //! The random number generator
      GeneralRNG &Random;
      int remain;
      //! A pointer to a function that returns a vector of probabilities
      tProbabilityFunction ProbabilityFunction;
      virtual void DoInit()
      {
        const tprobabilityv probabilities = ProbabilityFunction();
        const size_t popsize = probabilities.size();
        size_t currentindex = 0;

        std::vector<double> fraction(popsize, 0);
        indices.assign(popsize, 0);
        remain = popsize;
        //go through the whole population
        for (size_t i = 0; i < popsize; ++i)
          {
            //how many members can we expect in the new population based
            //on the probabilities
            const double expected = probabilities(i) * popsize;
            //we always assign the expected number rounded down
            //to the new population
            int assign = int(floor(expected));
            //and the save the difference between the rounded
            //and not rounded to determine additional members
            //later
            fraction.at(i) = expected - assign;
            //generate assign times index entries in the index
            //vector that describes the new population
            while (assign > 0)
              {
                --assign;
                indices.at(currentindex) = i;
                ++currentindex;
              }

          }
        //now we determine the remainder of the population
        //based on the difference between expected and assigned
        size_t fractionindex = 0;
        //as long as the population is not full
        while (currentindex < popsize)
          {
            //cycle through the population members
            //and see if we want to include the current member
            if (Random.GetNumber() <= fraction.at(fractionindex))
              {
                indices.at(currentindex) = fractionindex;
                ++currentindex;
                fraction.at(fractionindex) -= 1.0;
              }
            ++fractionindex;
            //when we reached the end of the population, go back to the beginning
            if (fractionindex >= popsize)
              fractionindex -= popsize;
          }
      }
      virtual size_t DoGetOne()
      {
        int pick = Random.GetNumber(remain);
        int result = indices.at(pick);
        // Have to reduce remain before because it starts with popsize but array is 0..popsize-1
        --remain;
        indices.at(pick) = indices.at(remain);
        return (result);
      }
    public:
      //! The constructor needs a random number generator and a function that returns probabilities
      /*! The constructor takes two parameters
       * @param LocalRandom A random number generator based on GeneralRNG
       * @param myPF A pointer to a function that returns a vector with probabilities for each population member
       */
      SimpleSelect(GeneralRNG &LocalRandom, tProbabilityFunction myPF) :
          Random(LocalRandom), ProbabilityFunction(myPF)
          {

          }
      virtual ~SimpleSelect();
      };
  /* @} */
  }
#endif // CSIMPLESELECT_H
