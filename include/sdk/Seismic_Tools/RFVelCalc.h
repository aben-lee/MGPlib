#ifndef RFVELCALC_H_
#define RFVELCALC_H_
#include "RecCalc.h"
#include "SeismicDataComp.h"
#include <string>
#include "WFunc.h"
#include <numeric>
#include <fstream>
#include <cassert>
#include "FatalException.h"
#include "NumUtil.h"

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class implements the method to calculate absolute S-Wave velocities from Receiver function data as described by Sevnningsen and Jacobsen, GJI 2007
    class RFVelCalc
      {
    private:
      RecCalc RFCalculator;
      ttsdata Velocities;
      ttsdata Periods;
      //! The core estimation routine, take radial and vertical receiver functions
      void AbsVelCalc(const double slowness, const SeismicDataComp &RadRec,
          const SeismicDataComp &VerRec, ttsdata &AppVel)
      {
        //we need filtered versions of the two components
        //so create copies that we can work on
        ttsdata FilteredR(RadRec.GetData().size()), FilteredZ(
            VerRec.GetData().size());
        //make sure all old stuff is deleted before we do another calculation
        AppVel.clear();
        Velocities.clear();
        Periods.clear();
        //in debug mode we perform some extra checks
        assert(FilteredR.size() == FilteredZ.size());
        assert(fcmp(RadRec.GetDt(),VerRec.GetDt(),std::numeric_limits<double>::epsilon())==0);
        //we have to compensate for the shift of 5 seconds that we use above
        const double relshift = 5.0
            / (RadRec.GetDt() * RadRec.GetData().size());
        //at the moment we calculate apparent velocities at periods independent of the receiver function parameters
        //we specify the width in seconds
        for (double width = 0.1; width < 80; width *= 1.1)
          {
            //calculate the width of the filter relative to the length of the whole component
            double sigma = width / (RadRec.GetDt() * RadRec.GetData().size());
            //window the component with a truncated squared cosine window
            ApplyWindow(RadRec.GetData().begin(), RadRec.GetData().end(),
                FilteredR.begin(), TruncCosSq(sigma), relshift);
            ApplyWindow(VerRec.GetData().begin(), VerRec.GetData().end(),
                FilteredZ.begin(), TruncCosSq(sigma), relshift);
            // and sum up the values, this is eq. 5 in Svenningsen
            double rvalue = std::accumulate(FilteredR.begin(), FilteredR.end(), 0.0);
            double zvalue = std::accumulate(FilteredZ.begin(), FilteredZ.end(), 0.0);

            if (zvalue == 0.0)
              throw FatalException("Zero amplitude for Z-Receiver function !");
            //calculate the apparent velocity
            double vsapp = sin(0.5 * atan2(rvalue, zvalue)) / slowness;
            //store the apparent velocity values and the periods
            AppVel.push_back(vsapp);
            Velocities.push_back(vsapp);
            Periods.push_back(width);
          }
      }

    public:
      //! return the vector of apparent velocities
      const ttsdata &GetVelocities()
        {
          return Velocities;
        }
      //! Calculate absolute velocities from the radial and vertical components of the seismogram
      void CalcRFVel(const double slowness, const SeismicDataComp &RadComp,
          const SeismicDataComp &VerComp, ttsdata &AppVel)
      {
        SeismicDataComp RRecFunc, ZRecFunc;
        RFCalculator.CalcRecData(RadComp, VerComp, RRecFunc);
        RFCalculator.CalcRecData(VerComp, VerComp, ZRecFunc);
        AbsVelCalc(slowness, RRecFunc, ZRecFunc, AppVel);
      }

      //!Calculate absolute velocities from the radial receiver function and the vertical component of the seismogram
      void CalcRFVelFromRec(const double slowness, const SeismicDataComp &RRec,
          const SeismicDataComp &VerComp, ttsdata &AppVel)
      {
        SeismicDataComp ZRecFunc;
        RFCalculator.CalcRecData(VerComp, VerComp, ZRecFunc);
        AbsVelCalc(slowness, RRec, ZRecFunc, AppVel);
      }

      //! Write the velocity estiamtes and corresponding periods into an ascii file
      void WriteVelocities(const std::string filename)
      {
        std::ofstream outfile(filename.c_str());
        for (size_t i = 0; i < Velocities.size(); ++i)
          outfile << Periods.at(i) << " " << Velocities.at(i) << std::endl;
      }
      //!  The constructor takes three parameters for the receiver function estimation
      /*!  The constructor takes three parameters for the receiver function estimation
       * @param mysigma The width of the gaussian filter used in calculating the receiver function
       * @param myc The waterlevel, only relevant if spectral division is used for RF calculation
       * @param themethod Do we want to calculate the RF with spectral division of iterative deconvolution
       * @return
       */
      RFVelCalc(const double mysigma, const double myc,
          const RecCalc::trfmethod themethod = RecCalc::specdiv) :
          //we initialize the receiver function calculation with a shift of 5 seconds
              //this enables us catch the full waveform of the initial correlation peak in most cases
              //there might be a better way to do this
              RFCalculator(5, mysigma, myc, false, themethod)
          {
            //with normalization absolute velocity estimation does not work
            //so we make sure the RF is not normalized
            RFCalculator.SetNormalize(false);
          }
      RFVelCalc& operator=(const RFVelCalc& source)
      {
        if (this == &source)
          return *this;
        RFCalculator = source.RFCalculator;
        Velocities = source.Velocities;
        Periods = source.Periods;
        return *this;
      }
      RFVelCalc(const RFVelCalc &Old):
          RFCalculator(Old.RFCalculator), Velocities(Old.Velocities), Periods(
              Old.Periods)
          {

          }

      virtual ~RFVelCalc();
      };
  /* @} */
  }
#endif /*RFVELCALC_H_*/
