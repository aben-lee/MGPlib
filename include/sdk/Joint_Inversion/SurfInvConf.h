//============================================================================
// Name        : SurfInvConf.h
// Author      : Apr 8, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef SURFINVCONF_H_
#define SURFINVCONF_H_


#include <string>
#include <fstream>
#include <boost/program_options.hpp>

namespace gplib
  {

    class SurfInvConf
      {
    public:
      std::string dispdata;
      int surffitexponent;
      double surferror;
      void GetData(std::ifstream &instream)
      {
        po::options_description desc("Surface wave inversion options");
        desc.add_options()("dispdata", po::value(&dispdata), "")(
            "surffitexponent", po::value(&surffitexponent)->default_value(2), "")("surferror",
            po::value(&surferror)->default_value(0.02), "");

        po::variables_map vm;
        po::store(po::parse_config_file(instream, desc, true), vm);
        po::notify(vm);

      }
      SurfInvConf();
      virtual ~SurfInvConf();
      };

  }

#endif /* SURFINVCONF_H_ */
