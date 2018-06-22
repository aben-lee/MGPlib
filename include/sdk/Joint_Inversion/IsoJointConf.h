//============================================================================
// Name        : IsoJointConf.h
// Author      : Apr 8, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef ISOJOINTCONF_H_
#define ISOJOINTCONF_H_

#include <string>
#include <fstream>
#include <vector>
#include "convert.h"
#include "VecMat.h"
#include "VectorOptions.h"
#include <boost/program_options.hpp>
#include <cmath>
#include <boost/tokenizer.hpp>

namespace gplib
  {

    class IsoJointConf
      {
    public:
      bool verbose;
      std::string outputbase;
      double poisson;
      bool usevrefmodel;
      std::string vrefmodel;
      std::vector<double> thickbase;
      std::vector<double> thickstep;
      std::vector<int> thicksizes;
      std::vector<double> resbase;
      std::vector<double> resstep;
      std::vector<int> ressizes;
      std::vector<double> svelbase;
      std::vector<double> svelstep;
      std::vector<int> svelsizes;
      std::vector<double> weights;
      void GetData(std::ifstream &instream)
      {
        DummyVec<double> Test;

        options_description desc("Joint inversion options");
        desc.add_options()("outputbase", value<std::string> (&outputbase),
            "The start of the name of the output files")("verbose", value(
            &verbose)->default_value(false), "")("poisson", value<double> (
            &poisson), "Poisson's ration")("usevrefmodel",
            value(&usevrefmodel)->default_value(false), "")("vrefmodel", value(
            &vrefmodel), "")("thickbase", value<DummyVec<double> > (), "")(
            "thickstep", value<DummyVec<double> > (), "")("thicksizes", value<
            DummyVec<int> > (), "")("resbase", value<DummyVec<double> > (), "")(
            "resstep", value<DummyVec<double> > (), "")("ressizes", value<
            DummyVec<int> > (), "")("svelbase", value<DummyVec<double> > (), "")(
            "svelstep", value<DummyVec<double> > (), "")("svelsizes", value<
            DummyVec<int> > (), "")("weights", value<DummyVec<double> > (), "");

        variables_map vm;
        store(parse_config_file(instream, desc, true), vm);
        notify(vm);

        if (vm.count("thickbase"))
          {
            thickbase = vm["thickbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("thickstep"))
          {
            thickstep = vm["thickstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("thicksizes"))
          {
            thicksizes = vm["thicksizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("resbase"))
          {
            resbase = vm["resbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("resstep"))
          {
            resstep = vm["resstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("ressizes"))
          {
            ressizes = vm["ressizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("svelbase"))
          {
            svelbase = vm["svelbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("svelstep"))
          {
            svelstep = vm["svelstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("svelsizes"))
          {
            svelsizes = vm["svelsizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("weights"))
          {
            weights = vm["weights"].as<DummyVec<double> > ().VecVal;
          }
      }
      IsoJointConf();
      virtual ~IsoJointConf();
      };

  }

#endif /* ISOJOINTCONF_H_ */
