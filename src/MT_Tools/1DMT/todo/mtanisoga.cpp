#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>
#include "SimpleSelect.h"
#include "BinaryTournamentSelect.h"
#include "UniformRNG.h"
#include "gentypes.h"
#include "BinaryPopulation.h"
#include "StandardPropagation.h"
#include "GrayTranscribe.h"
#include "AnnealingGA.h"
#include "ParetoGA.h"
#include "Aniso1DMTObjective.h"
#include "PTensor1DMTObjective.h"
#include "MTStation.h"
#include "Adaptors.h"
#include "MTFitSetup.h"
#include "PTensorMTStation.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <complex>
#include "Util.h"
#include "MTAnisoRoughness.h"
#include "MTAnisoGAConf.h"

using namespace std;
using namespace gplib;

enum tgatype
  {
  pareto, anneal
  };
typedef boost::shared_ptr<GeneralObjective> pCGeneralObjective;



void SetupAnnealingGA(boost::shared_ptr<GeneralGA> &GA,
    const MTAnisoGAConf Configuration)
  {
    double InitTemperature = Configuration.inittemp;
    if (Configuration.inittemp < 0)
      {
        double avgcombfit = 0;
        GA->DoIteration(0, false);
        /*for (int i = 0; i < GA->GetAvgFit().size(); ++i)
         avgcombfit += GA->GetAvgFit().at(i);*/
        avgcombfit = accumulate(GA->GetAvgFit().begin(), GA->GetAvgFit().end(),
            0.0);
        InitTemperature = avgcombfit * abs(Configuration.inittemp);
      }
    AnnealingGA *AnnealGA = dynamic_cast<AnnealingGA*> (GA.get());
    AnnealGA->SetParams(InitTemperature, Configuration.annealinggeneration,
        Configuration.coolingratio);
  }

