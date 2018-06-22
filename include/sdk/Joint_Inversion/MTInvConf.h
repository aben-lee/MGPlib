//============================================================================
// Name        : MTInvConf.h
// Author      : Apr 8, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef MTINVCONF_H_
#define MTINVCONF_H_

#include <string>
#include <fstream>
#include <boost/program_options.hpp>

namespace gplib
  {

    class MTInvConf
      {
    public:
      int mtfitexponent;
      double tensorerror;
      double reserror;
      double phaseerror;
      double surferror;
      std::string mode;
      std::string mtfit;
      std::string mtinputdata;
      void GetData(std::ifstream &instream)
      {
        po::options_description desc("MT inversion options");
        desc.add_options()("mtinputdata", po::value<std::string>(&mtinputdata),
            "The name of the MT data file")("mtfit", po::value<std::string>(
            &mtfit)->default_value("berd"), "The type of data to fit")(
            "mode",
            po::value<std::string>(&mode)->default_value("xy"),
            "The mode xy or yx to fit")(
            "mtfitexponent", po::value<int>(&mtfitexponent)->default_value(2),
            "The exponent in the misfit functional")("tensorerror",
            po::value<double>(&tensorerror)->default_value(0.02),
            "The error floor for fitting tensor data")(
            "reserror", po::value<double>(&reserror)->default_value(0.02),
            "The error floor for fitting apperent resistivity data")(
            "phaseerror", po::value<double>(&phaseerror)->default_value(0.02),
            "The error floor for fitting phase data");

        po::variables_map vm;
        po::store(po::parse_config_file(instream, desc, true), vm);
        po::notify(vm);

      }
      MTInvConf();
      virtual ~MTInvConf();
      };

  }

#endif /* MTINVCONF_H_ */
