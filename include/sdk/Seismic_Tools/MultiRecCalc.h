#ifndef MULTIRECCALC_H_
#define MULTIRECCALC_H_
#include "SeismicDataComp.h"
#include "SeismicStationList.h"
#include "TimeFrequency.h"
#include "FatalException.h"
#include "CRFSpecElement.h"
#include "TsSpectrum.h"
#include "WFunc.h"
#include "VecMat.h"
#include "Adaptors.h"

namespace ublas = boost::numeric::ublas;
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class implements the multi-site receiver function calculation in the frequency domain as suggested by Gurrolla 1995
    class MultiRecCalc
      {
    private:
      //! The waterlevel to fill in spectral holes
      double c;
      //! The width of the gaussian filter to smooth the receiver functions
      double sigma;
      //! Shift the data to move the initial correlation peak
      int shift;
      //! Calculate the receiver function by spectral division
    public:
      //! Calculate Receiver functions from a vector of data components, both vectors have to have the same number of elements
      //! and the seismograms have to have the same length
      void CalcRecData(const SeismicStationList::tseiscompvector &RadComp,
          const SeismicStationList::tseiscompvector &VerComp,
          SeismicDataComp &Receiver)
      {
        if (RadComp.size() != VerComp.size())
          throw FatalException(
              "Not the same number of stations for vertical and radial components !");
        const unsigned int compsize = RadComp.front()->GetData().size();
        const unsigned int ncomp = RadComp.size();
        const double omegastep = 2. * PI / (RadComp.front()->GetDt()
            * RadComp.front()->GetData().size());
        gplib::rvec ConcatRad(compsize * ncomp), ConcatVer(compsize * ncomp);
        for (unsigned int i = 0; i < ncomp; ++i)
          {
            if (RadComp.at(i)->GetData().size() != compsize
                || VerComp.at(i)->GetData().size() != compsize)
              throw FatalException(
                  "Incompatible sizes for Vertical or Radial component.");
            copy(RadComp.at(i)->GetData().begin(),
                RadComp.at(i)->GetData().end(), ConcatRad.begin() + i
                    * compsize);
            copy(VerComp.at(i)->GetData().begin(),
                VerComp.at(i)->GetData().end(), ConcatVer.begin() + i
                    * compsize);
          }
        gplib::cmat radtfspectrum = TimeFrequency(ConcatRad.begin(),
            ConcatRad.end(), compsize, Steep());
        gplib::cmat vertfspectrum = TimeFrequency(ConcatVer.begin(),
            ConcatVer.end(), compsize, Steep());
        gplib::cvec RecSpec(compsize / 2 + 1);
        RecSpec *= 0.0;
        for (unsigned int i = 0; i < radtfspectrum.size1(); ++i)
          {
            complex<double> delta = *max_element(
                column(vertfspectrum, i).begin(),
                column(vertfspectrum, i).end(), gplib::absLess<tcomp, tcomp>())
                * c;
            delta *= conj(delta);
            //delta /= radtfspectrum.size1();
            for (unsigned int j = 0; j < radtfspectrum.size2(); ++j)
              {
                RecSpec(j) += CalcSpectralElement(delta)(radtfspectrum(i, j),
                    vertfspectrum(i, j));
              }
          }
        const double denom = 1. / (4.0 * sigma * sigma);
        for (unsigned int i = 0; i < RecSpec.size(); ++i)
          {
            double freq = omegastep * i;
            RecSpec(i) *= exp(-(freq * freq) * denom);
          }
        Receiver.SetB(-shift);
        Receiver.SetDt(RadComp.front()->GetDt());
        Receiver.GetData().assign(compsize, 0.0);
        TsSpectrum Spectrum(false);
        Spectrum.CalcTimeSeries(RecSpec.begin(), RecSpec.end(),
            Receiver.GetData().begin(), Receiver.GetData().end());
        const int shiftpoints = boost::numeric_cast<size_t>(shift
            / RadComp.front()->GetDt());
        rotate(Receiver.GetData().begin(), Receiver.GetData().end()
            - shiftpoints, Receiver.GetData().end());
/*        const double maxamp = 1. / *max_element(Receiver.GetData().begin(),
            Receiver.GetData().end());
        transform(Receiver.GetData().begin(), Receiver.GetData().end(),
            Receiver.GetData().begin(), boost::bind(multiplies<double> (), _1,
                maxamp));*/
      }
      MultiRecCalc(const int myshift, const double mysigma, const double myc):
          c(myc), sigma(mysigma), shift(myshift)
          {
          }

      virtual ~MultiRecCalc();
      };
  /* @} */
  }
#endif /*MULTIRECCALC_H_*/
