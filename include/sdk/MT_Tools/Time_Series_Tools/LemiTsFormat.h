#ifndef _CLEMITSFORMAT_H_
#define _CLEMITSFORMAT_H_

#include "TimeSeries.h"
#include "MtuFormat.h"
#include "BirrpAsciiFormat.h"
#include "FatalException.h"
#include <boost/cast.hpp>
#include <fstream>

using namespace std;

namespace gplib
  {
    class MtuFormat;
    class BirrpAsciiFormat;

    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! Read and write ascii files produced by the LEMI instruments
    class LemiTsFormat: public TimeSeries
      {
    public:
        LemiTsFormat()
        {

        }
        virtual ~LemiTsFormat()
        {

        }
        virtual void GetData()
      {
          throw FatalException("Not implemented");
      }
      virtual void GetData(const std::string filename)
      {
        ifstream infile(filename.c_str());
        double rawsecond, fraction; //the second information stored in the file
        int year, month, day, hour, minute, second;
        const double rate = 4.0; // the fixed sampling rate is 4 Hz
        double number;

        while (infile.good())
          {
            infile.precision(15);
            infile >> year >> month >> day >> hour >> minute >> rawsecond; //read in time information
            second = static_cast<int> (rawsecond); //chop of the fractional part
            fraction = rawsecond - static_cast<int> (rawsecond); // calculate the fractional part
            TimeSeries::ttime currtime(
                boost::gregorian::date(year, month, day),
                boost::posix_time::time_duration(hour, minute, second)); //construct time structure
            currtime += boost::posix_time::microseconds(
                boost::numeric_cast<int>(fraction * 1000000));
            t.push_back(currtime);
            if (infile.good()) //if read was successfull
              {
                infile >> number;
                Hx.GetData().push_back(number);
                infile >> number;
                Hy.GetData().push_back(number);
                infile >> number;
                Hz.GetData().push_back(number);
                infile >> number >> number >> number; //we skip the two temperature values and read Ex
                Ex.GetData().push_back(number);
                infile >> number;
                Ey.GetData().push_back(number);
                infile >> number >> number >> number; // we skip the two additional channels and the extra time information
              }
          }
        if (!infile.eof())
          {
            throw FatalException("Problem reading from file: " + filename);
          }
        Hx.SetSamplerate(rate);
        Hy.SetSamplerate(rate);
        Hz.SetSamplerate(rate);
        Ex.SetSamplerate(rate);
        Ey.SetSamplerate(rate);
      }
      virtual void WriteData(const std::string filename)
      {
        throw FatalException("Not implemented");
      }
      LemiTsFormat& operator=(BirrpAsciiFormat& source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }
      LemiTsFormat& operator=(MtuFormat& source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }
      LemiTsFormat& operator=(TimeSeries& source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }
      LemiTsFormat& operator=(LemiTsFormat& source)
      {
        if (this != &source)
          {
            this->TimeSeries::operator=(source);
          }
        return *this;
      }
      };
  /* @} */
  }
#endif /*_CLEMITSFORMAT_H_*/
