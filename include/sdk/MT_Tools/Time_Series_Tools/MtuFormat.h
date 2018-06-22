
#ifndef _MTUFORMAT_INCLUDED_
#define _MTUFORMAT_INCLUDED_
#include "TimeSeries.h"
#include "FatalException.h"
#include <iostream>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/cast.hpp>
#include <time.h>

using namespace std;

#include <string>
#include <fstream>
namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! Read and write phoenix mtu binary files
    class MtuFormat: public TimeSeries
      {
        const char tagsize = 32;

    private:
      char startsec;
      char startmin;
      char starthr;
      char startday;
      char startmonth;
      char startyear;
      char startdow;
      char startcentury;
      int serialnumber;
      int nscans;
      char nchannels;
      char taglength;
      char status;
      char saturationflags;
      char futurereserved;
      double sampledenom;
      double sampleenum;
      char sampleunit;
      char samplelength;
      char rateunit;
      char clockstatus;
      int clockerror;
      char reserved[6];
      //! Read one record of data (header+data) from the filestream
      void ReadRecord(std::ifstream &infile)
      {
        unsigned char CurrentTag[tagsize];
        int recordlength;

        char *buffer;
        char *currentbyte;

        infile.read((char *) CurrentTag, tagsize);
        if (infile.good())
          {
            startsec = CurrentTag[0];
            startmin = CurrentTag[1];
            starthr = CurrentTag[2];
            startday = CurrentTag[3];
            startmonth = CurrentTag[4];
            startyear = CurrentTag[5];
            startdow = CurrentTag[6];
            startcentury = CurrentTag[7];
            serialnumber = CurrentTag[9] * 256 + CurrentTag[8];
            nscans = CurrentTag[11] * 256 + CurrentTag[10];
            nchannels = CurrentTag[12];
            taglength = CurrentTag[13];
            status = CurrentTag[14];
            saturationflags = CurrentTag[15];
            futurereserved = CurrentTag[16];
            samplelength = CurrentTag[17];
            sampledenom = boost::numeric_cast<double>(CurrentTag[19] * 256
                + CurrentTag[18]);
            sampleunit = CurrentTag[20];
            clockstatus = CurrentTag[21];
            clockerror = 16777216 * CurrentTag[25] + 65536 * CurrentTag[24]
                + 256 * CurrentTag[23] + CurrentTag[22];
            for (int i = 0; i < 6; ++i)
              reserved[i] = CurrentTag[i + 26];
            switch (sampleunit)
              {
            case 0:
              sampleenum = 1.0;
              break;
            case 1:
              sampleenum = 60.0;
              break;
            case '2':
              sampleenum = 3600.0;
              break;
            case '3':
              sampleenum = 3600.0 * 24.0;
              break;
              }
            const double samplerate = sampledenom / sampleenum;
            Hx.SetSamplerate(samplerate);
            Hy.SetSamplerate(samplerate);
            Hz.SetSamplerate(samplerate);
            Ex.SetSamplerate(samplerate);
            Ey.SetSamplerate(samplerate);
            recordlength = nscans * nchannels;

            TimeSeries::ttime basetime(boost::gregorian::date(startcentury
                * 100 + startyear, startmonth, startday),
                boost::posix_time::time_duration(starthr, startmin, startsec));

            buffer = new char[recordlength * samplelength];
            infile.read(buffer, recordlength * samplelength);
            currentbyte = buffer;
            for (int i = 0; i < nscans; ++i)
              {
                t.push_back(basetime + boost::posix_time::microseconds(
                    boost::numeric_cast<unsigned int>(i * 1000000.0
                        / samplerate)));
                ReadValue(Ex, currentbyte);
                currentbyte += samplelength;
                ReadValue(Ey, currentbyte);
                currentbyte += samplelength;
                ReadValue(Hx, currentbyte);
                currentbyte += samplelength;
                ReadValue(Hy, currentbyte);
                currentbyte += samplelength;
                ReadValue(Hz, currentbyte);
                currentbyte += samplelength;
              }
            delete[] buffer;
          }
      }
      //! Write a number to file in mtu binary format
      void WriteNum(double number, std::ofstream &outfile)
      {
        unsigned char high;
        unsigned char middle;
        unsigned char low;
        char buffer[3];
        unsigned int intnumber;
        if (number >= 0)
          intnumber = int(abs(floor(number)));
        else
          intnumber = ~int(abs(floor(number))) + 1;
        high = intnumber / 65536;
        middle = (intnumber % 65536) / 256;
        low = intnumber % 256;

        buffer[0] = low;
        buffer[1] = middle;
        buffer[2] = high;
        outfile.write(buffer, 3);
      }
      //! Convert raw bytes from mtu binary file to integer number
      int ByteToInt(unsigned char first, unsigned char second,
          unsigned char last)
      {
        const char highbit = 0x80;
        int value;
        if (last & highbit)
          {
            last = ~last;
            second = ~second;
            first = ~first;
            value = -(last * 65536 + second * 256 + first + 1);
          }
        else
          value = last * 65536 + second * 256 + first;
        return (value);
      }
      //! Convert byte sequence to a number and append to channel
      void ReadValue(TimeSeriesComponent &CurrChannel, char *pos)
      {
        unsigned char byte1, byte2, byte3;
        int datavalue;

        byte1 = *pos;
        byte2 = *(pos + 1);
        byte3 = *(pos + 2);
        datavalue = ByteToInt(byte1, byte2, byte3);
        CurrChannel.GetData().push_back(datavalue);
      }
      //! Set time information in header
      void UpDateHeader(unsigned char *&header, const int firstscan)
      {
        tm currtime = boost::posix_time::to_tm(t.at(firstscan)); //convert boost time to old c-style struct
        header[0] = boost::numeric_cast<char>(currtime.tm_sec); // read out seconds part
        header[1] = boost::numeric_cast<char>(currtime.tm_min); //boost::numeric_cast takes care of type conversion
        header[2] = boost::numeric_cast<char>(currtime.tm_hour);
        boost::gregorian::greg_year_month_day currdate =
            t.at(firstscan).date().year_month_day(); //convert date
        header[3] = boost::numeric_cast<char>(currdate.day.as_number());
        header[4] = boost::numeric_cast<char>(currdate.month.as_number());
        header[5] = boost::numeric_cast<char>(currdate.year % 100);
        header[6] = boost::numeric_cast<char>(currtime.tm_wday); // this is the day of week (between 0 and 6)
        header[7] = boost::numeric_cast<char>(currdate.year / 100);
      }
    public:
      //! remove the "bad" flag from the header
      void MakeGood()
      {
        status = 0;
        saturationflags = 0;
      }
      MtuFormat()
      {

      }
      virtual ~MtuFormat()
      {

      }
      virtual void GetData(const std::string filename)
      {
        ifstream infile(filename.c_str(), ios::binary);
        if (infile)
          {
            while (infile.good())
              {
                ReadRecord(infile);
              }
          }
        else
          {
            throw FatalException("Infile does not exist: " + filename);
          }
      }
      virtual void GetData()
      {

      }
      virtual void WriteData(const std::string filename)
      {

        int nrecords = 0;
        int firstscan = 0;
        unsigned char *header = new unsigned char[tagsize];

        header[8] = serialnumber % 256;
        header[9] = serialnumber / 256;
        header[10] = nscans % 256;
        header[11] = nscans / 256;
        header[12] = nchannels;
        header[13] = taglength;
        header[14] = status;
        header[15] = saturationflags;
        header[16] = futurereserved;
        header[17] = samplelength;
        header[18] = boost::numeric_cast<unsigned int>(sampledenom) % 256;
        header[19] = boost::numeric_cast<unsigned int>(sampledenom) / 256;
        header[20] = sampleunit;
        header[21] = clockstatus;
        header[22] = clockerror % 256;
        header[23] = (clockerror % 65536) / 256;
        header[24] = (clockerror % 16777216) / 65536;
        header[25] = clockerror / 16777216;
        for (int i = 0; i < 6; ++i)
          header[i + 26] = reserved[i];
        nrecords = Size() / nscans;

        ofstream outfile(filename.c_str());
        for (int i = 0; i < nrecords; ++i)
          {
            UpDateHeader(header, firstscan);
            outfile.write((char *) header, tagsize);
            for (int j = 0; j < nscans; ++j)
              {

                WriteNum(Ex.GetData().at(firstscan + j), outfile);
                WriteNum(Ey.GetData().at(firstscan + j), outfile);
                WriteNum(Hx.GetData().at(firstscan + j), outfile);
                WriteNum(Hy.GetData().at(firstscan + j), outfile);
                WriteNum(Hz.GetData().at(firstscan + j), outfile);
              }
            firstscan += nscans;

          }
      }

      MtuFormat& operator=(MtuFormat &source)
      {
        if (this != &source)
          {
            this->TimeSeries::operator=(source);
          }
        return *this;
      }

      MtuFormat& operator=(TimeSeries &source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }
      };
  /* @} */
  }
#endif
