#ifndef ANISOSURFACEWAVESYNTHETIC_H_
#define ANISOSURFACEWAVESYNTHETIC_H_

#include "ParkSurfaceWaveData.h"
#include "AnisoSurfaceWaveModel.h"
#include <string>
#include <boost/shared_ptr.hpp>

#include "types.h"
#include "Util.h"


namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */
    //! Calculate synthetic anisotropic surface wave data
    class AnisoSurfaceWaveSynthetic
      {
    private:
      trealdata calculationperiods;
      boost::shared_ptr<const AnisoSurfaceWaveModel> Model;
      ParkSurfaceWaveData SynthData;
    public:
      const ParkSurfaceWaveData &GetSynthData() const
        {
          return SynthData;
        }
      const AnisoSurfaceWaveModel &GetModel() const
        {
          return *Model.get();
        }
      void SetModel(const boost::shared_ptr<AnisoSurfaceWaveModel> m)
        {
          Model = m;
        }
      void WriteModel(const std::string &filename) const
        {
          Model->WriteModel(filename);
        }
      void WritePlot(const std::string &filename) const
        {
          Model->WritePlot(filename);
        }
      void PreParallel(const std::string &filename)
      {
        Model->WriteRunFile(filename);
        Model->WriteModel(filename + ".mod");
      }

      ParkSurfaceWaveData SafeParallel(const std::string &filename)
      {
        const std::string fullname = filename;
        int result = std::system(("bash ./" + fullname).c_str());
        SynthData.ReadAscii(fullname + ".cvel");
        CleanFiles(fullname);
        return SynthData;
      }
      ParkSurfaceWaveData GetSynthData(const std::string &filename)
      {
        PreParallel(filename);
        return SafeParallel(filename);
      }

      AnisoSurfaceWaveSynthetic();
      virtual ~AnisoSurfaceWaveSynthetic();
      };
  /* @} */
  }
#endif /*ANISOSURFACEWAVESYNTHETIC_H_*/
