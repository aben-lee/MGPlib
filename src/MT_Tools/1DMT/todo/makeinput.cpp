#include <iostream>
#include "C1DMTSynthData.h"
#include "CResPkModel.h"
#include "CRecCalc.h"
#include "CUniformRNG.h"
#include "MakeInputConf.h"
#include "CSeismicDataComp.h"
#include "Adaptors.h"
#include <vector>
#include <boost/bind.hpp>
#include <string>

using namespace std;
using namespace gplib;

string version = "$Id: makeinput.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

int main(int argc, char *argv[])
  {
    cout
        << " This is makeinput: Create MT and receiver function models and data"
        << endl; // write some info
    cout << " to be used as input for inversion methods." << endl;
    cout
        << " If one argument is given, this argument is taken as the filename base for all output files."
        << endl;
    cout
        << " Otherwise the output file base is read from the configuration file 'makeinput.conf' "
        << endl;
    cout << " The configuration file contains all other relevant settings. "
        << endl;
    cout << " This is Version: " << version << endl << endl;
    UniformRNG Random;
    MakeInputConf Configuration;
    Configuration.GetData("makeinput.conf");

    string outputbase;
    if (argc > 1)
      outputbase = argv[1];
    else
      outputbase = Configuration.outputbase;

    C1DMTSynthData MTSynth;
    ResPkModel RecModel;
    RecCalc RecSynth(Configuration.shift, Configuration.omega,
        Configuration.sigma, Configuration.cc);
    SeismicDataComp RecSynthData;
    const double basevel = 3.2;
    const double basedens = 2.6;
    const double baseres = 1.0 + Random.GetNumber();
    const double basethick = 1.0 + Random.GetNumber() * 10;
    vector<double> velocities(Configuration.nlayers);
    vector<double> densities(Configuration.nlayers);
    vector<double> resistivities(Configuration.nlayers);
    vector<double> mtthickness(Configuration.nlayers);
    vector<double> recthickness(Configuration.nlayers);
    densities.front() = basedens;
    resistivities.front() = baseres;
    velocities.front() = basevel;
    mtthickness.front() = basethick;
    if (Configuration.correlated)
      {
        recthickness.front() = basethick;
      }
    else
      {
        recthickness.front() = basethick * Random.GetNumber(1.1, 2.0);
      }
    for (int i = 1; i < Configuration.nlayers; ++i)
      {
        mtthickness.at(i) = mtthickness.at(i - 1) * Random.GetNumber(1.1, 2.0);
        if (Configuration.correlated)
          {
            recthickness.at(i) = mtthickness.at(i);
          }
        else
          {
            recthickness.at(i) = mtthickness.at(i) * Random.GetNumber(1.1, 2.0);

          }
        densities.at(i) = densities.at(i - 1) * Random.GetNumber(1.1, 1.5);
        resistivities.at(i) = Random.GetNumber(0.0, 3.0);
        velocities.at(i) = velocities.at(i - 1) * Random.GetNumber(1.05, 1.2);
      }
    transform(resistivities.begin(), resistivities.end(),
        resistivities.begin(), boost::bind(fopow<double, double> (), 10, _1));
    MTSynth.SetResistivities(resistivities);
    MTSynth.SetThicknesses(mtthickness);
    MTSynth.writemodel(outputbase + "_mt.mod");
    MTSynth.writeplot(outputbase + "_mt.plot");
    MTSynth.GetData();
    MTSynth.WriteAsMtt(outputbase);

    RecModel.Init(Configuration.nlayers); //initialize model
    RecModel.slowness = Configuration.slowness; //copy slowness
    copy(recthickness.begin(), recthickness.end(), RecModel.Thickness.begin()); //copy values
    copy(velocities.begin(), velocities.end(), RecModel.SVelocity.begin());
    copy(densities.begin(), densities.end(), RecModel.Density.begin());
    transform(RecModel.SVelocity.begin(), RecModel.SVelocity.end(), //PVelocity is calculated by multiplication of SVel by poisson's ratio
        RecModel.PVelocity.begin(), boost::bind(multiplies<double> (), _1,
            Configuration.poisson));
    RecModel.dt = Configuration.dt; // set dt
    RecModel.npts = Configuration.npts; //set number of points
    RecSynth.CalcRecSynth(Configuration.outputbase + "_rec", RecModel,
        RecSynthData, false); // Calculate forward model
    RecModel.WritePlot(outputbase + "_rec");
    RecSynthData.WriteAsSac(outputbase + ".rec");
  }
