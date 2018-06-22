//============================================================================
// Name        : RecInvConf.h
// Author      : Apr 7, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef RECINVCONF_H_
#define RECINVCONF_H_

#include <fstream>
#include <string>
#include <FatalException.h>
#include <boost/program_options.hpp>

namespace gplib
  {

    class RecInvConf
      {
    public:
      std::string recinfofile;
      std::string recmethod;
      bool normrec;
      int recfitexponent;
      double starttime;
      double endtime;
      void GetData(std::ifstream &instream)
      {
        po::options_description desc("Receiver function inversion options");
        desc.add_options()("recinfofile", po::value<std::string>(&recinfofile),
            "The file containing information about the receiver function data")(
            "recmethod", po::value<std::string>(&recmethod)->default_value("iterdecon"),
            "The method to calculate the receiver function, iterdecon oder specdiv")(
            "normrec", po::value<bool>(&normrec)->default_value(false),
            "The receiver functions have been normalized ")("recfitexponent",
            po::value<int>(&recfitexponent)->default_value(2),
            "The exponent for the misfit functional")("starttime", po::value<
            double>(&starttime)->default_value(-1.0),
            "The start time for the part of the RF considered in the inversion in s")(
            "endtime", po::value<double>(&endtime)->default_value(-1.0),
            "The end time for the part of the RF considered in the iversion in s");

        po::variables_map vm;
        po::store(po::parse_config_file(instream, desc, true), vm);
        po::notify(vm);
      }

      RecInvConf();
      virtual ~RecInvConf();
      };

  }

#endif /* RECINVCONF_H_ */
