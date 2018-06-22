#ifndef MISCFUNC_H_INCLUDED
#define MISCFUNC_H_INCLUDED
#include "types.h"
#include <vector>
#include "FatalException.h"
#include "TsSpectrum.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <functional>
#include "NumUtil.h"
#include <numeric>
#include <algorithm>
#include <fftw3.h>
#include <fstream>
#include <iomanip>
#include <complex>
#include <cmath>
using namespace std;
namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */
    namespace ublas = boost::numeric::ublas;

    //! Calculate the hilbert transform of the input vector
    void Hilbert(std::vector<double>::iterator Inputbegin,
        std::vector<double>::iterator Inputend, std::vector<double> &Output)
    {
      fftw_complex *timedomain;
      fftw_complex *freqdomain;
      fftw_plan p;
      double swapstore;
      const unsigned int size = distance(Inputbegin, Inputend);
      if (Output.size() != size)
        Output.assign(size, 0);

      timedomain = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * size);
      freqdomain = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * size);
      p = fftw_plan_dft_1d(size, timedomain, freqdomain, -1, FFTW_ESTIMATE);
      for (unsigned int i = 0; i < size; ++i)
        {
          timedomain[i][0] = *(Inputbegin + i) * (0.5 - 0.5 * cos(2 * PI * i
              / size));
          timedomain[i][1] = 0;
        }
      fftw_execute(p);
      for (unsigned int i = 0; i < size; ++i)
        {
          swapstore = freqdomain[i][0];
          if (i < size / 2)
            {
              freqdomain[i][0] = -freqdomain[i][1];
              freqdomain[i][1] = swapstore;
            }
          else
            {
              freqdomain[i][0] = freqdomain[i][1];
              freqdomain[i][1] = -swapstore;
            }
        }
      p = fftw_plan_dft_1d(size, freqdomain, timedomain, 1, FFTW_ESTIMATE);
      fftw_execute(p);
      for (unsigned int i = 0; i < size; ++i)
        Output.at(i) = 1. / double(size) * timedomain[i][0];
      fftw_destroy_plan(p);
      fftw_free(timedomain);
      fftw_free(freqdomain);
    }

    //! Calculate the normalized envelope of the input vector
    void NormEnvelope(std::vector<double>::iterator Inputbegin, std::vector<
        double>::iterator Inputend, std::vector<double> &Output)
    {
      const int size = distance(Inputbegin, Inputend);
      vector<double> Transformed(size);
      double maximum;
      Output.assign(size, 0);
      Hilbert(Inputbegin, Inputend, Transformed);
      for (int i = 0; i < size; ++i)
        Output.at(i) = sqrt(std::pow(*(Inputbegin + i), 2) + std::pow(
            Transformed.at(i), 2));
      maximum = *max_element(Output.begin(), Output.end());
      for (int i = 0; i < size; ++i)
        Output.at(i) /= maximum;
    }

    //! Calculate the normalized cross-correlation between Master and Corr between the indices startpoint and endpoint
    double Cross(ttsdata Master, ttsdata Corr, const int startpoint,
        const int endpoint)
    {
      const int size = endpoint - startpoint;
      double cross = 0;
      double auto1 = 0;
      double auto2 = 0;
      const double mean1 = accumulate(Master.begin() + startpoint,
          Master.begin() + endpoint, 0.) / size;
      const double mean2 = accumulate(Corr.begin() + startpoint, Corr.begin()
          + endpoint, 0.) / size;
      const double SQRT_DBL_EPSILON  = 1.4901161193847656e-08;
      for (int i = startpoint; i < endpoint; ++i)
        {
          cross += (Master.at(i) - mean1) * (Corr.at(i) - mean2);
          auto1 += pow2(Master.at(i) - mean1);
          auto2 += pow2(Corr.at(i) - mean2);
        }
      if (fcmp(0.0, auto1, SQRT_DBL_EPSILON ) || fcmp(0.0, auto2,
          SQRT_DBL_EPSILON))
        return (cross / (sqrt(auto1) * sqrt(auto2)));
      else
        return 0.0;
    }

    //! Calculates Commutator of two complex numbers
    inline double Commute(dcomp A, dcomp B)
      {
        return (A.real() * B.imag() - B.real() * A.imag());

      }
    //! Compare par1 and par2 within specified tolerance
    inline int FuzzComp(double par1, double par2, double tolerance)
      {
        double lower;
        double higher;

        lower = par1 - tolerance;
        higher = par1 + tolerance;
        if ((lower <= par2) && (higher >= par2))
          return (1);
        else
          return (0);
        //return (((par1-tolerance) <= par2) && ((par1+tolerance) >= par2));
      }

    //! perform spectral multiplication on two vector style container and write the result to output
    /*! Do_Spec_Mul takes two input vectors, Master and Corr of the same length, writes either the convolution or correlation
     * into the vector output, depending on docorrel
     */
    template<typename ts_type>
    void Do_Spec_Mul(const ts_type &Master, const ts_type &Corr,
        ts_type &Output, const bool docorrel, TsSpectrum &SpecCalc)
      {
        if (Corr.size() != Master.size()) //if input sizes are different
          throw FatalException("In Correl: Master.size != Corr.size !"); //throw exception
        if (Output.size() != Master.size()) //if ouput vector doesn't have the right length
          Output.resize(Master.size()); //adjust

        tcompdata MasterSpec(Master.size() / 2 + 1), CorrSpec(Corr.size() / 2
            + 1); //some temporary objects
        SpecCalc.CalcSpectrum(Master.begin(), Master.end(), MasterSpec.begin(),
            MasterSpec.end()); // calc spectrum for master
        SpecCalc.CalcSpectrum(Corr.begin(), Corr.end(), CorrSpec.begin(),
            CorrSpec.end()); // and for corr
        tcompdata CrossPower;
        if (docorrel) //if we want to do a correlation
          {
            std::transform(MasterSpec.begin(), MasterSpec.end(),
                CorrSpec.begin(), back_inserter(CrossPower), //we have to multiply
                boost::bind<std::complex<double> >( //Master elements with the conjugate of Corr elements and write
                    std::multiplies<std::complex<double> >(), //into CrossPower
                    _1, boost::bind<std::complex<double> >(&std::conj<double>,
                        _2)));
          }
        else //if convolution
          {
            std::transform(MasterSpec.begin(), MasterSpec.end(),
                CorrSpec.begin(), back_inserter(CrossPower), std::multiplies<
                    std::complex<double> >()); //just multiply elements in Master with elements in Corr
          }
        SpecCalc.CalcTimeSeries(CrossPower.begin(), CrossPower.end(),
            Output.begin(), Output.end()); //Calculate the timeseries from CrossPower
      }

    template<typename ts_type>
    void Do_Spec_Mul(const ts_type &Master, const ts_type &Corr,
        ts_type &Output, const bool docorrel)
      {
        TsSpectrum SpecCalc(false);
        Do_Spec_Mul(Master, Corr, Output, docorrel, SpecCalc);
      }

    //! A convenience wrapper to calculate correlations
    template<typename ts_type>
    void Correl(const ts_type &Master, const ts_type &Corr, ts_type &Output)
      {
        Do_Spec_Mul(Master, Corr, Output, true);
      }

    template<typename ts_type>
    void Correl(const ts_type &Master, const ts_type &Corr, ts_type &Output,
        TsSpectrum &SpecCalc)
      {
        Do_Spec_Mul(Master, Corr, Output, true, SpecCalc);
      }

    //! A convenience wrapper to calculate convolution
    template<typename ts_type>
    void Convolve(const ts_type &Master, const ts_type &Corr, ts_type &Output)
      {
        Do_Spec_Mul(Master, Corr, Output, false);
      }

    //! A convenience wrapper to calculate convolution
    template<typename ts_type>
    void Convolve(const ts_type &Master, const ts_type &Corr, ts_type &Output,
        TsSpectrum &SpecCalc)
      {
        Do_Spec_Mul(Master, Corr, Output, false, SpecCalc);
      }
  /* @} */
  }
#endif

