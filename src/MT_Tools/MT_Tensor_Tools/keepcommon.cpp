#include <iostream>
#include <iomanip>
#include <vector>
#include "MTStationList.h"
#include "Util.h"
using namespace std;
using namespace gplib;

int main(int argc, char* argv[])
  {
    string version = "$Id: keepcommon.cpp 1886 2014-10-29 12:38:46Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << " Read in several files with MT tensor data" << endl;
    cout << " and keep the common frequencies. The files will be written in" << endl;
    cout
        << " .mtt format. If the input files were in that format they will be overwritten"
        << endl;
    cout << endl << endl;

    try
      {
        MTStationList MTSites;
        std::string infilename;
        //read the file with the name of stations either directly from the command line
        if (argc > 1)
          {
            infilename = argv[1];
          }
        else
          {
            //or prompt for it.
            infilename = AskFilename("Station Filename: ");
          }

        MTSites.GetData(infilename);
        const size_t nstats = MTSites.GetList().size();
        //create a display of frequencies in the different files
        //first column is the filename, then a column for each frequency
        //in the first data files
        std::cout << "Frequency matrix \n" << std::endl;
        std::cout << std::setw(12) << "Filename ";
        for (double freq : MTSites.at(0).GetFrequencies())
          {
            std::cout << std::setw(10) << freq;
          }
        std::cout << std::endl;

        //the relative tolerance with which we consider two frequencies equal
        const double tolerance = 0.05;
        for (size_t i = 0; i < nstats; ++i)
          {
            //for each site we output its name in the first column
            std::cout << std::setw(10) << MTSites.at(i).GetName();
            const int nfreq = MTSites.at(0).GetFrequencies().size();
            std::vector<int> havefreq(nfreq, 0);
            //then we go through all the frequencies for that site
            for (size_t j = 0; j < nfreq; ++j)
              {
                bool foundfrequency = false;
                size_t k = 0;
                //as the different sites can have different order for
                //the frequencies we have to go through all of them
                //until we found a correspondance with the first site
                //or reached the end
                while ((foundfrequency == false)
                    && (k < MTSites.at(i).GetFrequencies().size()))
                  {
                    if (fcmp(MTSites.at(0).GetFrequencies().at(j),
                        MTSites.at(i).GetFrequencies().at(k), tolerance) == 0)
                      foundfrequency = true;
                    ++k;
                  }
                //if we found the frequency, we mark it in the vector
                havefreq.at(j) = foundfrequency;
              }
            //output the vector of found frequencies in the same order
            //as the frequencies in the first file
            for (int tick : havefreq)
              {
                std::cout << std::setw(10) << tick;
              }
            std::cout << std::endl;
          }

        //now we go through the sites again to mark the ones
        //that are not in the master file
        for (size_t i = 0; i < nstats; ++i)
          {
            trealdata freqs(MTSites.at(i).GetFrequencies());
            const int nfreq = MTSites.at(i).GetFrequencies().size();

            for (int j = 0; j < nfreq; ++j)
              {
                if (find(MTSites.GetComFreqIndices().at(i).begin(),
                    MTSites.GetComFreqIndices().at(i).end(), j)
                    == MTSites.GetComFreqIndices().at(i).end())
                  {
                    freqs.at(j) = 0;
                  }
              }

            MTSites.at(i).SetFrequencies(freqs);
            MTSites.at(i).WriteAsMtt(MTSites.at(i).GetName());

          }
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      }
  }

