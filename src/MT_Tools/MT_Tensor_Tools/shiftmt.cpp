/*! \file
 * This program adds gaussian random noise to the impedance estimates taken
 * from infilename and writes a new ".mtt" file with the noisy data and updated error
 * information. The output file has the same name as the input file with ".ns" appended.
 * The noise level is the relative noise for real and imaginary parts of the impedance at
 * each frequency.
 */

#include <iostream>
#include <complex>
#include <ctime>
#include <cmath>
#include "MTStation.h"
#include "Util.h"
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;
using namespace gplib;

string version = "$Id: addnoise.cpp 1844 2010-04-12 11:34:25Z mmoorkamp $";

void AddNoise(std::complex<double> &impelement, double &noiseest,
    const double relativenoiselevel, const double absolutenoiselevel,
    boost::lagged_fibonacci607 &generator)
  {
    //save the original impedance element
    complex<double> oldimp(impelement);
    //determine the noise level for the real part
    double realnoiselevel = max(std::abs(impelement.real() * relativenoiselevel),
        absolutenoiselevel);
    //and the imaginary part
    double imagnoiselevel = max(std::abs(impelement.imag() * relativenoiselevel),
        absolutenoiselevel);
    //draw a sample from a normal distribution for the real part
    impelement = boost::variate_generator<boost::lagged_fibonacci607&,
        boost::normal_distribution<> >(generator,
        boost::normal_distribution<>(impelement.real(), realnoiselevel))();
    //and for the imaginary part
    impelement += complex<double>(0.0, 1.0)
        * boost::variate_generator<boost::lagged_fibonacci607&,
            boost::normal_distribution<> >(generator,
            boost::normal_distribution<>(oldimp.imag(), imagnoiselevel))();

    noiseest = max(relativenoiselevel * abs(oldimp), absolutenoiselevel);
  }

int main(int argc, char *argv[])
  {
    string infilename, outfilename;
    MTStation Data;
    boost::lagged_fibonacci607 generator(static_cast<unsigned int>(std::time(0)));

    cout << "This is addnoise: Add random noise to MT impedance estimates." << endl
        << endl;
    cout << " Usage: addnoise  infilename  noiselevel" << endl;
    cout << " The output files will have the same name as the input files + .ns " << endl
        << endl;
    cout << " This is Version: " << version << endl << endl;

    infilename = AskFilename("Infilename: ");
    double minperiod;
    cout << "Minimum period:";
    cin >> minperiod;
    double shiftfactor;
    cout << "Shiftfactor:";
    cin >> shiftfactor;
    outfilename = infilename + ".rhons";

    Data.GetData(infilename);
    for (unsigned int i = 0; i < Data.GetMTData().size(); ++i)
      {
        if (Data.GetFrequencies().at(i) < 1.0 / minperiod)
          {
            Data.SetMTData().at(i).SetZxx() *= shiftfactor;
            Data.SetMTData().at(i).SetZxy() *= shiftfactor;
            Data.SetMTData().at(i).SetZyx() *= shiftfactor;
            Data.SetMTData().at(i).SetZyy() *= shiftfactor;
          }
      }
    Data.WriteAsMtt(outfilename);
    Data.GetData(infilename);
    outfilename = infilename + ".phins";
    for (unsigned int i = 0; i < Data.GetMTData().size(); ++i)
      {
        if (Data.GetFrequencies().at(i) < 1.0 / minperiod)
          {
            dcomp Zxx = Data.SetMTData().at(i).SetZxx();
            dcomp Zxy = Data.SetMTData().at(i).SetZxy();
            dcomp Zyx = Data.SetMTData().at(i).SetZyx();
            dcomp Zyy = Data.SetMTData().at(i).SetZyy();
            Data.SetMTData().at(i).SetZxx() = abs(Zxx)
                * dcomp(cos(shiftfactor), sin(shiftfactor));
            Data.SetMTData().at(i).SetZxy() = abs(Zxy)
                * dcomp(cos(shiftfactor), sin(shiftfactor));
            Data.SetMTData().at(i).SetZyx() = abs(Zyx)
                * dcomp(cos(shiftfactor), sin(shiftfactor));
            Data.SetMTData().at(i).SetZyy() = abs(Zyy)
                * dcomp(cos(shiftfactor), sin(shiftfactor));

          }
      }
    Data.WriteAsMtt(outfilename);
  }