//! Program to invert MT data for 1D anisotropic structure with a genetic algorithm
int main(int argc, char *argv[])
  {
    boost::posix_time::ptime starttime =
        boost::posix_time::microsec_clock::local_time();
    string version = "$Id: mtanisoga.cpp 1849 2010-05-07 11:53:45Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Genetic algorithm to jointly invert MT data for 1D anisotropy"
        << endl;
    cout << "look at mtanisoga.conf for configuration and setup " << endl;
    cout << "The root name of log-files can be overwritten by using " << endl;
    cout << "1dinvga newrootname " << endl;

    MTAnisoGAConf Configuration;

    UniformRNG Random;
    try
      {
        Configuration.GetData("mtanisoga.conf");

        ttranscribed transcribed;
        tgatype GAtype = pareto;

        string outputbase;

        if (argc > 1)
          outputbase = argv[1];
        else
          outputbase = Configuration.outputbase;

        ofstream misfitfile;
        ofstream valuefile;
        ofstream probfile;
        ofstream distancefile;
        ofstream fitstat((outputbase + ".ftst").c_str());
        ofstream uniquepop((outputbase + ".unpop").c_str());
        ofstream rankfile((outputbase + ".rank").c_str());
        ofstream frontfile((outputbase + ".front").c_str());
        ofstream bestfile((outputbase + ".best").c_str());

        if (Configuration.verbose) // in most cases we do not need all of these values
          {
            misfitfile.open((outputbase + ".msft").c_str());
            valuefile.open((outputbase + ".vals").c_str());
            probfile.open((outputbase + ".probs").c_str());
            distancefile.open((outputbase + ".dist").c_str());
          }

        if ((Configuration.thickbase.size() != Configuration.resbase.size())
            || (Configuration.thickbase.size()
                != Configuration.anisobase.size())
            || (Configuration.thickbase.size()
                != Configuration.strikebase.size()))
          {
            cerr << "Configuration of genes is not consistent ! ";
            return 100;
          }
        const int nparam = 4;
        const int genes = 4 * Configuration.thickbase.size();
        const int popsize = Configuration.popsize;
        const int maxgen = Configuration.generations;
        const int paramlength = genes / nparam;
        ttranscribed basevalues(genes);
        ttranscribed stepsizes(genes);
        tsizev genesizes(genes);

        misfitfile << popsize << " " << maxgen << " " << endl;
        valuefile << genes << " " << popsize << " " << maxgen << endl;

        copy(Configuration.resbase.begin(), Configuration.resbase.end(),
            basevalues.begin());
        copy(Configuration.resstep.begin(), Configuration.resstep.end(),
            stepsizes.begin());
        copy(Configuration.ressizes.begin(), Configuration.ressizes.end(),
            genesizes.begin());

        copy(Configuration.thickbase.begin(), Configuration.thickbase.end(),
            basevalues.begin() + paramlength);
        copy(Configuration.thickstep.begin(), Configuration.thickstep.end(),
            stepsizes.begin() + paramlength);
        copy(Configuration.thicksizes.begin(), Configuration.thicksizes.end(),
            genesizes.begin() + paramlength);

        copy(Configuration.anisobase.begin(), Configuration.anisobase.end(),
            basevalues.begin() + 2 * paramlength);
        copy(Configuration.anisostep.begin(), Configuration.anisostep.end(),
            stepsizes.begin() + 2 * paramlength);
        copy(Configuration.anisosizes.begin(), Configuration.anisosizes.end(),
            genesizes.begin() + 2 * paramlength);

        copy(Configuration.strikebase.begin(), Configuration.strikebase.end(),
            basevalues.begin() + 3 * paramlength);
        copy(Configuration.strikestep.begin(), Configuration.strikestep.end(),
            stepsizes.begin() + 3 * paramlength);
        copy(Configuration.strikesizes.begin(),
            Configuration.strikesizes.end(), genesizes.begin() + 3
                * paramlength);

        const int totalgenesize = accumulate(genesizes.begin(),
            genesizes.end(), 0);
        BinaryPopulation Population(popsize, totalgenesize, Random, true);
        BinaryTournamentSelect Select(Random, boost::bind(
            &GeneralPopulation::GetProbabilities, boost::ref(Population)),
            boost::bind(&GeneralPopulation::GetCrowdingDistances, boost::ref(
                Population)));
        StandardPropagation Propagator(&Select, &Population, &Random);
        double indmutationprob = 1.0 - std::pow(1.0 - Configuration.mutationprob, 1.
            / totalgenesize); // we specify the overall probability for mutation in config file
        cout << "Individual Mutation set to: " << indmutationprob << endl;
        Propagator.SetParams(indmutationprob, Configuration.crossoverprob);
        GrayTranscribe Transcribe(basevalues, stepsizes, genesizes);

        //read in data


        //setup MT Objective function
        boost::shared_ptr<PlottableObjective> MTObjective;

        if (Configuration.mtfit == "ptensor")
          {
            PTensorMTStation PTData;
            PTData.GetData(Configuration.ptensordata);
            boost::shared_ptr<PTensor1DMTObjective> PTObjective(
                new PTensor1DMTObjective(PTData));
            PTObjective->SetErrorLevel(Configuration.phaseerror);
            MTObjective = PTObjective;
          }
        else
          {
            MTStation MTData;
            MTData.GetData(Configuration.mtinputdata);
            boost::shared_ptr<Aniso1DMTObjective> AnisoObjective(
                new Aniso1DMTObjective(MTData));
            SetupMTFitParameters(Configuration, *AnisoObjective);
            MTObjective = AnisoObjective;
          }
        MTObjective->SetFitExponent(Configuration.mtfitexponent);

        //setup regularization

        boost::shared_ptr<MTAnisoRoughness> MTRegularization(
            new MTAnisoRoughness());
        MTRegularization->SetCondDiffWeight(Configuration.conddiffweight);
        MTRegularization->SetAnisotropyWeight(Configuration.anisotropyweight);
        MTRegularization->SetStrikeDiffWeight(Configuration.strikediffweight);
        vector<pCGeneralObjective> ObjVector;
        ObjVector.push_back(MTObjective);
        ObjVector.push_back(MTRegularization);

        boost::shared_ptr<GeneralGA> GA;
        if (Configuration.gatype == "pareto")
          {
            GAtype = pareto;
            boost::shared_ptr<ParetoGA> Pareto(new ParetoGA(&Propagator,
                &Population, &Transcribe, ObjVector, Configuration.threads));
            GA = Pareto;
          }
        else if (Configuration.gatype == "anneal")
          {
            GAtype = anneal;
            boost::shared_ptr<AnnealingGA> Annealing(new AnnealingGA(
                &Propagator, &Population, &Transcribe, ObjVector,
                Configuration.threads));
            GA = Annealing;
          }
        else
          {
            cerr << "Invalid GA type in configuration file." << endl;
            cerr << " Has to be either 'pareto' or 'anneal' !" << endl;
            return 100;
          }
        GA->SetWeights(Configuration.weights);
        //Setting up indices for forward modelling
        GeneralGA::tparamindv ParamIndices;
        const int nmtparam = 4 * Configuration.resbase.size();
        std::vector<int> LocalIndices;
        generate_n(back_inserter(LocalIndices), nmtparam, IntSequence(0)); //generate Indices 0 .. nmtparam for MT Objective function
        ParamIndices.push_back(LocalIndices);//both data misfit and regularization
        ParamIndices.push_back(LocalIndices); //work on all parts of the model vector

        GA->SetParameterIndices(ParamIndices);
        GA->SetElitist(Configuration.elitist);
        //we have to do a few things that are specific to the type of genetic algorithm
        if (GAtype == anneal)
          {
            SetupAnnealingGA(GA, Configuration);
            Population.InitPop();
          }
        //now comes the core loop
        for (int i = 0; i < maxgen; ++i) //iterate over the specified number of generattions
          {
            GA->DoIteration(i, i == (maxgen - 1)); // pass iteration number to GA and tell whether it's the final iteration
            if (Configuration.verbose) // in most cases we do not need all of these values
              {
                GA->PrintMisfit(misfitfile);
                GA->PrintTranscribed(valuefile);
                Population.PrintProbabilities(probfile);
                Population.PrintDistances(distancefile);
              }
            GA->PrintBestMisfit(frontfile);

            fitstat << i << " ";
            GA->PrintFitStat(fitstat);
          }

        //the following is to organize the output of the best models
        int bestcount = 0;
        UniquePop FinalUnique; //we only want to write each model once, even if it is several times in the population
        tfitvec bestfit(ObjVector.size());
        tpopmember member(Population.GetGenesize());

        vector<int> BestIndices(GA->GetBestModelIndices()); // store the indices of the best models
        const unsigned int noutmodels = GA->GetNBestmodels(); // and how many of them we have
        assert(BestIndices.size() == noutmodels);
        const unsigned int nobjective = ObjVector.size();
        GeneralGA::tparamvector LocalParameters(nobjective);
        for (unsigned int i = 0; i < nobjective; ++i)
          LocalParameters.at(i).resize(ParamIndices.at(i).size(), false);
        ofstream finalmodels((outputbase + ".final").c_str());
        for (unsigned int h = 0; h < noutmodels; ++h) //for each best model
          {
            member = row(Population.GetPopulation(), BestIndices.at(h)); //get the genetic string


            transcribed = Transcribe.GetValues(member); //transcribe the genetic string to model parameters
            GA->SetupParams(transcribed, LocalParameters); //copy the right parameters for each objective function

            for (unsigned int f = 0; f < nobjective; ++f) //calculate the performance for each function
              {
                if (Configuration.weights.at(f) > 0)
                  bestfit(f) = ObjVector.at(f)->CalcPerformance(
                      LocalParameters.at(f));
                else
                  bestfit(f) = 0;

              }

            if (FinalUnique.Insert(bestfit, transcribed)) //if we can insert it, it is a new model that we didn't output yet
              {
                copy(bestfit.begin(), bestfit.end(), ostream_iterator<double> (
                    finalmodels, " ")); //print the misfits in the .final file
                finalmodels << "  " << bestcount << endl; // write the index in the last column for easier identification
                ostringstream filename;
                filename << "best_" << bestcount;
                cout << "Best: " << h << " Index : " << BestIndices.at(h)
                    << " "; //write some info to screen
                for (unsigned int f = 0; f < nobjective; ++f)
                  cout << bestfit(f) << " ";
                cout << " Saved as : " << filename.str();

                MTObjective->WriteModel(filename.str() + "_mt.mod"); //write model, plotting file and synthetic data
                MTObjective->WritePlot(filename.str() + "_mt.plot");
                MTObjective->WriteData(filename.str());

                filename.str("");
                bestcount++;
                cout << endl;
              }

          }

        if (Configuration.verbose) // in most cases we do not need all of these values
          {
            GA->PrintUniquePop(uniquepop);
            FinalUnique.PrintAll(bestfile);
          }
        boost::posix_time::ptime endtime =
            boost::posix_time::microsec_clock::local_time();
        std::cout << "Total Runtime: " << endtime - starttime << std::endl;
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      }
  }
