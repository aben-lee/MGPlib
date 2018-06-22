#ifndef CPARETOGA_H
#define CPARETOGA_H

#include "GeneralGA.h"
#include <iostream>
#include <vector>
#include "VecMat.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include "NumUtil.h"
#include <boost/algorithm/minmax_element.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! Implements a genetic algorithm based on the concept of pareto-optimality, best suited for multi-objective problems
    /*! The class ParetoGA implements a variant of NSGA-II by Deb et al.:
     * Deb, K., Pratap. A, Agarwal, S., and Meyarivan, T. (2002). A fast and elitist multi-objective genetic algorithm: NSGA-II. IEEE Transaction on Evolutionary Computation, 6(2), 181-197.
     */
class dominates
  {
public:
  bool operator()(const gplib::rvec &fit1, const gplib::rvec &fit2) const
    {
      typedef vector<double>::const_iterator tit;
      bool smaller = false;
      const size_t length = fit2.size();
      for (size_t i = 0; i < length; ++i)
        {
          if (fit1(i) > fit2(i))
            return false;
          if (fit1(i) < fit2(i))
            smaller = true;
        }
      return smaller;
    }
  };
    class ParetoGA: public GeneralGA
      {
    private:
      typedef ublas::matrix_row<gplib::rmat>::const_iterator tMisfitIterator;
      void CalcCrowdingDistance(gplib::rmat &LocalMisFit,
          GeneralPopulation &LocalPopulation)
      {
        const double NearInfinity = 1e50;
        const double tolerance = 1e-10;
        const unsigned int popsize = LocalPopulation.GetPopsize();

        tcrowddistv CrowdingDistances(popsize);
        for (unsigned int i = 0; i < popsize; ++i)
          CrowdingDistances(i) = 0;
        for (unsigned int i = 0; i < nobjective; ++i)
          {
            if (fcmp(GetWeights().at(i), 0, tolerance) != 0)
              {
                pair<tMisfitIterator, tMisfitIterator> MinMax =
                    boost::minmax_element(ublas::row(LocalMisFit, i).begin(),
                        ublas::row(LocalMisFit, i).end());
                double normalize = 1;
                if (fcmp(*(MinMax.second) - *(MinMax.first), 0, tolerance)
                    != 0) // if minimum not equal maximum
                  normalize = *(MinMax.second) - *(MinMax.first);
                for (unsigned int j = 0; j < Ranks.size(); ++j)
                  {
                    tIndexMap IndexMap;
                    for (unsigned int k = 0; k < Ranks.at(j).size(); ++k)
                      {
                        IndexMap.insert(make_pair(LocalMisFit(i,
                            Ranks.at(j).at(k)), Ranks.at(j).at(k)));
                      }
                    tIndexMap::iterator end = --IndexMap.end();
                    tIndexMap::iterator pos = IndexMap.begin();
                    CrowdingDistances(pos->second) = NearInfinity; // set the crowding distance very large
                    if (pos != end)
                      {
                        CrowdingDistances(end->second) = NearInfinity; // for first and last element
                        tIndexMap::iterator previous = IndexMap.begin(); //the previous element is the first element
                        tIndexMap::iterator next = pos; // we start at the second, not the first element
                        advance(pos, 1);
                        advance(next, 2);
                        for (; pos != end; pos++)
                          {
                            CrowdingDistances(pos->second) += (next->first
                                - previous->first) / normalize;
                            ++previous;
                            ++next;
                          }
                      }
                  }
              }
          }
        LocalPopulation.SetCrowdingDistances(CrowdingDistances);
      }
      std::vector<std::vector<int> > Ranks;
      int MaxRanks;
    protected:
      //! The function Elitism ensures that the best models are preserved after mutation and crossover
      void virtual Elitism(const int iterationnumber)
      {
        const unsigned int popsize = Population->GetPopsize();
        const unsigned int ngenes = Population->GetGenesize();
        GeneralPopulation IntermediatePop(Population->GetPopulation(),
            Population->GetOldPopulation());
        gplib::rmat IntermediateMisFit(nobjective, 2 * popsize);
        ublas::matrix_range<gplib::rmat> MisFitFirstHalf(IntermediateMisFit,
            ublas::range(0, nobjective), ublas::range(0, popsize));
        ublas::matrix_range<gplib::rmat> MisFitSecondHalf(IntermediateMisFit,
            ublas::range(0, nobjective), ublas::range(popsize, 2 * popsize));
        MisFitFirstHalf = MisFit;
        MisFitSecondHalf = OldMisFit;
        CalcProbabilities(iterationnumber, IntermediateMisFit, IntermediatePop);

        unsigned int included = 0;
        unsigned int currentrank = 0;
        tpopulation Newpopulation(popsize, ngenes);
        while (Ranks.at(currentrank).size() <= (popsize - included)) // as long as we can fit the current rank into the population
          {
            for (unsigned int j = 0; j < Ranks.at(currentrank).size(); ++j)
              {
                ublas::row(Newpopulation, included) = ublas::row(
                    IntermediatePop.GetPopulation(),
                    Ranks.at(currentrank).at(j));
                ++included;
              }
            ++currentrank;
          }
        //Now we have to fill up the rest sorted by distance
        tIndexMap IndexMap; //sorts the current rank by crowding distance and stores the associated index
        for (unsigned int j = 0; j < Ranks.at(currentrank).size(); ++j)
          IndexMap.insert(make_pair(IntermediatePop.GetCrowdingDistances()(
              Ranks.at(currentrank).at(j)), Ranks.at(currentrank).at(j)));
        tIndexMap::iterator pos = IndexMap.begin();
        advance(pos, Ranks.at(currentrank).size() - (popsize - included)); // we have to take the last members with the biggest distance
        while (pos != IndexMap.end())
          {
            ublas::row(Newpopulation, included) = ublas::row(
                IntermediatePop.GetPopulation(), pos->second);
            ++included;
            ++pos;
          }
        Population->SetPopulation(Newpopulation);
      }

    void ParetoGA::PrintRanks(std::ostream &output)
      {
        const unsigned int nobj = MisFit.size1();
        const unsigned int nranks = Ranks.size();
        for (unsigned int i = 0; i < nranks; ++i)
          {
            output << "Rank: " << i << endl;
            for (unsigned int j = 0; j < Ranks.at(i).size(); ++j)
              {
                for (unsigned int k = 0; k < nobj; ++k)
                  output << MisFit(k, Ranks.at(i).at(j)) << " ";
                output << endl;
              }
            output << endl;
          }
        output << endl;
      }

    public:
      //! Return the size of the pareto-optimal front
      unsigned int virtual GetNBestmodels()
        {
          return Ranks.front().size();
        }
      //! Get the indices of the models within the Pareto front
      std::vector<int> virtual GetBestModelIndices()
        {
          return Ranks.front();
        }
      //! Calculate the probabilities of reproduction by ranking the population
      void virtual CalcProbabilities(const int iterationnumber,
          gplib::rmat &LocalMisFit, GeneralPopulation &LocalPopulation)
      {
        const unsigned int size = LocalPopulation.GetPopsize();
        gplib::rvec currmisfit(nobjective), compmisfit(nobjective); //local storage
        vector<int> Indices;
        unsigned int rankedelements = 0;

        vector<int> CurrRanks; //the indices of the members in the current rank
        unsigned int i, j, k = 0;
        vector<bool> dominated(size, false); //for each member whether it is dominated
        unsigned int maxindex = size; //the maximum index in the beginning is the population size

        if (!Ranks.empty()) //empty old storage
          Ranks.clear();
        Indices.reserve(size); //intialize population index
        for (i = 0; i < size; ++i)
          Indices.push_back(i);
        while (rankedelements < size) // while we haven't ranked everything
          {
            CurrRanks.clear(); //empty the current rank
            for (i = 0; i < maxindex; ++i) // for all population members that haven't been ranked
              {
                for (j = 0; j < nobjective; ++j) //get the misfit values
                  currmisfit(j) = LocalMisFit(j, Indices.at(i));
                j = 0;
                dominated.at(i) = false; // assume it is not dominated
                while (!dominated.at(i) && (j < maxindex)) //while we haven't found it dominated or reached the maximum index
                  {
                    for (k = 0; k < nobjective; ++k)
                      compmisfit(k) = LocalMisFit(k, Indices.at(j)); //get the misfit values for comparison
                    if (dominates()(compmisfit, currmisfit)) //if current member is dominated
                      {
                        dominated.at(i) = true; // set domination property in vector
                      }
                    ++j;
                  }
              } //end for all population members that haven't been ranked

            for (i = 0; i < maxindex; ++i) //remove non dominated members from comparison
              {
                if (!dominated.at(i)) //if the current member is not dominated
                  {
                    CurrRanks.push_back(Indices.at(i)); // add it to the non-dominated front
                    Indices.at(i) = Indices.at(maxindex - 1); //copy the last active index in the current position
                    dominated.at(i) = dominated.at(maxindex - 1); // same with domination property
                    ++rankedelements;//we have now ranked one element
                    --maxindex; // and have one less to go, the previous last index is now copied
                    --i; // we have to examine the element in this position again, because we copied
                  }
              }
            Ranks.push_back(CurrRanks); //add current rank to overall ranks
          } //now we have ranked everything
        const unsigned int nranks = Ranks.size();
        cout << "NRanks : " << nranks << endl;
        double sum = 0.0; //now we calculate the probabilities
        double prob = 0.0;
        tprobabilityv Probabilities(LocalPopulation.GetPopsize()); //allocate an array
        for (i = 0; i < nranks; ++i) //for all ranks
          {
            for (j = 0; j < Ranks.at(i).size(); ++j) //and members in the rank
              {
                prob = nranks - i; //high rank is low probability
                Probabilities(Ranks.at(i).at(j)) = prob; //Assign to the right member
                sum += prob; //sum for normalization
              }
          }
        Probabilities /= sum; //make values probabilities
        LocalPopulation.SetProbabilities(Probabilities); //assign to population object

        CalcCrowdingDistance(LocalMisFit, LocalPopulation);
      }
      //! Write the population by ranks to the stream output
      void PrintRanks(std::ostream &output);
      //! Write the models in the pareto-optimal front to stream output
      void PrintFront(std::ostream &output)
      {
        const unsigned int nobj = MisFit.size1();
        const unsigned int frontsize = Ranks.front().size();
        for (unsigned int i = 0; i < frontsize; ++i)
          {
            for (unsigned int j = 0; j < nobj; ++j)
              output << MisFit(j, Ranks.front().at(i)) << " ";
            output << endl;
          }
        output << endl << endl;
      }

      //! The constructor needs other classes that determine the behaviour of the GA
      ParetoGA(GeneralPropagation* const LocalPropagation,
          GeneralPopulation* const LocalPopulation,
          GeneralTranscribe* const LocalTranscribe,
          const tObjectiveVector &IndObjective, const int nthreads = 1) :
        GeneralGA(LocalPropagation, LocalPopulation, LocalTranscribe,
            IndObjective, nthreads)
        {
        }
      virtual ~ParetoGA();
      };
  /* @} */
  }
#endif // CPARETOGA_H
