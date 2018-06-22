#ifndef SEISMICSTATIONLIST_H_
#define SEISMICSTATIONLIST_H_
#include <vector>
#include <boost/shared_ptr.hpp>
#include "SeismicDataComp.h"
#include "StationParser.h"
#include <fstream>
#include <iomanip>
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! Manages a collection of seismic traces, mainly provides functionality to read in data specified in a file with names
    class SeismicStationList
      {
    public:
      typedef std::vector<boost::shared_ptr<SeismicDataComp> > tseiscompvector;
    private:
      tseiscompvector StationList;
    public:
      //! Return the content of the list for manipulation
      tseiscompvector &GetList()
        {
          return StationList;
        }
      //! return a read only version of thelist
      const tseiscompvector &GetList() const
        {
          return StationList;
        }
      //! read in a file with names and optionally coordinates
      void ReadList(const std::string filename)
      {
        ifstream infile(filename.c_str());
        //we open file, check whether it opened OK
        if (infile)
          {
            StationParser parser;
            parser.ParseFile(infile);
            for (unsigned int i = 0; i < parser.Stationnames.size(); ++i)
              {
                //show information about each file
                cout << "Working on file " << parser.Stationnames.at(i) << endl;
                //create a shared pointer object
                boost::shared_ptr<SeismicDataComp> CurrentStation(
                    new SeismicDataComp);
                //and read in the data from the specified file
                CurrentStation->ReadData(parser.Stationnames.at(i));
                //we can optionally specify latitude and longitude information
                if (parser.HasLatLong.at(i))
                  {
                    //this overrides the information in the file
                    CurrentStation->SetStLo(parser.Longitudes.at(i));
                    CurrentStation->SetStLa(parser.Latitudes.at(i));
                  }
                StationList.push_back(CurrentStation);
              }
          }
        else
          {
            throw("File not found: " + filename);
          }
      }

      //! Write out a file with the names of the files in the current list
      void WriteList(const std::string filename = "station.list")
      {
        ofstream outfile(filename.c_str());
        //go through the vector of seismic component objects
        for (tseiscompvector::iterator CurrentStation = StationList.begin(); CurrentStation
            != StationList.end(); CurrentStation++)
          {
            //write out name, longitude and latitude with some formatting
            outfile << CurrentStation->get()->GetName();
            outfile << setfill(' ') << setw(15) << resetiosflags(ios::fixed);
            outfile << CurrentStation->get()->GetStLo() << " ";
            outfile << setfill(' ') << setw(15) << resetiosflags(ios::fixed);
            outfile << CurrentStation->get()->GetStLa();
            outfile << endl;
          }
      }
      //! Write out the data of the files in the list
      void WriteAllData()
      {
        //go through the vector of seismic components
        //and write each one in the format it was read in
        for (tseiscompvector::iterator CurrentStation = StationList.begin(); CurrentStation
            != StationList.end(); CurrentStation++)
          CurrentStation->get()->WriteBack();
      }
      SeismicStationList();
      virtual ~SeismicStationList();
      };
  /* @} */
  }
#endif /*SEISMICSTATIONLIST_H_*/
