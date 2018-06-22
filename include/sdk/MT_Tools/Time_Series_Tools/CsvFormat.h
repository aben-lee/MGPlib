#ifndef _CSVFORMAT_INCLUDED_
#define _CSVFORMAT_INCLUDED_
#include "TimeSeries.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "MtuFormat.h"
#include "FatalException.h"
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

namespace gplib
  {
    class MtuFormat;

    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! This class reads and writes data from Comma Separated Files CSV as produced by Excel etc.  this particular flavour
    // aims at files produced by phoenix software
    class CsvFormat: public TimeSeries
      {
    public:
        CsvFormat()
        {

        }
        virtual ~CsvFormat()
        {

        }
        virtual void GetData()
        {

        }

        virtual void GetData(const std::string filename)
      {
        ifstream infile(filename.c_str());
        char dummy[255];
        string line1, line2, line3, line4, line5, line6;
        double number;
        vector<double>::iterator outit;

        infile.getline(dummy, sizeof(dummy));
        infile.getline(dummy, sizeof(dummy));
        infile.getline(dummy, sizeof(dummy));
        infile.getline(dummy, sizeof(dummy));
        infile.getline(dummy, sizeof(dummy));
        infile.getline(dummy, sizeof(dummy));
        while (infile.good())
          {
            infile.precision(8);
            //infile >> number;
            //t.push_back(number);
            //infile.ignore(256,',');

            infile >> number;
            if (infile.good())
              {
                Ex.GetData().push_back(number);
                infile.ignore(256, ',');

                infile >> number;
                Ey.GetData().push_back(number);
                infile.ignore(256, ',');

                infile >> number;
                Hx.GetData().push_back(number);
                infile.ignore(256, ',');

                infile >> number;
                Hy.GetData().push_back(number);
                infile.ignore(256, ',');

                infile >> number;
                Hz.GetData().push_back(number);
                infile.ignore(256, ',');
              }
          }
        if (!infile.eof())
          {
            throw FatalException("Problem reading file: " + filename);
          }
      }
      virtual void WriteData(const std::string filename)
      {
        ofstream outfile;

        outfile.open(filename.c_str());
        for (unsigned int i = 0; i < Ex.GetData().size(); ++i)
          {
            outfile.precision(8);
            outfile << setw(10) << boost::posix_time::to_simple_string(t.at(i))
                << ",";
            outfile << setw(10) << Ex.GetData().at(i) << ",";
            outfile << setw(10) << Ey.GetData().at(i) << ",";
            outfile << setw(10) << Hx.GetData().at(i) << ",";
            outfile << setw(10) << Hy.GetData().at(i) << ",";
            outfile << setw(10) << Hz.GetData().at(i) << endl;
          }
        outfile.close();

      }

      CsvFormat& operator=(CsvFormat& source)
      {
        if (this != &source)
          {
            this->TimeSeries::operator=(source);
          }
        return *this;
      }

      CsvFormat& operator=(MtuFormat& source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }

      CsvFormat& operator=(TimeSeries& source)
      {
        this->TimeSeries::operator=(source);
        return *this;
      }
      };
  /* @} */
  }
#endif
