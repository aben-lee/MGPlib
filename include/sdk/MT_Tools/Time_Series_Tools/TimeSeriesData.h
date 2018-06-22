
#ifndef CTIMESERIESDATA_H
#define CTIMESERIESDATA_H
#include "TimeSeries.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include "BirrpAsciiFormat.h"
#include "MtuFormat.h"
#include "CsvFormat.h"
#include "LemiTsFormat.h"
#include "FatalException.h"
#include "convert.h"
#include "Util.h"
#include <iostream>

using namespace std;

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! ttsdatatype is used to store the source the data was read from
    enum ttsdatatype
      {
      tsunknown, mtu, birrp, csv, lemi
      };

    //! TimeSeriesData stores  a pointer to the different components of magnetotelluric data and provides functions to read and write it to files

    /*! This should be made consistent with the corresponding Seismic data at some point
     */
    class TimeSeriesData
      {
    private:
      //! the sitename
      std::string name;
      //! the type of data
      ttsdatatype datatype;
      //! a pointer to the actual data object
      boost::shared_ptr<TimeSeries> Data;
    public:
      //! return a reference to the actual object stored in the pointer
      TimeSeries &GetData()
        {
          return *Data;
        }
      //! GetData reads in data from a file and determines the type from the ending
      void GetData(std::string filename)
      {
        string ending;
        //we identify the type of data by the file extension
        ending = GetFileExtension(filename);
        //Phoenix MTU data can have different endings depending on the sampling frequency
        if (ending == ".ts3" || ending == ".TS3" || ending == ".ts4" || ending
            == ".TS4" || ending == ".ts5" || ending == ".TS5")
          {
            Data = boost::shared_ptr<TimeSeries>(new MtuFormat);
            datatype = mtu;
          }
        //asc is the format used by birrp, basically just columns of numbers
        else if (ending == ".asc")
          {
            Data = boost::shared_ptr<TimeSeries>(new BirrpAsciiFormat);
            datatype = birrp;
          }
        //comma separated values have the ending .csv
        else if (ending == ".csv")
          {
            Data = boost::shared_ptr<TimeSeries>(new CsvFormat);
            datatype = csv;
          }
        //the lemi instruments produce ascii files with additional columns
        else if (ending == ".lem")
          {
            Data = boost::shared_ptr<TimeSeries>(new LemiTsFormat);
            datatype = lemi;
          }
        else
          {
            datatype = tsunknown;
            throw FatalException(
                "Unknown data format or file does not exist : " + filename);
          }
        name = filename;
        unsigned int dotpos = name.find('.', 0);
        if (dotpos != string::npos)
          name.erase(dotpos);
        Data->GetData(filename);
      }
      //! Write data to file in Phoenix MTU format
      void WriteAsMtu(std::string filename_base)
      {
        if (datatype == mtu)
          {
            switch (int(Data->GetSamplerate()))
              {
            case 2400:
              Data->WriteData(filename_base + ".ts3");
              break;
            case 150:
              Data->WriteData(filename_base + ".ts4");
              break;
            case 15:
              Data->WriteData(filename_base + ".ts5");
              break;
            default:
              throw FatalException(
                  "Unknown samplerate ! Cannot write file. Value is: "
                      + stringify(Data->GetSamplerate()));
              break;
              }
          }
        else
          {
            throw FatalException("Data conversion not implemented yet ! ");
          }
      }

      //! Write data to file in ascii format for birrp processing
      void WriteAsBirrp(std::string filename_base)
      {
        //return static_cast<CBirrpAsciiFormat*>(Data)->WriteData(filename_base+".asc");
        if (datatype == birrp)
          Data->WriteData(filename_base + ".asc");
        else
          {
            BirrpAsciiFormat BirrpData;
            BirrpData = *Data;
            BirrpData.WriteData(filename_base + ".asc");
          }
      }
      //! Write data as comma seperated ascii file
      void WriteAsCsv(std::string filename_base)
      {
        throw FatalException("Csv write not implemented yet ! ");
      }
      //! Write as file in Lemi compatible format
      void WriteAsLemi(std::string filename_base)
      {
        if (datatype == lemi)
          Data->WriteData(filename_base + ".lem");
        else
          {
            LemiTsFormat LemiData;
            LemiData = *Data;
            LemiData.WriteData(filename_base + ".lem");
          }
      }
      //! Write in the format it was originally read in
      void WriteBack(std::string filename_base)
      {
        switch (datatype)
          {
        case lemi:
          WriteAsLemi(filename_base);
          break;
        case birrp:
          WriteAsBirrp(filename_base);
          break;
        case mtu:
          WriteAsMtu(filename_base);
          break;
        case csv:
          WriteAsCsv(filename_base);
          break;
        default:
          throw FatalException("Cannot write back data ! Unknown datatype !");
          break;
          }
      }
      TimeSeriesData()
      {

      }
      virtual ~TimeSeriesData()
      {

      }
      //! The copy constructor
      TimeSeriesData& operator=(const TimeSeriesData& source)
      {
        if (this != &source)
          {
            this->name = source.name;
            this->datatype = source.datatype;
            //TODO introduce virtual constructors or redesign read/write mechanism
            this->Data = source.Data;
          }
        return *this;
      }

      };
  /* @} */
  }
#endif // CTIMESERIESDATA_H
