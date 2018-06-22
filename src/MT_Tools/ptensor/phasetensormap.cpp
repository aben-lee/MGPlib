#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "MTStationList.h"
#include "FatalException.h"
#include "Adaptors.h"
#include "Jacknife.h"
#include "MTSampleGenerator.h"
#include "Util.h"
#include <sstream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iterator>
#include <boost/progress.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace gplib;

string version =
    "$Id: phasetensormap.cpp 1838 2010-03-04 16:19:34Z mmoorkamp $";

//! Print out one component of MT data from a list of Stations for plotting with GMT

/*! Print Component prints one component of MT Data e.g. phase, strike angle, for all sites into a file with
 * name file name. Parameters are
 * @param filename  name of the file to print to
 * @param f Pointer to member function of MTTensor that will print out the desired component
 * @param StationList  Object holding all the station data
 * @param freqindex  the index of the frequency to print, this will be synchronized through the ComFreqIndices array
 * @param adaptor  pointer to a function that maps the result of f to a double value
 * @param ntestcases how many samples needed for bootstrap error calculation
 * @param CalcError  is ErrorCalculation wanted
 */
template<typename T> void PrintComponent(const std::string &filename,
    boost::function<const T(const MTTensor*)> f, MTStationList &StationList,
    const int freqindex, boost::function<double(T)> adaptor, int ntestcases = 0)
  {
    const std::vector<tindexvector>
        realindices(StationList.GetComFreqIndices()); //store the indices of the desired frequency for each station 
    ofstream outfile(filename.c_str()); //init output
    std::cout << " Working on file: " << filename << std::endl; // feedback for the user
    boost::progress_display show_progress(StationList.GetList().size()); // init progress bar

    for (unsigned int i = 0; i < StationList.GetList().size(); ++i) //for all sites
      {
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << StationList.at(i).GetLongitude() << " "; //print latitude
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << StationList.at(i).GetLatitude() << " "; //print longitude
        outfile << setw(12) << setfill(' ') << setprecision(4) << adaptor(
            boost::bind(f, &StationList.at(i).GetMTData().at(
                realindices.at(i).at(freqindex)))());// bind the MTTensor object with the correct frequency index
        // to the member function that gives the chosen component and pass it through the adaptor function
        if (ntestcases > 2) // if we want Errors and we have enough samples
          {
            double JackMean, JackErr;
            MTSampleGenerator Generator(f, StationList.at(i).GetMTData().at(
                realindices.at(i).at(freqindex)));
            Jacknife<MTSampleGenerator> ErrEst(ntestcases, Generator);
            ErrEst.CalcErrors(JackMean, JackErr); //that calculates the final value from raw data
            outfile << " " << setw(12) << setfill(' ') << setprecision(4)
                << JackErr; // output the error
          }
        ++show_progress; // make sure progress bar progresses
        outfile << endl; // and start a new line for the next site
      }
    std::cout << std::endl << std::endl;
  }

namespace po = boost::program_options;

int main(int argc, char *argv[])
  {
    string infilename, outfilename; //storing names for input and root of output
    MTStationList MTSites; // object for the station data
    cout
        << " This is phasetensormap, calculate phasetensor elipses etc. from MT data"
        << endl; // write some info
    cout << " Reads in a list of files and outputs files for plotting with gmt"
        << endl;
    cout << " File endings will be automatically appended." << endl;
    cout
        << " For error calculation, numbers < 2 will be interpreted as no error calculation."
        << endl;
    cout << " This is Version: " << version << endl << endl;

    int nbootsamples = -1; //by default no bootstrap errors
    double scalefactor = 10; // the default scaling for phase tensor ellipses

    po::options_description desc("General options");
    desc.add_options()("help", "produce help message")("calcerr",
        po::value<int>(&nbootsamples)->default_value(-1),
        "Calculate error estimates")("scalefactor", po::value<double>(
        &scalefactor)->default_value(10.0),
        "Scalefactor for phase tensor ellipse size in plots.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
      {
        std::cout << desc << "\n";
        return 1;
      }

    infilename = AskFilename("File with station names: ");
    try
      {
        MTSites.GetData(infilename); //try to read in all station data
        if (MTSites.GetCommonFrequencies().size() == 0)
          {
            cerr << "No common frequencies found !";
            return 100;
          }
      } catch (FatalException &e)
      {
        cerr << e.what() << endl; // if something fails print error
        return -1; // and stop execution
      }
    outfilename = AskFilename("Output Filename Root: ");

    cout << "Available Periods: " << MTSites.GetCommonFrequencies().size()
        << endl;

    for (trealdata::const_iterator frequencies =
        MTSites.GetCommonFrequencies().begin(); frequencies
        != MTSites.GetCommonFrequencies().end(); ++frequencies)
      {
        cout << setw(9) << setfill(' ') << setprecision(4) << distance(
            MTSites.GetCommonFrequencies().begin(), frequencies);
        cout << setw(15) << setfill(' ') << setprecision(8) << 1.
            / (*frequencies) << endl;
      }
    int freqindex;
    cout << "Select frequency Index: ";
    cin >> freqindex;

    ofstream outfile((outfilename + ".ptensor").c_str());
    for (vector<MTStation>::iterator it = MTSites.GetList().begin(); it
        != MTSites.GetList().end(); ++it)
      {
        int realfreqindex = MTSites.GetComFreqIndices().at(distance(
            MTSites.GetList().begin(), it)).at(freqindex);
        double rotangle = (it->GetMTData().at(realfreqindex).GetPhiStrike())
            * 180. / PI;

        //cout << it->GetName() << " " << 1./it->GetFrequencies().at(realfreqindex) << " " << it->GetMTData().at(realfreqindex).GetZxx() <<  endl;
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << it->GetLongitude();
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << it->GetLatitude();
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << it->GetMTData().at(realfreqindex).GetBeta_phi() * 180. / PI;
        outfile << setw(12) << setfill(' ') << setprecision(4) << 90 - rotangle;
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << it->GetMTData().at(realfreqindex).GetPhiMax() * scalefactor;
        outfile << setw(12) << setfill(' ') << setprecision(4)
            << it->GetMTData().at(realfreqindex).GetPhiMin() * scalefactor
            << endl;

      }
    outfile.close();

    PrintComponent<double> ((outfilename + ".ptskew"), &MTTensor::GetBeta_phi,
        MTSites, freqindex, gplib::absangle(), nbootsamples);
    PrintComponent<double> ((outfilename + ".ptstrike"),
        &MTTensor::GetPhiStrike, MTSites, freqindex, boost::bind(multiplies<
            double> (), _1, -180. / PI), nbootsamples);
    PrintComponent<double> ((outfilename + ".bstrike"), &MTTensor::GetAlpha,
        MTSites, freqindex, boost::bind(multiplies<double> (), _1, 180. / PI),
        nbootsamples);
    PrintComponent<double> ((outfilename + ".ptellip"), &MTTensor::GetPhiEllip,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptmin"), &MTTensor::GetPhiMin,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptmax"), &MTTensor::GetPhiMax,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi1"), &MTTensor::GetPhi1,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi2"), &MTTensor::GetPhi2,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi3"), &MTTensor::GetPhi3,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi11"), &MTTensor::GetPhi11,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi12"), &MTTensor::GetPhi12,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi21"), &MTTensor::GetPhi21,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    PrintComponent<double> ((outfilename + ".ptphi22"), &MTTensor::GetPhi22,
        MTSites, freqindex, gplib::nomod<double>, nbootsamples);
    return (0);
  }

