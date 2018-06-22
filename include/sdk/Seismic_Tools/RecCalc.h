#ifndef CRECFUNC_H
#define CRECFUNC_H
#include "SeismicDataComp.h"
#include "ResPkModel.h"
#include "TsSpectrum.h"
#include <string>
#include "types.h"
#include "convert.h"
#include "miscfunc.h"
#include "IterDecon.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/cast.hpp>
#include <boost/filesystem.hpp>
#include <numeric>
#include <functional>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
#include "statutils.h"
#include "WFunc.h"
#include "CRFSpecElement.h"
#include "SeisTools.h"
#include "Adaptors.h"
#include "Util.h"

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class is used to calculate receiver functions from seismic data
    class RecCalc
      {
    public:
      //! There are several ways to calculate receiver functions
      enum trfmethod
        {
        specdiv, iterdecon
        };
    private:
      //! The method we want to use to calculate the receiver function
      trfmethod method;
      //! For spectral division we need an object to calculate spectra
      TsSpectrum Spectrum;
      //! The waterlevel to fill in spectral holes
      double c;
      //! The width of the gaussian filter to smooth the receiver functions
      double sigma;
      //! Shift the data to move the initial correlation peak
      int shift;
      //! Should the receiver function be normalized to maximum amplitude
      bool normalize;
      //! The components used for the receiver function calculation
      SeismicDataComp RadComp;
      SeismicDataComp VerComp;
      //! Calculate the receiver function with the spectral division waterlevel method
      void SpectralDivision(const SeismicDataComp &RComp,
          const SeismicDataComp &VComp, SeismicDataComp &Receiver)
      {
        const double omegastep = 2. * PI / (RComp.GetDt() * RComp.GetData().size());
        // Make local copies for trimming and mean removal
        ttsdata LocalRad(RComp.GetData());
        ttsdata LocalVer(VComp.GetData());
        // Make both components the same length
        if (LocalRad.size() > LocalVer.size())
          LocalRad.erase(LocalRad.end() - (LocalRad.size() - LocalVer.size()),
              LocalRad.end());
        else if (LocalVer.size() > LocalRad.size())
          LocalVer.erase(LocalVer.end() - (LocalVer.size() - LocalRad.size()),
              LocalVer.end());
        //remove the mean
        SubMean(LocalVer.begin(), LocalVer.end());
        SubMean(LocalRad.begin(), LocalRad.end());
        //apply a window function for spectral calculation
        ApplyWindow(LocalVer.begin(), LocalVer.end(), LocalVer.begin(), Steep());
        ApplyWindow(LocalRad.begin(), LocalRad.end(), LocalRad.begin(), Steep());
        //assign space for spectra
        tcompdata RadSpec(LocalRad.size() / 2 + 1);
        tcompdata VerSpec(LocalVer.size() / 2 + 1);
        //calculate spetrca
        Spectrum.CalcSpectrum(LocalRad.begin(), LocalRad.end(), RadSpec.begin(),
            RadSpec.end());
        Spectrum.CalcSpectrum(LocalVer.begin(), LocalVer.end(), VerSpec.begin(),
            VerSpec.end());
        tcompdata RecSpec(RadSpec.size(), 0);

        Receiver.GetData().assign(LocalRad.size(), 0);
        // determine the waterlevel threshold from the maximum vertical spectrum and the waterlevel parameter c
        tcomp cmaxelem = *max_element(VerSpec.begin(), VerSpec.end(),
            gplib::absLess<tcomp, tcomp>());
        cmaxelem *= conj(cmaxelem) * c;

        // the denominator for the gaussian filter
        const double denom = 1. / (4.0 * sigma * sigma);
        //calculate the spectrum of the receiver function
        transform(RadSpec.begin(), RadSpec.end(), VerSpec.begin(), RecSpec.begin(),
            CalcSpectralElement(cmaxelem));
        //determine the phaseshift for the desired shift in points
        const dcomp phaseshift(0, shift);
        // apply the gaussian filter
        /*for (auto recit = RecSpec.begin(); recit < RecSpec.end(); ++recit)
         {
         double freq = omegastep * distance(RecSpec.begin(), recit);
         *recit *= exp(-(freq * freq) * denom - phaseshift * freq);
         }*/
        for (size_t i = 0; i < RecSpec.size(); ++i)
          {
            double freq = omegastep * i;
            RecSpec[i] *= exp(-(freq * freq) * denom - phaseshift * freq);
          }
        //transform receiver function spectrum back to time domain
        Spectrum.CalcTimeSeries(RecSpec.begin(), RecSpec.end(),
            Receiver.GetData().begin(), Receiver.GetData().end());
      }

      //! Calculate the receiver function by iterative convolution
      void IterativeDeconvolution(const SeismicDataComp &RComp,
          const SeismicDataComp &VComp, SeismicDataComp &Receiver)
      {
        gplib::rvec Filter(RComp.GetData().size());
        const double dt = RComp.GetDt();
        double normfactor = 1.; // /(sigma * sqrt(2.* acos(-1.)));
        const int shiftpoints = boost::numeric_cast<int>(shift / dt);
        const double variancesq = sigma * dt * sigma * dt;
        const unsigned int maxit = 100;
        const double minimprove = 1e-6; // we want to stop when the improvement is less than 0.1%
        const int maxpoints = Filter.size() / 2; //we store it in a signed variable to avoid compiler warning for the loop below
        //the loop index HAS TO BE SIGNED !
        for (int i = 0; i <= maxpoints; ++i)
          {
            Filter(i) = normfactor * exp(-std::pow((i - shiftpoints), 2.) * variancesq);
            Filter(Filter.size() - i - 1) = normfactor
                * exp(-std::pow((-i - 1 - shiftpoints), 2.) * variancesq);
          }

        gplib::rvec RadFilter(RComp.GetData().size()), VerFilter(VComp.GetData().size());
        copy(RComp.GetData().begin(), RComp.GetData().end(), RadFilter.begin());
        copy(VComp.GetData().begin(), VComp.GetData().end(), VerFilter.begin());
        SubMean(RadFilter.begin(), RadFilter.end());
        SubMean(VerFilter.begin(), VerFilter.end());
        Convolve(RadFilter, Filter, RadFilter, Spectrum);
        Convolve(VerFilter, Filter, VerFilter, Spectrum);
        gplib::rvec Current(RadFilter), Output(RadFilter);

        IterDecon Decon(VerFilter.size(), Spectrum);
        const double power = ublas::prec_inner_prod(RadFilter, RadFilter);
        double error = power;
        double lasterror = 1.;
        double improvement = 1.;
        unsigned int iter = 0;
        while (improvement > minimprove && iter < maxit)
          {
            Decon.AdaptFilter(VerFilter, Current);
            Decon.CalcOutput(VerFilter, Output);

            Current = RadFilter - Output;
            error = ublas::prec_inner_prod(Current, Current) / power;
            improvement = lasterror - error;
            lasterror = error;
            ++iter;

          }
        std::cout << "Iterations: " << iter << " Error:  " << error << std::endl;
        Convolve(Decon.GetWeights(), Filter, Current, Spectrum); //we re-use current to store the filtered weights, to save another object
        Receiver.GetData().assign(Current.size(), 0);
        copy(Current.begin(), Current.end(), Receiver.GetData().begin());
      }

    public:
      //! Get the radial component, mostly needed for synthetic data
      const SeismicDataComp &GetRadComp()
        {
          return RadComp;
        }
      const SeismicDataComp &GetVerComp()
        {
          return VerComp;
        }
      //! Change whether the output receiver function is normalized to a maximum amplitude of 1
      void SetNormalize(const bool what)
        {
          normalize = what;
        }
      //! The three Synth*Parallel methods provide alternative acces to the steps in CalcRecSynth for safe parallel execution
      void SynthPreParallel(const std::string &filename, ResPkModel &Model,
          SeismicDataComp &Receiver, const bool cleanfiles = false)
      {
        Model.WriteRunFile(filename);
        Model.WriteModel(filename + ".mod");
      }

      //! All operations that are safe to execute in parallel
      void SynthSafeParallel(const std::string &filename, ResPkModel &Model,
          SeismicDataComp &Receiver, const bool cleanfiles = false)
      {
        int result = std::system(("bash ./" + filename).c_str());
        if (result != 0)
          throw gplib::FatalException(
              "Problem in synthetic receiver function calculation !");
      }
      //! Operations of the synthetic receiver function calculation that are not safe in parallel and hafe to be executed after the parallel part
      void SynthPostParallel(const std::string &filename, ResPkModel &Model,
          SeismicDataComp &Receiver, const bool cleanfiles = false)
      {
        RadComp.ReadData(filename + ".mod_sp.r");
        VerComp.ReadData(filename + ".mod_sp.z");
        Receiver = RadComp;
        CalcRecData(RadComp, VerComp, Receiver);
        if (cleanfiles)
          {
            CleanFiles(filename);
          }
      }
      //! Calculate Receiver functions from two data components
      void CalcRecData(const SeismicDataComp &RadComp,
          const SeismicDataComp &VerComp, SeismicDataComp &Receiver)
      {
        Receiver.CopyHeader(RadComp);
        switch (method)
          {
        case iterdecon:
          IterativeDeconvolution(RadComp, VerComp, Receiver);
          break;
        case specdiv:
          SpectralDivision(RadComp, VerComp, Receiver);
          break;
          }
        // set parameters for the timeseries object
        Receiver.SetB(-shift);
        Receiver.SetDt(RadComp.GetDt());
        if (normalize)
          {
            Normalize(Receiver.GetData());
          }
      }
      //! Calculate synthetic receiver funtions from a model
      void CalcRecSynth(const std::string &filename, ResPkModel &Model,
          SeismicDataComp &Receiver, const bool cleanfiles = false)
      {
        SynthPreParallel(filename, Model, Receiver, cleanfiles);
        SynthSafeParallel(filename, Model, Receiver, cleanfiles);
        SynthPostParallel(filename, Model, Receiver, cleanfiles);
      }

      RecCalc& operator=(const RecCalc& source)
      {
        if (this == &source)
          return *this;
        method = source.method;
        Spectrum = source.Spectrum;
        c = source.c;
        sigma = source.sigma;
        shift = source.shift;
        normalize = source.normalize;
        RadComp = source.RadComp;
        VerComp = source.VerComp;
        return *this;
      }
      //! The constructor takes the essential parameters that shouldn't change during different calculations
      RecCalc(int myshift, double mysigma, double myc,
          bool multicalc = false, trfmethod themethod = iterdecon):
          method(themethod), Spectrum(multicalc), c(myc), sigma(mysigma), shift(myshift), normalize(
              false)
        {

        }
      RecCalc(const RecCalc &Old):
          method(Old.method), Spectrum(Old.Spectrum), c(Old.c), sigma(Old.sigma), shift(
              Old.shift), normalize(Old.normalize), RadComp(Old.RadComp), VerComp(
              Old.VerComp)
        {

        }
      virtual ~RecCalc();
      };
  /* @} */
  }
#endif // CRECFUNC_H
