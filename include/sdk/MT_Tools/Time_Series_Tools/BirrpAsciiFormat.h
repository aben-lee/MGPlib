
#ifndef _BIRRPASCIIFORMAT_INCLUDED_
#define _BIRRPASCIIFORMAT_INCLUDED_
#include "TimeSeries.h"
#include "MtuFormat.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <FatalException.h>
#include <boost/cast.hpp>

using namespace std;

namespace gplib
  {
    class MtuFormat;

    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! BirrpAsciiFormat reads and stores MT data in the ascii format used by the birrp processing software
    class BirrpAsciiFormat: public TimeSeries
      {
    private:
    public:
        BirrpAsciiFormat()
        {

        }
        ~BirrpAsciiFormat()
        {

        }
        //! Read data in birrp ascii format from a file called filename
      virtual void GetData(const std::string filename)
      {
        ifstream infile(filename.c_str());
        double currex, currey, currhx, currhy, currhz; // the current samples in the file
        const double birrp_samplerate = 1.0; //arbitrary sampling rate, birrp format does not contain rate
        // the birrp format does not store time information, so we set an arbitrary start time
        TimeSeries::ttime basetime(boost::gregorian::date(2004, 1, 1),
            boost::posix_time::time_duration(12, 0, 0));
        while (infile.good())
          {
            infile.precision(15);
            infile >> currex >> currey >> currhx >> currhy >> currhz;
            if (infile.good())
              {
                Ex.GetData().push_back(currex);
                Ey.GetData().push_back(currey);
                Hx.GetData().push_back(currhx);
                Hy.GetData().push_back(currhy);
                Hz.GetData().push_back(currhz);
                t.push_back(basetime);
                basetime += boost::posix_time::seconds(
                    boost::numeric_cast<int>(birrp_samplerate)); // we assume an arbitrary sampling rate of 1 second
              }
          }
        //if we didn't stop because the file ended
        if (!infile.eof())
          {
            throw FatalException("Problem reading from file: " + filename);
          }
        Hx.SetSamplerate(birrp_samplerate); //we set the samplerate for each component, this value is arbitrary, but we don't have information
        Hy.SetSamplerate(birrp_samplerate);
        Hz.SetSamplerate(birrp_samplerate);
        Ex.SetSamplerate(birrp_samplerate);
        Ey.SetSamplerate(birrp_samplerate);
      }

      //! Write data in birrp ascii format to a file called filename
      virtual void WriteData(const std::string filename)
      {
        ofstream outfile(filename.c_str());
        TimeSeriesComponent::tdatait exit, eyit, hxit, hyit, hzit;
        //if any of the components has a different number of points throw and error
        const size_t exsize = Size();

        exit = Ex.GetData().begin();
        eyit = Ey.GetData().begin();
        hxit = Hx.GetData().begin();
        hyit = Hy.GetData().begin();
        hzit = Hz.GetData().begin();
        // write a simple ascii file with 5 values in one row
        while (exit != Ex.GetData().end())
          {
            outfile.precision(8);
            outfile << setw(20) << *exit << " ";
            outfile << setw(20) << *eyit << " ";
            outfile << setw(20) << *hxit << " ";
            outfile << setw(20) << *hyit << " ";
            outfile << setw(20) << *hzit << endl;
            exit++;
            eyit++;
            hzit++;
            hyit++;
            hxit++;
          }
      }

      BirrpAsciiFormat& operator=(BirrpAsciiFormat& source)
      {
        if (this != &source)
          {
            this->TimeSeries::operator=(source);
          }
        return *this;
      }

      BirrpAsciiFormat& operator=(MtuFormat& source)
      {

        this->TimeSeries::operator=(source);
        return *this;
      }

      BirrpAsciiFormat& operator=(TimeSeries& source)
      {

        this->TimeSeries::operator=(source);
        return *this;
      }
      };
  /* @} */
  }
#endif

