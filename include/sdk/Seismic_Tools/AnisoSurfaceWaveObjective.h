#ifndef ANISOSURFACEWAVEOBJECTIVE_H_
#define ANISOSURFACEWAVEOBJECTIVE_H_

#include "PlottableObjective.h"
#include "ParkSurfaceWaveData.h"
#include "AnisoSurfaceWaveSynthetic.h"
#include <string>
#include "AnisoSurfaceWaveModel.h"
#include <boost/bind.hpp>
#include <cmath>
#include "SeisTools.h"

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */
    //! This class calculates the misfit for anisotropic surface wave dispersion data
    class AnisoSurfaceWaveObjective: public PlottableObjective
      {
    private:
      ParkSurfaceWaveData MeasuredData;
      ParkSurfaceWaveData SynthData;
      AnisoSurfaceWaveSynthetic Synthetic;
      double errorlevel;
      double poisson;
      double backazimuth;
      double avelratio;
    public:

      //! Write the current model to ascii file for calculations
      virtual void WriteModel(const std::string &filename)
        {
          Synthetic.WriteModel(filename);
        }
      //! Write the current model to ascii file for plotting
      virtual void WritePlot(const std::string &filename)
        {
          Synthetic.WritePlot(filename);
        }
      //! Write synthetic data as ascii file
      virtual void WriteData(const std::string &filename)
        {
          SynthData.WriteAscii(filename);
        }
      //! Provide read only access to the synthetic data
      const ParkSurfaceWaveData &GetSynthetic() const
        {
          return SynthData;
        }
      AnisoSurfaceWaveObjective(const AnisoSurfaceWaveObjective &Old):
          PlottableObjective(Old), MeasuredData(Old.MeasuredData), SynthData(
              Old.SynthData), Synthetic(Old.Synthetic)
          {
            errorlevel = Old.errorlevel;
            poisson = Old.poisson;
            avelratio = Old.avelratio;
          }
      AnisoSurfaceWaveObjective& operator=(
          const AnisoSurfaceWaveObjective& source)
      {
        if (this == &source)
          return *this;
        PlottableObjective::operator=(source);
        MeasuredData = source.MeasuredData;
        SynthData = source.SynthData;
        Synthetic = source.Synthetic;
        errorlevel = source.errorlevel;
        poisson = source.poisson;
        avelratio = source.avelratio;
        return *this;
      }

      AnisoSurfaceWaveObjective(const ParkSurfaceWaveData &Data,
          const double ba, const double avel, const double pois = 1.8,
          const double err = 0.01):
          MeasuredData(Data)
          {
            avelratio = avel;
            backazimuth = ba;
            poisson = pois;
            errorlevel = err;
          }

      virtual ~AnisoSurfaceWaveObjective();
      //! We need clone and create for building an array of derived objects, see FAQ lite 20.8, the return type depends on the derived class
      virtual AnisoSurfaceWaveObjective *clone() const
        {
          return new AnisoSurfaceWaveObjective(*this);
        }
      //! Some operations cannot be done in parallel, these are done before
      virtual void PreParallel(const ttranscribed &member)
      {
        const unsigned int nfulllayers = member.size() / 6;
        boost::shared_ptr<AnisoSurfaceWaveModel> Model(
            new AnisoSurfaceWaveModel);
        ttranscribed thickness(nfulllayers), velocity(nfulllayers), angle(
            nfulllayers), deltaangle(nfulllayers), anisotropy1(nfulllayers),
            anisotropy2(nfulllayers);
        copy(member.begin(), member.begin() + nfulllayers, thickness.begin()); //copy values
        copy(member.begin() + nfulllayers, member.begin() + 2 * nfulllayers,
            velocity.begin());
        transform(member.begin() + 2 * nfulllayers, member.begin() + 3
            * nfulllayers, angle.begin(), boost::bind(std::minus<double>(), _1,
            backazimuth));
        copy(member.begin() + 3 * nfulllayers,
            member.begin() + 4 * nfulllayers, deltaangle.begin());
        copy(member.begin() + 4 * nfulllayers,
            member.begin() + 5 * nfulllayers, anisotropy1.begin());
        copy(member.begin() + 5 * nfulllayers,
            member.begin() + 6 * nfulllayers, anisotropy2.begin());

        //Set parameters for Modes
        copy(thickness.begin(), thickness.end(), back_inserter(
            Model->SetThicknesses()));
        copy(velocity.begin(), velocity.end(), back_inserter(Model->SetVs()));
        //No link assumed between the two anisotropic coefficients; Set B to anisotropy 2
        copy(anisotropy2.begin(), anisotropy2.end(), back_inserter(
            Model->SetB()));

        // Set B to anisotropy2 for the first layers (always >0) - No relation between seismic and electrical anisotropies
        //        copy(anisotropy2.begin(), anisotropy2.begin() + (nfulllayers - 2) ,back_inserter(Model->SetB()));
        // For the last two layers of the model (asthenosphere + HS), we introduce a relation between seismic and electrical anisotropies
        // Set Temp to Pow(10, an1)
        //        transform(anisotropy1.begin()+ (nfulllayers - 2), anisotropy1.end(), back_inserter(
        //                Model->SetTemp()), Pow10());
        // Set B to product of Temp and anisotropy2
        //        transform(anisotropy2.begin()+ (nfulllayers-2), anisotropy2.end(),
        //            Model->GetTemp().begin(), back_inserter(Model->SetB()),std::multiplies<double>());

        //Set anisotropy angle to sum of angle and deltaangle - phi
        transform(angle.begin(), angle.end(), deltaangle.begin(),
            back_inserter(Model->SetPhi()), std::plus<double>());
        //Set angle1 to product of cos(2phi) - cos (2*phi)
        transform(Model->GetPhi().begin(), Model->GetPhi().end(),
            back_inserter(Model->SetAngle1()), CalcAngle1());
        //Set AnisoS to product of B and angle1 - B*cos(2*phi)
        transform(Model->GetB().begin(), Model->GetB().end(),
            Model->GetAngle1().begin(), back_inserter(Model->SetAnisoS()),
            std::multiplies<double>());
        //Set Vsapp to sum of Vs and AnisoS - Vs + B*cos(2*phi)
        transform(Model->GetVs().begin(), Model->GetVs().end(),
            Model->GetAnisoS().begin(), back_inserter(Model->SetVsapp()),
            std::plus<double>());
        //We compute Vp and Density from Vsapp
        transform(Model->GetVsapp().begin(), Model->GetVsapp().end(),
            back_inserter(Model->SetDensities()), CalcDensity());
        transform(Model->GetVsapp().begin(), Model->GetVsapp().end(), //P Velocity is calculated by multiplication of SVel by poisson's ratio
            back_inserter(Model->SetVp()), boost::bind(multiplies<double> (),
                _1, poisson));

        Synthetic.SetModel(Model);
        Synthetic.PreParallel(GetParallelID());
      }
      //! Some operations cannot be done in parallel, these are done after, returns the misfit value
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      //! The core performance calculation, has to be safe to be done in parallel
      virtual void SafeParallel(const ttranscribed &member)
      {
        SynthData = Synthetic.SafeParallel(GetParallelID());
        assert(errorlevel> 1e-4);
        // an errorlevel < 0.01% is absolutely unrealistic
        const unsigned int ndata = min(SynthData.GetPhaseVelocities().size(),
            MeasuredData.GetPhaseVelocities().size());
        SetMisfit().resize(ndata); // we need vectors of the right size for misfit
        SetSynthData().resize(ndata); // and  data
        double returnvalue = 0.0; // init returnvalue
        for (unsigned int i = 0; i < ndata; ++i)
          {
            returnvalue += CalcMisfit(MeasuredData.GetPhaseVelocities().at(i),
                SynthData.GetPhaseVelocities().at(i), 0.0, errorlevel, i);
          }

        SetRMS(pow(returnvalue / ndata, 1.0 / GetFitExponent())); //return misfit
      }
      };
  /* @} */
  }
#endif /*ANISOSURFACEWAVEOBJECTIVE_H_*/
