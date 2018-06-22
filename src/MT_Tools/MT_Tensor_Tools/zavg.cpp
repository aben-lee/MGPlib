#include <iostream>
#include <iomanip>
#include "MTStationList.h"

using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Average impedances from a number of different sites. Each datum is weighted
 * by its variance. Can be used to extract average 1D responses, but is affected
 * by static distortions, you can also try ptavg to average phase tensor elements.
 */

int main()
  {
    MTStationList MTSites;

    string infilename;

    string version = "$Id: zavg.cpp 1836 2009-11-27 12:17:24Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Average MT responses from a list of file  " << endl;
    cout << "The average response will be written in a file called avg.mtt "
        << endl;
    cout << "List filename:";
    cin >> infilename;
    double xxweights = 0;
    double xyweights = 0;
    double yxweights = 0;
    double yyweights = 0;

    MTSites.GetData(infilename);
    MTStation AvgSite(MTSites.at(0).GetMTData().size());
    AvgSite.SetFrequencies(MTSites.at(0).GetFrequencies());
    const size_t nfreq = MTSites.at(0).GetFrequencies().size();
    const size_t nsites = MTSites.GetList().size();
    const double errorfloor = 0.02;
    const double absolutemin = 1e-4; // have to find a better solution to avoid strong weighting of 0 values
    for (size_t j = 0; j < nfreq; ++j)
      {
        xxweights = 0;
        xyweights = 0;
        yxweights = 0;
        yyweights = 0;
        dcomp currzxx = 0;
        dcomp currzxy = 0;
        dcomp currzyx = 0;
        dcomp currzyy = 0;
        for (size_t i = 0; i < nsites; ++i)
          {
            double minweight = max(
                abs(MTSites.at(i).GetMTData().at(j).GetZxx()) * errorfloor,
                absolutemin);
            double currweight = 1. / pow(max(
                MTSites.at(i).GetMTData().at(j).GetdZxx(), minweight), 2);
            currzxx += MTSites.at(i).GetMTData().at(j).GetZxx() * currweight;
            xxweights += currweight;

            minweight = max(abs(MTSites.at(i).GetMTData().at(j).GetZxy())
                * errorfloor, absolutemin);
            currweight = 1. / pow(max(
                MTSites.at(i).GetMTData().at(j).GetdZxy(), minweight), 2);
            currzxy += MTSites.at(i).GetMTData().at(j).GetZxy() * currweight;
            xyweights += currweight;

            minweight = max(abs(MTSites.at(i).GetMTData().at(j).GetZyx())
                * errorfloor, absolutemin);
            currweight = 1. / pow(max(
                MTSites.at(i).GetMTData().at(j).GetdZyx(), minweight), 2);
            currzyx += MTSites.at(i).GetMTData().at(j).GetZyx() * currweight;
            yxweights += currweight;

            minweight = max(abs(MTSites.at(i).GetMTData().at(j).GetZyy())
                * errorfloor, absolutemin);
            currweight = 1. / pow(max(
                MTSites.at(i).GetMTData().at(j).GetdZyy(), minweight), 2);
            currzyy += MTSites.at(i).GetMTData().at(j).GetZyy() * currweight;
            yyweights += currweight;
          }
        AvgSite.SetMTData().at(j).SetZxx() = currzxx / xxweights;
        AvgSite.SetMTData().at(j).SetZxy() = currzxy / xyweights;
        AvgSite.SetMTData().at(j).SetZyx() = currzyx / yxweights;
        AvgSite.SetMTData().at(j).SetZyy() = currzyy / yyweights;
        AvgSite.SetMTData().at(j).SetErrors(sqrt(1. / xxweights), sqrt(1.
            / xyweights), sqrt(1. / yxweights), sqrt(1. / yyweights));
      }

    AvgSite.WriteAsMtt("avg");
  }
/*@}*/

