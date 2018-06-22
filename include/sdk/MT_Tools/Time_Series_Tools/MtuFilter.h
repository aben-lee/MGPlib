#ifndef CMTUFILTER_H
#define CMTUFILTER_H

#include "types.h"
#include <string>
#include <fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include "FatalException.h"
#include <cassert>
using namespace std;

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! Store the filter coefficients for one component of Phoenix mtu data
    class MtuFilter
      {
      int seglength;
      double freqstep;
      tcompdata FilterCoeff;
    public:
      const tcompdata &GetFilterCoeff()
        {
          return FilterCoeff;
        }
      virtual void GetData(const std::string filename)
      {
        ifstream filterfile;
        ttsdata rawfreqs;
        ttsdata rawimag, rawreal;
        double currfreq, currreal, currimag, dummy;
        //double absresponse,phaseresponse;
        double *imag, *real, *freqs;

        FilterCoeff.clear();
        filterfile.open(filename.c_str());
        if (!filterfile)
          {
            throw FatalException("Filter-file  does not exist: " + filename);
          }
        filterfile >> dummy;
        while (filterfile.good())
          {
            filterfile >> currfreq;
            filterfile.ignore(256, ',');
            filterfile >> currreal;
            filterfile.ignore(256, ',');
            filterfile >> currimag;
            if (filterfile.good())
              {
                rawfreqs.push_back(currfreq);
                rawreal.push_back(currreal);
                rawimag.push_back(currimag);
              }
          }
        assert(rawreal.size() == rawimag.size());
        assert(rawreal.size() == rawfreqs.size());
        filterfile.close();

        real = new double[rawreal.size()];
        imag = new double[rawimag.size()];
        freqs = new double[rawfreqs.size()];

        for (unsigned int i = 0; i < rawreal.size(); ++i)
          {
            real[rawreal.size() - 1 - i] = rawreal.at(i);
            imag[rawreal.size() - 1 - i] = rawimag.at(i);
            freqs[rawreal.size() - 1 - i] = rawfreqs.at(i);
          }

        gsl_interp_accel *accreal = gsl_interp_accel_alloc();
        gsl_interp_accel *accimag = gsl_interp_accel_alloc();

        gsl_spline *realspline = gsl_spline_alloc(gsl_interp_cspline,
            rawreal.size());
        gsl_spline *imagspline = gsl_spline_alloc(gsl_interp_cspline,
            rawimag.size());

        gsl_spline_init(realspline, freqs, real, rawreal.size());
        gsl_spline_init(imagspline, freqs, imag, rawimag.size());

        for (int i = 0; i < seglength / 2 + 1; ++i)
          {
            currreal = gsl_spline_eval(realspline, i * freqstep, accreal);
            currimag = gsl_spline_eval(imagspline, i * freqstep, accimag);
            FilterCoeff.push_back(currreal + I * currimag);
          }
        delete[] freqs;
        delete[] real;
        delete[] imag;
        gsl_spline_free(realspline);
        gsl_spline_free(imagspline);
        gsl_interp_accel_free(accreal);
        gsl_interp_accel_free(accimag);
      }
      virtual void WriteData(const std::string filename)
      {
        ofstream rawout;
        rawout.open((filename + ".raw").c_str());
        for (unsigned int i = 0; i < FilterCoeff.size(); ++i)
          {
            rawout << i * freqstep << " " << abs(FilterCoeff.at(i)) << " "
                << arg(FilterCoeff.at(i)) << endl;
          }
        rawout.close();
      }
      MtuFilter(const int length, const double step) :
        seglength(length), freqstep(step)
        {
        }
      ;
      virtual ~MtuFilter();
      };
  /* @} */
  }
#endif // CMTUFILTER_H
