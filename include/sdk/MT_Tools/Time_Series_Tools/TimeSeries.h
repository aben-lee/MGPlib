
#ifndef CTIMSERIES_H
#define CTIMSERIES_H
#include "FatalException.h"
#include "TimeSeriesComponent.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <vector>
#include <algorithm>
#include <numeric>
#include "FatalException.h"
#include <boost/cast.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! This class is the base class for all classes dealing with MT time series
    class TimeSeries
      {
    public:
      //! We use the boost library time functionality for time types and store the time for each point in a vector
      typedef boost::posix_time::ptime ttime;
      typedef std::vector<ttime> ttimedata;
    protected:
      //! The data for the north-south magnetic field
      TimeSeriesComponent Hx;
      //! The data for the east-west magnetic field
      TimeSeriesComponent Hy;
      //! The data for the vertical magnetic field
      TimeSeriesComponent Hz;
      //! The data for the north-south electric field
      TimeSeriesComponent Ex;
      //! The data for the east-west electric field
      TimeSeriesComponent Ey;
      //! The time associated with each data point
      ttimedata t;
    public:
      //! Access function for Hx, returns reference for efficiency
      TimeSeriesComponent &GetHx()
        {
          return Hx;
        }
      TimeSeriesComponent &GetHy()
        {
          return Hy;
        }
      TimeSeriesComponent &GetHz()
        {
          return Hz;
        }
      TimeSeriesComponent &GetEx()
        {
          return Ex;
        }
      TimeSeriesComponent &GetEy()
        {
          return Ey;
        }
      ttimedata &GetTime()
        {
          return t;
        }
      //! Return the size of the time series, throws if one of the components has a different size
      size_t Size()
      {
        size_t exlength = Ex.GetData().size();
        if (exlength != Ey.GetData().size() || exlength != Hx.GetData().size()
            || exlength != Hy.GetData().size() || exlength
            != Hz.GetData().size())
          throw FatalException(
              "Component sizes differ, unable to determine size !");
        else
          return exlength;
      }
      /*! Declaration for GetData() that reads data from
       * a file. This is intended for use with external data, such as
       * recorded data, or synthetic data from external programs.
       */
      virtual void GetData(const std::string filename) = 0;
      /*! The abstract declaration for a method that writes the data to
       * a file. Therefore no version without a filename is present
       */
      virtual void WriteData(const std::string filename) = 0;
      //! The samplerate is stored in each component, we just return the samplerate of Hx assuming they are all equal
      double GetSamplerate()
        {
          const double samplerate = Hx.GetSamplerate();
          if (samplerate != Hy.GetSamplerate() || samplerate
              != Hz.GetSamplerate() || samplerate != Ex.GetSamplerate()
              || samplerate != Ey.GetSamplerate())
            throw FatalException("Samplerate is not equal for all components");
          return samplerate;
        }
      TimeSeries()
      {
        Ex.SetName("ex");
        Ey.SetName("ey");
        Hx.SetName("hx");
        Hy.SetName("hy");
        Hz.SetName("hz");
      }
      virtual ~TimeSeries()
      {

      }
      TimeSeries& operator=(const TimeSeries &source)
      {
        if (this != &source)
          {
            this->Ex = source.Ex;
            this->Ey = source.Ey;
            this->Hx = source.Hx;
            this->Hy = source.Hy;
            this->Hz = source.Hz;
            copy(source.t.begin(), source.t.end(), back_inserter(t));
          }
        return *this;
      }
      //! Multiply all components by a constant factor
      TimeSeries& operator*=(const double &factor)
      {
        this->Ex *= factor;
        this->Ey *= factor;
        this->Hx *= factor;
        this->Hy *= factor;
        this->Hz *= factor;
        return *this;
      }

      //! Add a constant shift to all components
      TimeSeries& operator+=(const double &shift)
      {
        this->Ex += shift;
        this->Ey += shift;
        this->Hx += shift;
        this->Hy += shift;
        this->Hz += shift;
        return *this;
      }
      //! Erase data between startindex and endindex
      void erase(const int startindex, const int endindex)
      {
        Ex.GetData().erase(Ex.GetData().begin() + startindex,
            Ex.GetData().begin() + endindex);
        Ey.GetData().erase(Ey.GetData().begin() + startindex,
            Ey.GetData().begin() + endindex);
        Hx.GetData().erase(Hx.GetData().begin() + startindex,
            Hx.GetData().begin() + endindex);
        Hy.GetData().erase(Hy.GetData().begin() + startindex,
            Hy.GetData().begin() + endindex);
        Hz.GetData().erase(Hz.GetData().begin() + startindex,
            Hz.GetData().begin() + endindex);
        t.erase(t.begin() + startindex, t.begin() + endindex);
      }
      //friend void Synchronize(TimeSeries &Data1, TimeSeries &Data2);
   };

    /*! Synchronize two Objects containing MT data so that they have the same start time
     */
    void Synchronize(TimeSeries &Data1, TimeSeries &Data2)
    {
      if (Data1.GetTime().empty() || Data2.GetTime().empty())
        throw FatalException("No time information available !");
      boost::posix_time::time_duration startdiff(Data1.GetTime().at(0)
          - Data2.GetTime().at(0));
      int offset = boost::numeric_cast<int>(startdiff.total_microseconds()
          * Data1.GetSamplerate() / 1000000); //calculate the offset in samples
      if (boost::numeric_cast<unsigned int>(abs(offset)) > min(
          Data1.GetTime().size(), Data2.GetTime().size()))
        throw FatalException("Offset too large. Cannot synchronize !");
      if (offset > 0) //Data1 starts later
        Data2.erase(0, offset);
      if (offset < 0)
        Data1.erase(0, -offset);
    }
  /* @} */

  }
#endif
