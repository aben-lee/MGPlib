//============================================================================
// Name        : StationParser.h
// Author      : Mar 5, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================


#ifndef STATIONPARSER_H_
#define STATIONPARSER_H_

#include <vector>
#include <iostream>
#include "FatalException.h"
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include "convert.h"

namespace gplib
  {
  /** \addtogroup mttools MT data analysis, processing and inversion */
  /* @{ */
    //! Read in an ascii file containing  a list of filenames for each station and optionally position
    /*! This class is used as a helper for programs that need to read in information from several
     * separate files. It reads in an ascii file in the format
     * name   lat long
     * where lat and long are optional and stores these values in vectors that can be accessed
     * by other classes or programs.
     */
    class StationParser
      {
        //! Analyze the content of a single line in the station file
        /*! This function takes a single line from the station file
         * and splits it into tokens. Each line should consist of the stationname
         * and optionally latitude and longitude.
         * @param Line The string with the line as read from the station file
         * @param stationname The name of the station
         * @param haslatlong Does the line contain latitude/longitude information
         * @param latitude The latitude from the file, or zero if not set
         * @param longitude The longitude from the file, or zero if not set
         * @return Did we read the line successfully
         */
        bool ReadStationLine(const std::string &Line, std::string &stationname,
            bool &haslatlong, double &latitude, double &longitude)
          {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tok(Line, sep);
            haslatlong = false;
            latitude = 0.0;
            longitude = 0.0;
            tokenizer::iterator it = tok.begin();
            if (it != tok.end())
              stationname = *it;
            else
              return false;
            it++;
            if (it != tok.end())
              {
                gplib::convert(it.current_token(), latitude);
                it++;
                gplib::convert(*it, longitude);
                haslatlong = true;
              }
            return true;
          }

    public:
      //! Vector of latitudes for each station, zero of no value in the file
      std::vector<double> Latitudes;
      //! Vector of longitudes for each station, zero of no value in the file
      std::vector<double> Longitudes;
      //! Do we have valid lat/lon information for each station
      std::vector<bool> HasLatLong;
      //! Name of the different station, usually a filename that is used in other classes
      std::vector<std::string> Stationnames;
      //! Read in lines from an ascii file and parse each line for station information
      void ParseFile(std::istream& in)
      {
        while (in.good())
          {
            const size_t linelength = 1024;
            char currentline[linelength];
            in.getline(currentline, linelength, '\n');
            if (in.good())
              {
                std::string stationname;
                bool hasll;
                double latitude, longitude;
                if (ReadStationLine(currentline,
                    stationname, hasll, latitude, longitude))
                  {
                    Stationnames.push_back(stationname);
                    HasLatLong.push_back(hasll);
                    Latitudes.push_back(latitude);
                    Longitudes.push_back(longitude);
                  }
                else
                  throw gplib::FatalException("Invalid entry in station file !");
              }
          }

      }
      StationParser()
	  {
	  }
      virtual ~StationParser()
	  {
	  }
    };
    /* @} */
  }

#endif /* STATIONPARSER_H_ */
