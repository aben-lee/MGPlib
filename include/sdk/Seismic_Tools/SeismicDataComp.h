#ifndef CSEISMICDATACOMP_H
#define CSEISMICDATACOMP_H
#include <string>
#include "types.h" 
#include "TimeSeriesComponent.h"
#include <algorithm>
#include <fstream>
#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/cstdint.hpp>
#include "FatalException.h"

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    class SeismicDataComp: public TimeSeriesComponent
      {
    public:
      enum tseismicdataformat
        {
        unknownseis, sac, sks, head, ascii
        };
      double GetB() const
        {
          return b;
        }
      void SetB(const double theb)
        {
          b = theb;
        }
      tseismicdataformat GetFormat()
        {
          return dataformat;
        }
      //! Return the latitude of the station
      double GetStLa() const
        {
          return stla;
        }
      //! Set the latitude of the station
      void SetStLa(const double lat)
        {
          stla = lat;
        }
      //! Get the longitude of the station
      double GetStLo() const
        {
          return stlo;
        }
      //! Set the longitude of the station
      void SetStLo(const double lon)
        {
          stla = lon;
        }
      //! Get the elevation of the station in m
      double GetStEl() const
        {
          return stel;
        }
      //! Get the depth of the station below the ground in m
      double GetStDp() const
        {
          return stdp;
        }
      //! Get the latitude of the event
      double GetEvLa() const
        {
          return evla;
        }
      //! Get the longitude of the event
      double GetEvLo() const
        {
          return evlo;
        }
      //! Get the elevation of the event
      double GetEvEl() const
        {
          return evel;
        }
      //! Get the depth of the event
      double GetEvDp() const
        {
          return evdp;
        }
      //! Get the magnitude of the event
      double GetMag() const
        {
          return mag;
        }
      //! Get the distance between event and station
      double GetDist() const
        {
          return dist;
        }
      //! Get the azimuth of the event
      double GetAz() const
        {
          return az;
        }
      //! Get the back-azimuth of the event
      double GetBaz() const
        {
          return baz;
        }
      //! Get the distance between station and event along a great circle
      double GetGcarc() const
        {
          return gcarc;
        }
      //! Read in data from a file, as we cannot determine the type from the ending we have to provide it
      int
          ReadData(const std::string &filename, tseismicdataformat format = sac)
      {
        if (!boost::filesystem::exists(filename))
          throw FatalException("File does not exist : " + filename);
        switch (format)
          {
        case sac:
          ReadSac(filename);
          break;
        case ascii:
          ReadAscii(filename);
          break;
        case unknownseis:
          cerr << "Unknown dataformat ! Cannot read " << filename << endl;
          return -100;
          break;
        default:
          cerr << "Unknown dataformat ! Cannot read " << filename << endl;
          return -100;
          break;
          }
        SetName(filename);
        return 0;
      }
      //! Write the data in sac binary format
      int WriteAsSac(const std::string &filename) const
      {
        int npts;
        boost::int32_t ihd[40];
        float fhd[70];
        char chd[8][24];
        ofstream outfile;
        float *temp = NULL;
        int i;

        outfile.open(filename.c_str());

        npts = GetData().size();

        temp = new float[npts]; //allocate memory for data
        std::string dummyline = "-12345  -12345  -12345 ";
        copy(GetData().begin(), GetData().end(), temp);
        for (i = 0; i < 40; i++)
          ihd[i] = -12345;
        for (i = 0; i < 70; i++)
          fhd[i] = -12345.00;
        for (i = 0; i < 8; i++)
          std::copy(dummyline.begin(), dummyline.end(), chd[i]);

        /*Set essential sac parameters*/
        ihd[35] = 1; /*Sets file to evenly spaced*/
        ihd[15] = 1; /*Sets file type to Timeseries*/
        ihd[6] = 6; /*Variable Name Internal */

        fhd[31] = stla;
        fhd[32] = stlo;
        fhd[33] = stel;
        fhd[34] = stdp;
        fhd[35] = evla;
        fhd[36] = evlo;
        fhd[37] = evel;
        fhd[38] = evdp;
        fhd[39] = mag;
        fhd[50] = dist;
        fhd[51] = az;
        fhd[52] = baz;
        fhd[53] = gcarc;

        ihd[9] = npts;
        fhd[0] = GetDt();
        fhd[5] = b;

        outfile.write((char *) (&fhd), 70 * 4); /*Write Sac Float Field*/
        outfile.write((char *) (&ihd), 40 * 4); /*Write Sac Int   Field*/
        outfile.write((char *) (&chd), 24 * 8); /*Write Sac Char. Field*/
        outfile.write((char *) (temp), npts * sizeof(float)); //write data part of SAC file
        outfile.close();
        delete[] temp;
        return (0);
      }
      //! Write the data in plain ascii format
      int WriteAsAscii(const std::string &filename) const
      {
        ofstream outfile(filename.c_str());

        for (unsigned int i = 0; i < GetData().size(); ++i)
          {
            outfile << b + i * GetDt() << " " << GetData().at(i) << endl;
          }
        return 0;
      }
      //! Write the data in the format it was read in and with the same filename
      int WriteBack() const
      {
        switch (dataformat)
          {
        case sac:
          WriteAsSac(GetName());
          break;
        case ascii:
          WriteAsAscii(GetName());
          break;
        case unknownseis:
          cerr << "Unknown dataformat ! Cannot write " << GetName() << endl;
          return -100;
          break;
        default:
          cerr << "Unknown dataformat ! Cannot write !" << GetName() << endl;
          return -100;
          break;
          }
        return 0;
      }
  }
      //! Copy the information in the header from another object
      void CopyHeader(const SeismicDataComp& source)
      {
        this->stla = source.stla;
        this->stlo = source.stlo;
        this->stel = source.stel;
        this->stdp = source.stdp;
        this->evla = source.evla;
        this->evlo = source.evlo;
        this->evel = source.evel;
        this->evdp = source.evdp;
        this->mag = source.mag;
        this->dist = source.dist;
        this->az = source.az;
        this->baz = source.baz;
        this->gcarc = source.gcarc;
        this->b = source.b;
      }
      SeismicDataComp(const std::string &filename, tseismicdataformat format =
          sac):
          stla(0), stlo(0), stel(0), stdp(0), evla(0), evlo(0), evel(0), evdp(0),
              mag(0), dist(0), az(0), baz(0), gcarc(0), b(0), dataformat(sac)
          {
            ReadData(filename, format);
          }
      SeismicDataComp():
          stla(0), stlo(0), stel(0), stdp(0), evla(0), evlo(0), evel(0), evdp(0),
              mag(0), dist(0), az(0), baz(0), gcarc(0), b(0), dataformat(sac)
          {
          }
      virtual ~SeismicDataComp();
      virtual SeismicDataComp& operator=(const SeismicDataComp& source)
      {
        if (this == &source)
          return *this;
        CopyHeader(source);
        this->dataformat = source.dataformat;
        TimeSeriesComponent::operator=(source);
        return *this;
      }
    private:
      double stla;
      double stlo;
      double stel;
      double stdp;
      double evla;
      double evlo;
      double evel;
      double evdp;
      double mag;
      double dist;
      double az;
      double baz;
      double gcarc;
      //std::string name;
      double b; // Time Shift between origin time of eq and beginning of data
      //ttsdata Data;
      tseismicdataformat dataformat;
      void ReadSac(const std::string &filename)
      {
        boost::int32_t ihd[40];
        float fhd[70];
        char chd[8][24];
        ifstream infile(filename.c_str());
        infile.read((char *) (&fhd), 70 * 4); /*Read Sac Float Field*/
        if (infile.fail()) //if reading fails
          {
            throw FatalException("Cannot read from file: " + filename);
          }
        else
          {

            infile.read((char *) (&ihd), 40 * 4); /*Read Sac Int   Field*/
            infile.read((char *) (&chd), 24 * 8); /*Read Sac Char. Field*/

            stla = fhd[31];
            stlo = fhd[32];
            stel = fhd[33];
            stdp = fhd[34];
            evla = fhd[35];
            evlo = fhd[36];
            evel = fhd[37];
            evdp = fhd[38];
            mag = fhd[39];
            dist = fhd[50];
            az = fhd[51];
            baz = fhd[52];
            gcarc = fhd[53];
            boost::int32_t npts = ihd[9];
            assert(fhd[0] > 0.0);
            SetDt(fhd[0]);
            b = fhd[5];
            assert(npts > 0);
            float *temp = new float[npts]; //allocate memory for data
            infile.read((char *) (temp), npts * sizeof(float)); //read data part of SAC file
            if (!GetData().empty())
              GetData().clear();
            copy(temp, temp + npts, back_inserter(GetData()));

            //Data.assign(npts,0);
            //for (int i = 0; i < npts; ++i)
            //	Data.at(i) = temp[i];
            delete[] temp;
            //ShiftStart(static_cast<int>(ceil(b/dt)));
          }
      }

      void ReadHeaderAscii(const std::string &filename);
      void ReadSKS(const std::string &filename);
      void ReadAscii(const std::string &filename)
      {
        ifstream infile(filename.c_str());
        double time, amp, oldtime;

        infile >> oldtime >> amp;
        if (infile.good())
          GetData().push_back(amp);
        else
          throw FatalException("Cannot read from file: " + filename);
        b = oldtime;
        infile >> time >> amp;
        assert(time - oldtime > 0.0);
        GetData().push_back(amp);
        SetDt(time - oldtime);
        if (!GetData().empty() && infile.good())
          GetData().clear();
        while (infile.good())
          {
            infile >> time >> amp;
            if (infile.good())
              GetData().push_back(amp);
          }
      }
      };
  /* @} */
  }
#endif // CSEISMICDATACOMP_H
