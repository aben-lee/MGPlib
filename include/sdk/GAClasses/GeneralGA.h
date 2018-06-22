#ifndef CGENERALGA_H
#define CGENERALGA_H

#include "GeneralPropagation.h"
#include "GeneralObjective.h"
#include "GeneralPopulation.h"
#include "GeneralTranscribe.h"
#include "GeneralRNG.h"
#include "GeneralSelect.h"
#include "UniquePop.h"
#include <vector>
#include <fstream>
#include "VecMat.h"
#include <boost/shared_ptr.hpp>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <map>
#include "statutils.h"
#include "VecMat.h"
#include "FatalException.h"
#include <boost/bind.hpp>
#include <algorithm>
#include <cassert>
#include <unistd.h>
#ifdef _OPENMP
#include <omp.h>
#endif
using namespace std;
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! General genetic algorithm class
    /*! GeneralGA implements the functionality that is common to all genetic algorithms
     * it declares a bunch of virtual functions, that are implemented in derived classes and
     * pointers to several other objects that together make up the genetic algorithm
     */
    class GeneralGA
      {
        struct CopyFromPointer
          {
          boost::shared_ptr<GeneralObjective> operator()(boost::shared_ptr<
              GeneralObjective> param)
            {
              return boost::shared_ptr<GeneralObjective>(param->clone());
            }
          };
        struct GenObjective
          {
          GeneralGA::tObjectiveVector operator()(
              const GeneralGA::tObjectiveVector &IndObjective)
            {
              GeneralGA::tObjectiveVector result(IndObjective.size()); //allocate space
              transform(IndObjective.begin(), IndObjective.end(), result.begin(),
                  CopyFromPointer());//copy each objective function into result
              return result;
            }
          };
        std::string MakeParallelID(const int j, const int i,
            const int iterationnumber, const int Programnum)
          {
            ostringstream filename;
            filename << "j" << j << "i" << i << "g" << iterationnumber << "p"
                << Programnum;
            return filename.str();
          }

    public:
      //! We provide some typedefs that are used in other parts as well
      typedef std::vector<gplib::rvec> tparamvector;
      typedef std::vector<boost::shared_ptr<GeneralObjective> >
          tObjectiveVector;
      typedef std::vector<std::vector<int> > tparamindv;
    private:
      //! Calculate the misfit for all models, this implements the core functionality for misfit calculations
      void CalcMisfit(const int iterationnumber);
      //! The number of threads for parallel calculation, works only with OpenMP
      int Threads;
      //the process ID of the main program, used for file identification
      int Programnum;
      //! The average summed fit
      double CombAvgFit;
      //! The maximum summed fit
      double CombMaxFit;
      //! The minimum summed fit
      double CombMinFit;
      //! Should the GA be elitist, i.e. ensure that the best models are preserved
      bool Elitist;
      //!  Holds the summed Fit for each objective function
      std::vector<double> CombMisFit;
      std::vector<double> AvgFit;
      //! Maximum Fit for each objective function
      std::vector<double> MaxFit;
      //! Minimum Fit for each objective Function
      std::vector<double> MinFit;
      //! The weight for each objective function, the exact meaning will depend on the algorithm, i.e. the derived class
      std::vector<double> Weights;
      //! The object holding one copy of each model vector calculated so far
      UniquePop UniquePopHist;
      //! For each objective function we store the indices of the complete model vector that each objective function needs for its calculations
      tparamindv ParameterIndices;
    protected:
      gplib::rmat OldMisFit;
      //! The number of objective functions we're using
      const unsigned int nobjective;
      //! A matrix holding the numerical model vectors (transcribed from the genes) for each population member
      gplib::rmat Transcribed;
      //! Misfit first index objective function second index population member
      gplib::rmat MisFit;
      //! The vector holding the objective functions
      tObjectiveVector Objective;
      //! A pointer to an object dealing with propagation
      GeneralPropagation* const Propagation;
      //! A pointer to an object holding the population
      GeneralPopulation* const Population;
      //! A pointer to an object translating genes to model vectors
      GeneralTranscribe* const Transcribe;
      //! default implementation does nothing, this can be overriden @see ParetoGA
      void virtual Elitism(const int iterationnumber)
        {
        }
      ;
    public:
      //! Return the weight for each objecive function
      const std::vector<double> &GetWeights()
        {
          return Weights;
        }
      ;
      //! Copy the appropriate parameter values from the transcribed vector for use with the objective functions
      void SetupParams(const ttranscribed &member, tparamvector &params)
      {
        for (unsigned int i = 0; i < nobjective; ++i)
          for (unsigned int j = 0; j < ParameterIndices.at(i).size(); ++j)
            {
              params.at(i)(j) = member(ParameterIndices.at(i).at(j));
            }
      }

      //! Return the average fitness for each objective function
      const std::vector<double> &GetAvgFit()
        {
          return AvgFit;
        }
      ;
      //! Do we want elitist behaviour, effect depends on the GA implementetion in the derived class
      void SetElitist(const bool IsElitist)
        {
          Elitist = IsElitist;
        }
      ;
      //! Set the weights for each objective function
      void SetWeights(const std::vector<double> &LocalWeights)
      {
        if (LocalWeights.size() != Weights.size()) //Weights has been pre allocated based on the number of objective functions
          throw FatalException(
              "Configured number of weights does not match number of objective functions !");
        Weights = LocalWeights;
      }
      //! Configure which parts of the complete parameter vector are used in each objective function
      void SetParameterIndices(const tparamindv &Indices)
      {
        ParameterIndices = Indices;
      }
      //! Print Fitness statistics for each objective function to output
      void PrintFitStat(std::ostream &output)
      {
        for (unsigned int i = 0; i < nobjective; ++i)
          {
            output << MaxFit.at(i) << " " << MinFit.at(i) << " "
                << AvgFit.at(i) << "   ";
          }
        output << CombMaxFit << " " << CombMinFit << " " << CombAvgFit << "   ";
        output << endl << flush;
      }
      //!Print misfit for each member to output
      void PrintMisfit(std::ostream &output)
      {
        const unsigned int isize = MisFit.size1();
        const unsigned int jsize = MisFit.size2();

        for (unsigned int i = 0; i < isize; ++i)
          {
            for (unsigned int j = 0; j < jsize; ++j)
              output << MisFit(i, j) << " ";
            output << endl;
          }
        copy(CombMisFit.begin(), CombMisFit.end(), ostream_iterator<double> (
            output, " "));
        output << endl << endl;
      }
      //!Print transcribed values for each member to output
      void PrintTranscribed(std::ostream &output)
      {
        const unsigned int isize = Transcribed.size1();
        const unsigned int jsize = Transcribed.size2();
        unsigned int i, j;
        for (i = 0; i < isize; ++i)
          {
            for (j = 0; j < jsize; ++j)
              output << Transcribed(i, j) << " ";
            output << endl;
          }
        output << endl << flush;
      }

      //! Print each population member exactly once
      void PrintUniquePop(std::ostream &output)
        {
          UniquePopHist.PrintAll(output);
        }
      ;
      //! Print misfit of the best population members
      void PrintBestMisfit(std::ostream &output)
      {
        std::vector<int> Indices(GetBestModelIndices());
        const unsigned int isize = Indices.size();
        const unsigned int jsize = MisFit.size1();

        for (unsigned int i = 0; i < isize; ++i)
          {
            const int currindex = Indices.at(i);
            for (unsigned int j = 0; j < jsize; ++j)
              output << MisFit(j, currindex) << " ";
            output << endl;
          }
        output << endl << endl;
      }
      //! This has to be implemented in the derived class to return the number of best models
      unsigned int virtual GetNBestmodels() = 0;
      //! Return the indices of the best models
      std::vector<int> virtual GetBestModelIndices() = 0;
      //! Do one iteration of the GA
      void virtual DoIteration(const int iterationnumber, const bool last)
      {
        cout << endl << endl << "Iteration: " << iterationnumber + 1 << endl;
        cout << "Calculating Misfit ...";
        CalcMisfit(iterationnumber);
        cout << " done" << endl << flush;
        //cout << "Before Elitism " << endl;
        //PrintMisfit(cout);
        cout << endl;
        if ((iterationnumber >= 1) && Elitist)
          {
            Elitism(iterationnumber);
          }
        CalcMisfit(iterationnumber)
        {
          int calculatecount = 0;
          int newcount = 0;
          // popsize cannot be unsigned because loop variables for openmp have to be signed
          const int popsize = Population->GetPopsize();
          ublas::vector<bool> AlreadyCalculated(popsize);
          tfitvec fitvec(nobjective);

  #pragma omp parallel for default(shared)
          for (int i = 0; i < popsize; ++i)
            {
              tparamvector LocalParameters(nobjective);
              for (unsigned int k = 0; k < nobjective; ++k)
                {
                  LocalParameters.at(k).resize(ParameterIndices.at(k).size(),
                      false);
                }
              row(Transcribed, i) = Transcribe->GetValues(row(
                  Population->GetPopulation(), i));
              AlreadyCalculated(i) = UniquePopHist.Find(row(Transcribed, i),
                  fitvec);
              if (!AlreadyCalculated(i))
                {
                  SetupParams(row(Transcribed, i), LocalParameters);
                  tObjectiveVector LocalObjective(GenObjective()(Objective));
                  for (unsigned int j = 0; j < nobjective; ++j)
                    {
                      LocalObjective.at(j)->SetParallelID(MakeParallelID(j, i,
                          iterationnumber, Programnum));
                      if (Weights.at(j) != 0)
                        {
  #pragma omp critical
                            {
                              LocalObjective.at(j)->PreParallel(
                                  LocalParameters.at(j));
                            }
                          LocalObjective.at(j)->SafeParallel(
                              LocalParameters.at(j));
  #pragma omp critical
                            {
                              MisFit(j, i) = Weights.at(j)
                                  * LocalObjective.at(j)->PostParallel(
                                      LocalParameters.at(j));
                              CombMisFit.at(i) += MisFit(j, i);
                            }

                        }
                      else
                        {
                          MisFit(j, i) = 0;
                        }
                    }
                  tfitvec fitvector(column(MisFit, i));
  #pragma omp critical
                    {
                      UniquePopHist.Insert(fitvector, ublas::matrix_row<
                          gplib::rmat>(Transcribed, i));
                    }
                  newcount++;
                }
              else // if already calculated
                {
                  column(MisFit, i) = fitvec;
                  CombMisFit.at(i) = ublas::sum(fitvec);
                  calculatecount++;
                }
            }
          cout << "New models: " << newcount << " Re-used models: "
              << calculatecount << endl;
        }// we have to update the misfit after elitism
        //because we cache the misfit values, the cost is low for this
        CalcProbabilities(iterationnumber, MisFit, *Population);
        for (unsigned int i = 0; i < nobjective; ++i) // do some statistics on the misfit

          {
            ublas::matrix_row<gplib::rmat> mr(MisFit, i);
            AvgFit.at(i) = Mean(mr.begin(), mr.end());
            MaxFit.at(i) = *max_element(mr.begin(), mr.end());
            MinFit.at(i) = *min_element(mr.begin(), mr.end());
          }
        CombAvgFit = Mean(CombMisFit.begin(), CombMisFit.end());
        CombMaxFit = *max_element(CombMisFit.begin(), CombMisFit.end());
        CombMinFit = *min_element(CombMisFit.begin(), CombMisFit.end());
        if (!last) // if we're not in the last iteration, we store the last population for elitism

          {
            Population->StoreOldPopulation();
            OldMisFit = MisFit;
            Propagation->NextGeneration();
          }
      }
      //! Calculate the Probabilities
      void virtual CalcProbabilities(const int iterationnumber,
          gplib::rmat &LocalMisFit, GeneralPopulation &LocalPopulation) = 0;
      GeneralGA(GeneralPropagation* const LocalPropagation,
          GeneralPopulation* const LocalPopulation,
          GeneralTranscribe* const LocalTranscribe,
          const tObjectiveVector &IndObjective, const int nthreads = 1)
          :
                CombMisFit(LocalPopulation->GetPopsize()), AvgFit(IndObjective.size()),
                    MaxFit(IndObjective.size()), MinFit(IndObjective.size()), Weights(
                        IndObjective.size(), 1), nobjective(IndObjective.size()),
                    Transcribed(LocalPopulation->GetPopsize(),
                        LocalTranscribe->GetNparams()), MisFit(IndObjective.size(),
                        LocalPopulation->GetPopsize()), Objective(IndObjective),
                    Propagation(LocalPropagation), Population(LocalPopulation),
                    Transcribe(LocalTranscribe)
                {
                  Threads = nthreads;
                  Elitist = true;
                  Programnum = getpid();
                }

      virtual ~GeneralGA();
      };
  /* @} */
  }
#endif // CGENERALGA_H
