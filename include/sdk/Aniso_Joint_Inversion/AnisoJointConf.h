#include <string>
#include <fstream>
#include <vector>
#include <boost/program_options.hpp>
#include "VectorOptions.h"

namespace gplib
  {
    class AnisoJointConf
      {
           using namespace boost::program_options;
    public:
      void GetData(std::ifstream &instream)
      {
        DummyVec<double> Test;

        options_description desc("Joint inversion options");
        desc.add_options()("outputbase", value<std::string> (&outputbase),
            "The start of the name of the output files")("verbose", value(
            &verbose)->default_value(false), "")("ptensordata", value(
            &ptensordata), "The name of a file containing phase tensor MT data")

        ("conddiffweight", value(&conddiffweight),
            "The weight for regularizing the difference in conductivity between layers")(
            "anisotropyweight", value(&anisotropyweight),
            "The weight for regularizing the anisotropy")("strikediffweight",
            value(&strikediffweight),
            "The weight for regularizing the difference in strike between layers")(
            "veldiffweight", value(&veldiffweight),
            "The weight for regularizing the difference in velocity")(
            "anisovelweight", value(&anisovelweight),
            "The weight for regularizing the anisotropy of the velocity")(
            "deltastrikediffweight", value(&deltastrikediffweight),
            "The weight for regularizing the difference in strike between MT and seismics")(
            "avelratio", value(&avelratio), "")("thickstep", value<DummyVec<
            double> > (), "")("resstep", value<DummyVec<double> > (), "")(
            "velstep", value<DummyVec<double> > (), "")("aresstep", value<
            DummyVec<double> > (), "")("avelstep", value<DummyVec<double> > (),
            "")("strikestep", value<DummyVec<double> > (), "")("dstrikestep",
            value<DummyVec<double> > (), "")("thickstep", value<
            DummyVec<double> > (), "")("thickbase",
            value<DummyVec<double> > (), "")("resbase",
            value<DummyVec<double> > (), "")("velbase",
            value<DummyVec<double> > (), "")("aresbase",
            value<DummyVec<double> > (), "")("avelbase",
            value<DummyVec<double> > (), "")("strikebase", value<DummyVec<
            double> > (), "")("dstrikebase", value<DummyVec<double> > (), "")(
            "thicksizes", value<DummyVec<int> > (), "")("ressizes", value<
            DummyVec<int> > (), "")("velsizes", value<DummyVec<int> > (), "")(
            "aressizes", value<DummyVec<int> > (), "")("avelsizes", value<
            DummyVec<int> > (), "")("strikesizes", value<DummyVec<int> > (), "")(
            "dstrikesizes", value<DummyVec<int> > (), "")("weights", value<
            DummyVec<double> > (), "");

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
            thicksizes = vm["thicksize"].as<DummyVec<int> > ().VecVal;
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

        if (vm.count("velbase"))
          {
            velbase = vm["velbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("velstep"))
          {
            velstep = vm["velstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("velsizes"))
          {
            velsizes = vm["velsizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("aresbase"))
          {
            aresbase = vm["aresbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("aresstep"))
          {
            aresstep = vm["aresstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("aressizes"))
          {
            aressizes = vm["aressizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("avelbase"))
          {
            avelbase = vm["avelbase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("avelstep"))
          {
            avelstep = vm["avelstep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("avelsizes"))
          {
            avelsizes = vm["avelsizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("strikebase"))
          {
            strikebase = vm["strikebase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("strikestep"))
          {
            strikestep = vm["strikestep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("strikesizes"))
          {
            strikesizes = vm["strikesizes"].as<DummyVec<int> > ().VecVal;
          }

        if (vm.count("dstrikebase"))
          {
            dstrikebase = vm["dstrikebase"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("dstrikestep"))
          {
            dstrikestep = vm["dstrikestep"].as<DummyVec<double> > ().VecVal;
          }
        if (vm.count("dstrikesizes"))
          {
            dstrikesizes = vm["dstrikesizes"].as<DummyVec<int> > ().VecVal;
          }
        if (vm.count("weights"))
          {
            weights = vm["weights"].as<DummyVec<double> > ().VecVal;
          }
      }
      void GetData(std::string filename);
      void WriteData(std::ofstream &outstream);
      void WriteData(std::string filename);
      bool verbose;
      std::string outputbase;
      std::string ptensordata;
      std::vector<double> thickbase;
      std::vector<double> thickstep;
      std::vector<int> thicksizes;
      std::vector<double> resbase;
      std::vector<double> resstep;
      std::vector<int> ressizes;
      std::vector<double> velbase;
      std::vector<double> velstep;
      std::vector<int> velsizes;
      std::vector<double> aresbase;
      std::vector<double> aresstep;
      std::vector<int> aressizes;
      std::vector<double> avelbase;
      std::vector<double> avelstep;
      std::vector<int> avelsizes;
      std::vector<double> strikebase;
      std::vector<double> strikestep;
      std::vector<int> strikesizes;
      std::vector<double> dstrikebase;
      std::vector<double> dstrikestep;
      std::vector<int> dstrikesizes;
      std::vector<double> weights;
      double conddiffweight;
      double anisotropyweight;
      double strikediffweight;
      double veldiffweight;
      double anisovelweight;
      double deltastrikediffweight;
      double avelratio;
      AnisoJointConf();
      ~AnisoJointConf();
      AnisoJointConf(std::string filename)
        {
          GetData(filename);
        }
      };
  }
