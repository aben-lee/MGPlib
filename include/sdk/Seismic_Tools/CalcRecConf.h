/***************************************************************************
 Copyright (C) 2007 - 2009 Max Moorkamp

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 ***************************************************************************/

#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <FatalException.h>
#include <boost/program_options.hpp>

namespace gplib
  {
    class CalcRecConf
      {
        using namespace std;
        namespace po = boost::program_options;
    private:
      int argc;
      char **argv;
    public:
      void GetData(std::string filename)
      {
        ifstream infile;
        infile.open(filename.c_str());
        infile.peek();
        if (!infile)
          throw gplib::FatalException("No Configurationfile found !");

        GetData(infile);
        infile.close();
      }

      void GetData(std::ifstream &instream)
      {

        po::options_description desc("Receiver function calculation options");
        desc.add_options()("cc", po::value<double>(&cc),
            "The waterlevel for the deconvolution")("shift",
            po::value<int>(&shift)->default_value(0),
            "The shift in s of the initial correlation peak")("sigma",
            po::value<double>(&sigma)->default_value(1.0),
            "The bandwidth of the receiver function")("recmethod",
            po::value<std::string>(&recmethod), "The deconvolution method")("normalize",
            po::value<bool>(&normalize), "Normalize the receiver function")("upperfreq",
            po::value<double>(&upperfreq)->default_value(-1.0), "")("lowerfreq",
            po::value<double>(&lowerfreq)->default_value(-1.0), "")("rotate",
            po::value<bool>(&rotate)->default_value(false))("prec",
            po::value<bool>(&prec)->default_value(true))("beta",
            po::value<double>(&beta)->default_value(3.5))("p",
            po::value<double>(&p)->default_value(-1));

        po::variables_map vm;
        po::store(po::parse_config_file(instream, desc), vm);
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

      }
      double upperfreq;
      double lowerfreq;
      double cc;
      double sigma;
      int shift;
      std::string recmethod;
      bool normalize;
      bool rotate;
      double rotwin;
      bool prec;
      double beta;
      double p;
      CalcRecConf(std::string filename)
        {
          GetData(filename);
        }
      CalcRecConf(int ac = 0, char **av = (char **)0) :
          argc(ac), argv(av)
        {
        }
      };
  }
