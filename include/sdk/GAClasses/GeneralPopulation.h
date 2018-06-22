#ifndef CGENERALPOPULATION_H
#define CGENERALPOPULATION_H
#include "gentypes.h"
#include "GeneralRNG.h"
#include "FatalException.h"
#include "VecMat.h"
using namespace std;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! The base class for the population of a genetic algorithm, implements storage and access functions
    class GeneralPopulation
      {
    private:
      //! The population of the last iteration for elitism
      tpopulation OldPopulation;
      //! Did we store the last population
      bool OldStored;
      //! The selection probabilities for each population member
      tprobabilityv Probabilities;
      //! The crowding distance for each population member
      tcrowddistv CrowdingDistances;
    protected:
      //! Change the population size
      void ResizePop(const int popsize, const int genesize)
      {
        OldPopulation.resize(popsize, genesize);
        Population.resize(popsize, genesize);
        Probabilities.resize(popsize);
        CrowdingDistances.resize(popsize);
      }
      //! The population of the current iteration
      tpopulation Population;
    public:
      virtual void InitPop()
        {
        }
      ;
      const tpopulation& GetOldPopulation() const
        {
          if (OldStored)
            return OldPopulation;
          else
            throw FatalException("Old Population has not been stored");
        }
      ;
      void StoreOldPopulation()
        {
          OldPopulation = Population;
          OldStored = true;
        }
      ;
      void PrintPopulation(std::ostream &output) const
      {
        const int popsize = Population.size1();
        const int genesize = Population.size2();
        int i, j;
        output << popsize << " " << genesize << endl;
        for (i = 0; i < popsize; ++i)
          {
            for (j = 0; j < genesize; ++j)
              output << Population(i, j) << " ";
            output << endl;
          }
      }
      void ReadPopulation(std::istream &input)
      {
        unsigned int popsize, genesize, dummy;
        unsigned int i, j;

        input >> popsize >> genesize;
        ResizePop(popsize, genesize);
        for (i = 0; i < popsize; ++i)
          {
            for (j = 0; j < genesize; ++j)
              {
                input >> dummy;
                Population(i, j) = (dummy == 1);
              }
          }
      }
      void PrintProbabilities(std::ostream &output) const
      {
        for (unsigned int i = 0; i < Probabilities.size(); ++i)
          {
            output << Probabilities(i) << " ";
          }
        output << endl;
      }

      void PrintDistances(std::ostream &output) const
      {
        for (unsigned int i = 0; i < CrowdingDistances.size(); ++i)
          {
            output << CrowdingDistances(i) << " ";
          }
        output << endl;
      }
      const tpopulation& GetPopulation() const
        {
          return Population;
        }
      ;
      const tprobabilityv& GetProbabilities() const
        {
          return Probabilities;
        }
      ;
      const tcrowddistv& GetCrowdingDistances() const
        {
          return CrowdingDistances;
        }
      ;
      void SetPopulation(const tpopulation &LocalPop)
        {
          OldPopulation = Population;
          Population = LocalPop;
          OldStored = true;
        }
      ;
      void SetProbabilities(const tprobabilityv &LocalProb)
        {
          Probabilities = LocalProb;
        }
      ;
      void SetCrowdingDistances(const tcrowddistv &LocalDist)
        {
          CrowdingDistances = LocalDist;
        }
      ;
      int GetPopsize() const
        {
          return Population.size1();
        }
      ;
      int GetGenesize() const
        {
          return Population.size2();
        }
      ;
      GeneralPopulation(const int popsize, const int genesize) :
          Probabilities(popsize), CrowdingDistances(popsize), Population(popsize,
              genesize)
          {
            OldStored = false;
          }
      GeneralPopulation(GeneralPopulation &Old):
          OldPopulation(Old.OldPopulation), Probabilities(Old.Probabilities),
              CrowdingDistances(Old.CrowdingDistances), Population(Old.Population)
          {
            OldStored = Old.OldStored;
          }
      //! Merge two populations in a new population object
      GeneralPopulation(const tpopulation &FirstHalf,
          const tpopulation &SecondHalf):
          OldPopulation(FirstHalf.size1() + SecondHalf.size1(), FirstHalf.size2()),
              Probabilities(FirstHalf.size1() + SecondHalf.size1()),
              CrowdingDistances(FirstHalf.size1() + SecondHalf.size1()),
              Population(FirstHalf.size1() + SecondHalf.size1(), FirstHalf.size2())
          {
            OldStored = false;
            ublas::matrix_range<tpopulation> PopFirstHalf(Population, ublas::range(
                0, FirstHalf.size1()), ublas::range(0, FirstHalf.size2()));
            ublas::matrix_range<tpopulation> PopSecondHalf(Population,
                ublas::range(FirstHalf.size1(), FirstHalf.size1()
                    + SecondHalf.size1()), ublas::range(0, FirstHalf.size2()));
            PopFirstHalf = FirstHalf;
            PopSecondHalf = SecondHalf;
          }

      virtual GeneralPopulation& operator=(const GeneralPopulation &source)
      {
        if (this != &source)
          {
            OldPopulation = source.OldPopulation;
            Population = source.Population;
            Probabilities = source.Probabilities;
            CrowdingDistances = source.CrowdingDistances;
          }
        return *this;
      }
      virtual ~GeneralPopulation();
      };
  /* @} */
  }
#endif // CGENERALPOPULATION_H
