#ifndef CANNEALINGGA_H
#define CANNEALINGGA_H
#include <vector>
#include "GeneralGA.h"
#include "VecMat.h"
#include <cmath>

#include "miscfunc.h"

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;
using namespace gplib;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! AnnealingGA implements a genetic algorithm with an annealing style objective function
    /*! For the first AnnealingGeneration iterations the objective function is kept constant
     * after that the misfit is stretched  with an exponential annealing function  to focus on the minimum
     */
    class AnnealingGA: public GeneralGA
      {
    private:
      //! The initial "Temperature" for the Annealing function
      double InitTemperature;
      //! Before AnnealingGeneration iterations the objective function stays constant
      int AnnealingGeneration;
      //! The ratio by which the temperature is decreased
      double AnnealingRatio;
    protected:
      //! The implementation of Elitism for the AnnealingGA, in this case this function has no effect
      void virtual Elitism(const int iterationnumber);
    public:
      //! The index of the best population member
      int GetBestIndex()
      {
        return distance(Population->GetProbabilities().begin(), max_element(
            Population->GetProbabilities().begin(),
            Population->GetProbabilities().end()));
      }
      //! Set the parameters for the annealing process
      void SetParams(const double InitT, const int AnnealG,
          const double AnnealR)
      {
          InitTemperature = InitT;
          AnnealingGeneration = AnnealG;
          AnnealingRatio = AnnealR;
      }
      //! How many best models exist in this iteration, for this GA it is always 1
      unsigned int virtual GetNBestmodels()
        {
          return distance(Population->GetProbabilities().begin(), max_element(
              Population->GetProbabilities().begin(),
              Population->GetProbabilities().end()));
        } // there is one best model in each iteration
      //! Return the vector containing the best indices, here it has always one component equal to GetBestIndex
      std::vector<int> virtual GetBestModelIndices()
        {
          return std::vector<int>(1, GetBestIndex());
        }
      //! Calculate the selection probabilities given the iterationnumber, misfit and population to store the results
      void virtual CalcProbabilities(const int iterationnumber,
          gplib::rmat &LocalMisFit, GeneralPopulation &LocalPopulation)
      {
        double sum = 0;
        const int popsize = LocalPopulation.GetPopsize();
        double T = 1.0;
        gplib::rvec CurrentMisFit;
        tprobabilityv Probabilities(popsize);
        // The temperature depends on the iteration
        if (iterationnumber < AnnealingGeneration)
          T = InitTemperature;
        else
          T = InitTemperature / AnnealingRatio;
        // for all members of the population
        for (int i = 0; i < popsize; ++i)
          {
            CurrentMisFit = column(LocalMisFit, i); //Get the misfit vector of the current member
            Probabilities(i) = exp(-ublas::sum(CurrentMisFit) / T); //apply the annealing scheme to the summed misfits
            sum += Probabilities(i); // add all misfit values
          }
        const double factor = 1. / sum;
        for (int i = 0; i < popsize; ++i)
          Probabilities(i) *= factor;
        LocalPopulation.SetProbabilities(Probabilities);
      }
      //! The constructor only passes on the parameters to GeneralGA
      AnnealingGA(GeneralPropagation* const LocalPropagation,
          GeneralPopulation* const LocalPopulation,
          GeneralTranscribe* const LocalTranscribe,
          const tObjectiveVector &IndObjective, const int nthreads = 1):
          GeneralGA(LocalPropagation, LocalPopulation, LocalTranscribe,
              IndObjective, nthreads), InitTemperature(1.0),
              AnnealingGeneration(1), AnnealingRatio(1.0)
          {
          }
      virtual ~AnnealingGA();
      };
  /* @} */
  }
#endif // CANNEALINGGA_H
