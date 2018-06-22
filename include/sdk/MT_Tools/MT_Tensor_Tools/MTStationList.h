#ifndef CMTSTATIONLIST_H
#define CMTSTATIONLIST_H

#include <string>
#include "MTStation.h"
#include <vector>
#include <utility>
#include "StationParser.h"
#include "FatalException.h"
#include "convert.h"
#include "stringcompare.h"
#include "NumUtil.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <utility>
#include <boost/bind.hpp>
using namespace std;

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    typedef std::vector<MTStation> tStationList;
    //! MTStationList holds a number of MTSites, usually associated with a single project, line, etc.
    class MTStationList
      {
    private:
      //! The relative tolerance at which we accept two frequencies as being euqal
      double tolerance;
      //! A vector that holds the frequencies common to all sites
      trealdata commonfrequencies;
      //! A vector that holds the storage index for each of the commonfrequencies for each site
      std::vector<tindexvector> cfindices;
      //! The vector holding the actual site data
      tStationList StationData;
      //! A helper function that finds all common frequencies
      void FindCommon(void)
      {
        trealdata masterfrequencies(StationData.begin()->GetFrequencies());

        commonfrequencies.clear();
        for (unsigned int i = 0; i < masterfrequencies.size(); ++i)
          {
            bool iscommon = true;
            for (size_t j = 0; j < StationData.size(); ++j)
              {
                bool foundfrequency = false;
                size_t k = 0;
                while ((foundfrequency == false) && (k
                    < StationData.at(j).GetFrequencies().size()))
                  {
                    if (fcmp(masterfrequencies.at(i),
                        StationData.at(j).GetFrequencies().at(k), tolerance)
                        == 0)
                      foundfrequency = true;
                    ++k;
                  }
                // if foundfrequency is false once, iscommon will be false for the rest of the loop
                iscommon = (iscommon && foundfrequency);
              }
            if (iscommon)
              commonfrequencies.push_back(masterfrequencies.at(i));
          }
        tindexvector indices(commonfrequencies.size(), -1);
        cfindices.assign(StationData.size(), indices);
        for (unsigned int i = 0; i < commonfrequencies.size(); ++i)
          {
            for (unsigned int j = 0; j < StationData.size(); ++j)
              {
                double bestfit = 1e32;
                for (size_t k = 0; k < StationData.at(j).GetFrequencies().size(); ++k)
                  {
                    if ((fcmp(commonfrequencies.at(i),
                        StationData.at(j).GetFrequencies().at(k), tolerance)
                        == 0) && (abs(commonfrequencies.at(i) - StationData.at(
                        j).GetFrequencies().at(k)) < bestfit))
                      {
                        cfindices.at(j).at(i) = k;
                        bestfit = commonfrequencies.at(i)
                            - StationData.at(j).GetFrequencies().at(k);
                      }
                  }
              }
          }
      }

    public:
      //! Access to the complete vector of Stations
      tStationList &GetList()
        {
          return StationData;
        }
      //! Read a list of filenames and the associated data in those files to fill the list
      void GetData(const std::string filename)
      {
        ifstream infile(filename.c_str());

        if (infile)
          {
            //first parse the file with the station information
            StationParser parser;
            parser.ParseFile(infile);
            //go through all the station names and read in the data for each station
            for (unsigned int i = 0; i < parser.Stationnames.size(); ++i)
              {
                cout << "Working on file " << parser.Stationnames.at(i) << endl;
                try
                  {
                    MTStation CurrentStation;
                    CurrentStation.GetData(parser.Stationnames.at(i));
                    //we can have a stationfile with lat/lon information or without it
                    //if yes we use this as position information
                    if (parser.HasLatLong.at(i))
                      {
                        CurrentStation.SetLongitude(parser.Longitudes.at(i));
                        CurrentStation.SetLatitude(parser.Latitudes.at(i));
                      }
                    StationData.push_back(CurrentStation);
                  } catch (FatalException &e)
                  {
                    cerr << e.what() << " Skipping file !" << endl;
                  }
              }
          }
        else
          {
            throw FatalException("File not found: " + filename);
          }
        //if we did read in some data we create an index of common frequencies in each file
        if (!StationData.empty())
          {
            FindCommon();
          }
      }
      //! Write the names of the sites in the current list to a file
      void WriteList(const std::string filename = "station.list")
      {
        ofstream outfile(filename.c_str());
        for (vector<MTStation>::iterator CurrentStation = StationData.begin(); CurrentStation
            != StationData.end(); CurrentStation++)
          {
            outfile << CurrentStation->GetName();
            outfile << setfill(' ') << setw(15) << resetiosflags(ios::fixed);
            outfile << CurrentStation->GetLongitude() << " ";
            outfile << setfill(' ') << setw(15) << resetiosflags(ios::fixed);
            outfile << CurrentStation->GetLatitude();
            outfile << endl;
          }
      }
      //! Write the data of each station to an individual file
      void WriteAllData()
      {
        //for each station in the station list we write back the data in the original format
        for (std::vector<MTStation>::iterator CurrentStation =
            StationData.begin(); CurrentStation != StationData.end(); CurrentStation++)
          CurrentStation->WriteBack();
      }

      //! Get a vector that for each site contains the indices to the common frequencies
      const std::vector<tindexvector> &GetComFreqIndices()
        {
          return cfindices;
        }
      //! Get a vector with frequencies that are common to all sites
      const trealdata &GetCommonFrequencies()
        {
          return commonfrequencies;
        }
      //! Get a reference to a site at a given index
      MTStation& at(int loc)
      {
        return (StationData.at(loc));
      }

      MTStationList(double freqtol = 0.05):
          tolerance(freqtol)
        {
        }
      virtual ~MTStationList();
      };

    class HasSameName: public std::binary_function<MTStation, MTStation, bool>
      {
    public:
      bool inline operator()(MTStation a, MTStation b)
        {
          // if a does not precede b and b does not precede a, they have the same name , concept of equivalence,
          //Effective STL Item 19, page 84
          return !ciStringCompare(a.GetName(), b.GetName())
              && !ciStringCompare(b.GetName(), a.GetName());
        }
      };

    typedef std::vector<std::pair<MTStation*, MTStation*> > tStatSyncPair;
    //! Take two different site Lists of arguments and return a vector of pairs that point to the sites that correspond to each other
    tStatSyncPair FindCorrespondingSites(tStationList &MasterList,
        tStationList &SlaveList)
    {
      std::vector<std::pair<MTStation*, MTStation*> > CorrespondingSites;
      for (size_t i = 0; i < MasterList.size(); ++i)
        {
          tStationList::iterator slaveit = find_if(SlaveList.begin(),
              SlaveList.end(), boost::bind(HasSameName(), MasterList.at(i),
                  _1)); //find site with same name in SlaveList
          if (slaveit != SlaveList.end())
            CorrespondingSites.push_back(std::make_pair(&MasterList.at(i),
                &*slaveit));
          else
            std::cerr << "Not found: " << MasterList.at(i).GetName()
                << std::endl;
        }
      return CorrespondingSites;
    }
  /* @} */
  }
#endif // CMTSTATIONLIST_H
