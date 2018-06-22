//============================================================================
// Name        : GAConf.h
// Author      : Apr 7, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef GACONF_H_
#define GACONF_H_

#include <string>
#include <fstream>
#include <iostream>
#include <FatalException.h>
#include <boost/program_options.hpp>

namespace gplib
  {

    class GAConf
      {
        using namespace std;
        namespace po = boost::program_options;
    public:
      int popsize;
      double inittemp;
      double coolingratio;
      int generations;
      double mutationprob;
      double crossoverprob;
      std::string gatype;
      int annealinggeneration;
      bool elitist;
      void GetData(std::ifstream &instream)
      {
        po::options_description desc("");
        desc.add_options()("popsize", po::value<int>(&popsize),
            "The size of the GA population")("inittemp", po::value<double>(
            &inittemp), "The initial temperature for an annealing type GA")(
            "coolingratio",
            po::value<double>(&coolingratio)->default_value(1.0),
            "The ratio for the decrease in temperature in the annealing schedule")(
            "annealinggeneration", po::value<int>(&annealinggeneration),
            "The generation number when to apply the cooling")("generations",
            po::value<int>(&generations),
            "The total number of generations for the GA to run")(
            "mutationprob", po::value<double>(&mutationprob),
            "The probability for mutation for the whole genetic string")(
            "crossoverprob", po::value<double>(&crossoverprob),
            "The crossover probability")("gatype", po::value<std::string>(
            &gatype)->default_value("anneal"),
            "The type of genetic algorithm can be anneal or pareto")("elitist",
            po::value<bool>(&elitist)->default_value("true"),
            "Do we always preserve the best model from generation to generation");

        po::variables_map vm;
        po::store(po::parse_config_file(instream, desc, true), vm);
        po::notify(vm);

      }
      GAConf();
      virtual ~GAConf();
      };

  }

#endif /* GACONF_H_ */
