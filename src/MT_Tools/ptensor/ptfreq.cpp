#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "MTStationList.h"
#include "FatalException.h"
#include "Adaptors.h"
#include "Jacknife.h"
#include "MTSampleGenerator.h"
#include <sstream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <iterator>
#include <boost/progress.hpp>

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate phase tensor components and errors from MT impedance data
 */

using namespace gplib;
using namespace std;
namespace po = boost::program_options;

string version = "$Id: ptfreq.cpp 1851 2010-05-18 13:48:45Z mmoorkamp $";

//! This helper function prints out a single phase tensor component together with error information to a file
template<typename T>
inline void PrintComponent(const std::string &compname,
    boost::function<const T(const MTTensor*)> f, MTStationList &StationList,
    int ntestcases = 0, double errorfloor = 0.02)
  {

    const unsigned int nstations = StationList.GetList().size();

    cout << "Processing component: " << compname << endl << endl;
    boost::progress_display show_progress(nstations); // init progress bar

    for (unsigned int i = 0; i < nstations; ++i) //for all sites
      {
        string outfilename = StationList.at(i).GetName() + compname + ".dat";
        ofstream outfile(outfilename.c_str()); //init output
        const unsigned int nfreq = StationList.at(i).GetMTData().size();
        for (unsigned int j = 0; j < nfreq; ++j)
          {
            outfile << setw(12) << setfill(' ') << setprecision(4) << 1.
                / StationList.at(i).GetMTData().at(j).GetFrequency();
            // bind the MTTensor object with the correct frequency index
            // to the member function that gives the chosen component
            outfile << setw(12) << setfill(' ') << setprecision(4)
                << boost::bind(f, &StationList.at(i).GetMTData().at(j))();

            if (ntestcases > 2) // if we want Errors and we have enough samples
              {
                double JackMean, JackVar;
                StationList.at(i).SetMTData().at(j).SetdZxx() = max(
                    StationList.at(i).at(j).GetdZxx(), errorfloor * abs(
                        StationList.at(i).at(j).GetZxx()));
                StationList.at(i).SetMTData().at(j).SetdZxy() = max(
                    StationList.at(i).at(j).GetdZxy(), errorfloor * abs(
                        StationList.at(i).at(j).GetZxy()));
                StationList.at(i).SetMTData().at(j).SetdZyx() = max(
                    StationList.at(i).at(j).GetdZyx(), errorfloor * abs(
                        StationList.at(i).at(j).GetZyx()));
                StationList.at(i).SetMTData().at(j).SetdZyy() = max(
                    StationList.at(i).at(j).GetdZyy(), errorfloor * abs(
                        StationList.at(i).at(j).GetZyy()));
                MTSampleGenerator Generator(f, StationList.at(i).at(j));
                Jacknife<MTSampleGenerator> ErrEst(ntestcases, Generator);
                ErrEst.CalcErrors(JackMean, JackVar); //that calculates the final value from raw data
                outfile << " " << setw(12) << setfill(' ') << setprecision(4)
                    << sqrt(JackVar); // output the error
              }
            outfile << endl; // and start a new line for the next frequency
          }
        ++show_progress; // make sure progress bar progresses

      }
    std::cout << std::endl << std::endl;
  }

int main(int argc, char *argv[])
  {
    string infilename, outfilename; //storing names for input and root of output
    MTStationList MTSites; // object for the station data
    // write some info
    cout << " This is ptfreq, calculate phasetensor elipses etc. from MT data"
        << endl;
    cout
        << " Reads in a list of stations and outputs one file for each station"
        << endl;
    cout
        << " Each file contains the frequency dependency of a component of the phase tensor for one site"
        << endl;
    cout << " File endings will be automatically appended." << endl;
    cout
        << " For error calculation, numbers < 2 will be interpreted as no error calculation."
        << endl;
    cout << " This is Version: " << version << endl << endl;

    int nbootsamples = -1;
    double errorfloor = 0.0;
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("nboot", po::value<int>(
        &nbootsamples)->default_value(10000),
        "The number of samples for bootstrap error calculation")("errfloor",
        po::value<double>(&errorfloor)->default_value(0.01),
        "The minimum relative error to assume for the data")
        ("input-file", po::value< string>(&infilename), "input file");

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }


    try
      {
        //try to read in all station data
        MTSites.GetData(infilename);

        //calculate and print various components of the phase tensor
        //these files contain a single phase tensor quantities and its error as a function of period
        PrintComponent<double> ("phi11", &MTTensor::GetPhi11, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phi12", &MTTensor::GetPhi12, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phi21", &MTTensor::GetPhi21, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phi22", &MTTensor::GetPhi22, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phimax", &MTTensor::GetPhiMax, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phimin", &MTTensor::GetPhiMin, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phiellip", &MTTensor::GetPhiEllip, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phialpha", &MTTensor::GetAlpha_phi, MTSites,
            nbootsamples, errorfloor);
        PrintComponent<double> ("phibeta", &MTTensor::GetBeta_phi, MTSites,
            nbootsamples, errorfloor);
        //now we also generate some files that contain various components
        //we do this for all files in the list
        for (vector<MTStation>::iterator it = MTSites.GetList().begin(); it
            != MTSites.GetList().end(); ++it)
          {
            //the first file simply contains all relevant quantities as a quick overview
            string rotfilename = it->GetName() + "_phiall.dat";
            ofstream rotfile(rotfilename.c_str());
            for (unsigned int i = 0; i < it->GetFrequencies().size(); ++i)
              {
                rotfile << setw(12) << setfill(' ') << setprecision(4) << 1.
                    / it->GetFrequencies().at(i);
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhi11();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhi12();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhi21();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhi22();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetAlpha_phi();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetBeta_phi();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhiMax();
                rotfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhiMin() << endl;

              }
            rotfile.close();
            //this file is for plotting ellipses with gmt
            //we want one ellipse per period
            string ptfilename = it->GetName() + "_ptellip.dat";
            ofstream ptfile(ptfilename.c_str());
            for (unsigned int i = 0; i < it->GetMTData().size(); ++i)
              {
                //the x value is the period
                ptfile << setw(12) << setfill(' ') << setprecision(4) << 1.
                    / it->GetMTData().at(i).GetFrequency();
                //all ellipses should be at the same height, i.e. y value
                ptfile << setw(12) << setfill(' ') << setprecision(4) << 1.0;
                // the gmt documentation is not clear, but we need the color before the directions etc.
                //we color the ellipses by the skew
                ptfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetBeta_phi() * 180. / PI;
                //GMT wants the angle counter clockwise from horizontal
                ptfile << setw(12) << setfill(' ') << setprecision(4) << 90
                    - (it->GetMTData().at(i).GetPhiStrike()) * 180. / PI;
                // and then the major axis
                ptfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhiMax();
                // and the minor axis of the ellipse
                ptfile << setw(12) << setfill(' ') << setprecision(4)
                    << it->GetMTData().at(i).GetPhiMin();
                ptfile << endl;
              }
            ptfile.close();
          }
      } catch (FatalException &e)
      {
        cerr << e.what() << endl; // if something fails print error
        return -1; // and stop execution
      }
  }
/*@}*/

