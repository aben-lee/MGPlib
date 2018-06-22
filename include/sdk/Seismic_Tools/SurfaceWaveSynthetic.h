#ifndef SURFACEWAVESYNTHETIC_H_
#define SURFACEWAVESYNTHETIC_H_
#include "Sdisp96Model.h"
#include "SurfaceWaveData.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! Calculate synthetic fundamental mode Rayleigh phase velocity data from an isotropic 1D model
    class SurfaceWaveSynthetic
      {
    private:
      trealdata calculationperiods;
      Sdisp96Model Model;
      SurfaceWaveData SynthData;
    public:
      //! For a parallel execution, these are things that have to be done before any parallel block
      void PreParallel(const std::string &filename)
      {

        Model.WriteRunFile("surf" + filename, calculationperiods);
        Model.WriteModel("surf" + filename + ".mod");
      }
      //! Operations that are safe to perform in parallel
      SurfaceWaveData SafeParallel(const std::string &filename)
      {
        const std::string fullname = "./surf" + filename;
        int result = std::system((std::string("bash ")+fullname).c_str());
        SynthData.ReadSurf96(fullname + ".asc96");
        boost::filesystem::remove_all(fullname);
        boost::filesystem::remove_all(fullname + "_dir");
        return SynthData;
      }
      //! Read only access to the current seismic model
      const SurfaceWaveModel &GetModel()
        {
          return Model;
        }
      //! Get the vector of periods in s for which we want to calculate phase velocities
      const trealdata &GetCalculationPeriods() const
        {
          return calculationperiods;
        }
      //! Set the vector of periods in s for which we want to calculate phase velocities
      void SetCalculationPeriods(const trealdata &c)
        {
          calculationperiods.clear();
          std::copy(c.begin(),c.end(),std::back_inserter(calculationperiods));
        }
      //! Set the model for which we want to calculate the data
      void SetModel(const Sdisp96Model &m)
        {
          Model = m;
        }
      //! Perform a complete forward calculation and return the calculated data, not thread safe as it calls PreParallel
      SurfaceWaveData GetSynthData(const std::string &filename)
      {
        PreParallel(filename);
        return SafeParallel(filename);
      }
      SurfaceWaveSynthetic();
      virtual ~SurfaceWaveSynthetic();
      };
  /* @} */
  }
#endif /*SURFACEWAVESYNTHETIC_H_*/
