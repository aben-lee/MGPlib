#include <iostream>
#include <iomanip>
#include <fstream>
#include "MTStationList.h"
#include "PTensorMTStation.h"
#include "VecMat.h"
#include "statutils.h"

using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Average the phase tensor elements from a number of MT files, each datum is weighted equally.
 * This program is mainly used as an attempt to get average 1D (isotropic or anisotropic) responses
 * for a region from a number of measurements.
 */

int main()
  {
    MTStationList MTSites;
    PTensorMTStation PTStation;
    string infilename;

    string version = "$Id: ptavg.cpp 1836 2009-11-27 12:17:24Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Average MT phase tensor elements from a list of files  " << endl;
    cout
        << "The average phase tensor will be written in a file called avg.ptensor "
        << endl;
    cout << "List filename:";
    cin >> infilename;

    MTSites.GetData(infilename);
    const size_t nfreq = MTSites.at(0).GetFrequencies().size();
    const size_t nsites = MTSites.GetList().size();
    const double errorfloor = 0.02;
    const double absolutemin = 1e-4; // have to find a better solution to avoid strong weighting of 0 values
    for (size_t j = 0; j < nfreq; ++j)
      {
        gplib::rvec xxvalues(nsites);
        gplib::rvec xyvalues(nsites);
        gplib::rvec yxvalues(nsites);
        gplib::rvec yyvalues(nsites);

        for (size_t i = 0; i < nsites; ++i)
          {
            xxvalues(i) = MTSites.at(i).GetMTData().at(j).GetPhi11();
            xyvalues(i) = MTSites.at(i).GetMTData().at(j).GetPhi12();
            yxvalues(i) = MTSites.at(i).GetMTData().at(j).GetPhi21();
            yyvalues(i) = MTSites.at(i).GetMTData().at(j).GetPhi22();

          }
        double phi11 = Mean(xxvalues.begin(), xxvalues.end());
        double phi12 = Mean(xyvalues.begin(), xyvalues.end());
        double phi21 = Mean(yxvalues.begin(), yxvalues.end());
        double phi22 = Mean(yyvalues.begin(), yyvalues.end());

        double varphi11 = Variance(xxvalues.begin(), xxvalues.end());
        double varphi12 = Variance(xyvalues.begin(), xyvalues.end());
        double varphi21 = Variance(yxvalues.begin(), yxvalues.end());
        double varphi22 = Variance(yyvalues.begin(), yyvalues.end());

        PTStation.GetTensor().push_back(PTensorMTData(
            MTSites.at(0).GetFrequencies().at(j), phi11, phi12, phi21, phi22,
            sqrt(varphi11), sqrt(varphi12), sqrt(varphi21), sqrt(varphi22)));
      }
    PTStation.WriteData("avg.ptensor");
  }
/*@}*/

