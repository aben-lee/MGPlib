#ifndef TIMESERIESCOMPONENT_H_
#define TIMESERIESCOMPONENT_H_
#include <vector>
#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/operators.hpp>
#include "VecMat.h"
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include "FatalException.h"

namespace gplib
  {

    /** \addtogroup tstools Time series analysis methods */
    /* @{ */

    //! TimeSeriesComponent is the base storage class for all types of time series data
    /*! This is the base class for both MT and Seismic data, all common functionality will
     * be in this class. Furthermore all functions should be implemented to use this class
     * unless they need functionality specific to the method.
     * We inherit from ring_operators to provide a set of useful mathematical operators with minimum implementation
     */
    class TimeSeriesComponent: public boost::arithmetic<boost::ring_operators<
        TimeSeriesComponent>, double>
      {
    private:
      //! The structure holding the data
      std::vector<double> data;
      //! Samplerate in Hz
      double samplerate;
      //! The name of the data (component or site or both)
      std::string name;
      //! The start of the recording
      boost::posix_time::ptime starttime;
    public:
      typedef std::vector<double>::iterator tdatait;
      //! Access for data vector, for ease of use and efficiency we return a reference
      std::vector<double> &GetData()
        {
          return data;
        }
      const std::vector<double> &GetData() const
        {
          return data;
        }
      //! For some methods we prefer to get the data as a ublas vector, we return a copy
      /*! This function is quite expensive, as the ublas object is generated on the fly and we return a copy.
       */
      gplib::rvec GetUblasData();
      //! Return samplerate in Hz
      double GetSamplerate() const
        {
          return samplerate;
        }
      //! Set sampling rate in Hz
      void SetSamplerate(const double rate)
        {
          samplerate = rate;
        }
      //! Set delta t in s
      void SetDt(const double dt)
        {
          samplerate = 1. / dt;
        }
      //! Return dt in s
      double GetDt() const
        {
          return 1. / samplerate;
        }
      //! Return name of the component
      std::string GetName() const
        {
          return name;
        }
      //! Modify name of the component
      void SetName(const std::string &n)
        {
          name = n;
        }
#ifdef HAVEGSL
      //! resample to a new dt by interpolation, this method only exists when HAVEGSL is defined durign compilation
      void Resample(const double newdt);
#endif
      //! Shift the start of the recording by npts points
      /*! if npts < 0 we cut abs(npts) from the beginning, otherwise we add npts 0s at the beginning
       * this will also adjust the starttime accordingly
       */
      void ShiftStart(const int npts)
      {
        //calculate the time_shift with microsecond precision
        boost::posix_time::time_duration time_shift =
            boost::posix_time::microseconds(boost::numeric_cast<unsigned int>(
                npts * 1000000 / samplerate));
        if (npts < 0) // if we want to remove something
          {
            if (static_cast<size_t> (abs(npts)) > data.size())
              throw FatalException("Trying to shift by too many points. ");
            // erase the data points
            data.erase(data.begin(), data.begin() + abs(npts));
            // correct the starttime with microsecond precision
            starttime = starttime + time_shift;
          }
        else //we want to add something
          {
            data.insert(data.begin(), npts, 0);
            starttime = starttime - time_shift;
          }
      }
      //! Shift the end of the recording by npts points
      /*! if npts < 0 we cut abs(npts) from the end, otherwise we add npts 0s at the end
       */
      void ShiftEnd(const int npts)
      {
        if (npts < 0)
          {
            if (static_cast<size_t> (abs(npts)) > data.size())
              throw FatalException("Trying to cut too many points. ");
            data.erase(data.end() + npts, data.end());
          }
        else
          {
            data.insert(data.end(), npts, 0);
          }
      }
      // we declare the operators necessary for boost::ring_operators to generate the rest
      TimeSeriesComponent& operator=(const TimeSeriesComponent& source)
      {
        if (this != &source)
          {
            this->samplerate = source.samplerate;
            this->name = source.name;
            this->starttime = source.starttime;
            this->data.assign(source.data.size(), 0); //assign and copy clears old data
            std::copy(source.data.begin(), source.data.end(),
                this->data.begin());
          }
        return *this;
      }

#ifdef HAVEGSL
    void TimeSeriesComponent::Resample(const double newdt)
      {
        const size_t oldlength = data.size();
        double *oldtime = new double[oldlength];
        const double dt = GetDt();
        double start = 0.0;
        //we need time information for interpolation, the real starttime is irrelevant for this
        for (size_t i = 0; i < oldlength; ++i)
          {
            oldtime[i] = start + i * dt;
          }
        //initialize the gsl interpolation routines
        gsl_interp_accel *acc = gsl_interp_accel_alloc();
        gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, oldlength);
        gsl_spline_init(spline, oldtime, &data[0], oldlength);
        // calculate the lenght of the resampled timeseries
        const size_t newlength = boost::numeric_cast<size_t>(oldlength * (dt
            / newdt));
        // clear old data
        data.clear();
        //create new timeseries
        for (size_t i = 0; i < newlength; ++i)
          {
            data.push_back(gsl_spline_eval(spline, start + i * newdt, acc));
          }
        gsl_spline_free(spline);
        gsl_interp_accel_free(acc);
        samplerate = 1. / newdt;

      }
#endif //HAVEGSL

      //! Multiply each element of the time series by a constant factor
      TimeSeriesComponent& operator*=(const double factor)
      {
        std::transform(data.begin(), data.end(), data.begin(), boost::bind(
            std::multiplies<double>(), factor, _1));
        return *this;
      }
      //! Devide each element of the time series by a constant number
      TimeSeriesComponent& operator/=(const double numerator)
      {
        const double factor = 1. / numerator;
        operator*=(factor);
        return *this;
      }
      //! Add a constant shift to each element of the time series
      TimeSeriesComponent& operator+=(const double shift)
      {
        std::transform(data.begin(), data.end(), data.begin(), boost::bind(
            std::plus<double>(), shift, _1));
        return *this;
      }

      //! Substract a constant shift from each element of the time series
      TimeSeriesComponent& operator-=(const double shift)
      {
        operator+=(-shift);
        return *this;
      }
      //! Add two time series point by point and store the result in the current object
      TimeSeriesComponent& operator+=(const TimeSeriesComponent &other)
      {
        std::transform(data.begin(), data.end(), other.data.begin(),
            data.begin(), std::plus<double>());
        return *this;
      }
      //! Substract two time series point by point and store the result in the current object
      TimeSeriesComponent& operator-=(const TimeSeriesComponent &other)
      {
        std::transform(data.begin(), data.end(), other.data.begin(),
            data.begin(), std::minus<double>());
        return *this;
      }
      TimeSeriesComponent(const TimeSeriesComponent& source):
          data(source.data), samplerate(source.samplerate), name(source.name),
              starttime(source.starttime)
          {
          }
      TimeSeriesComponent()
      {
        samplerate = 0.0;
      }
      virtual ~TimeSeriesComponent()
      {

      }
    };

    //! We want to make this inline, so it appears in the header
    inline gplib::rvec TimeSeriesComponent::GetUblasData()
      {
        gplib::rvec ubvec(data.size());
        std::copy(data.begin(), data.end(), ubvec.begin());
        return ubvec;
      }
  /* @} */
  }
#endif /*TIMESERIESCOMPONENT_H_*/
