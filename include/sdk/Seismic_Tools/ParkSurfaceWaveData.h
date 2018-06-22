#ifndef PARKSURFACEWAVEDATA_H_
#define PARKSURFACEWAVEDATA_H_

#include <vector>
#include <string>
#include <boost/cstdint.hpp>
#include "SurfaceWaveData.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include "FatalException.h"
#include <cassert>

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    class ParkSurfaceWaveData: public SurfaceWaveData
      {
    public:
      virtual void ReadAscii(const std::string &filename)
        {
          std::ifstream infile(filename.c_str());
          double currfreq, currphase;
          SetPeriods().clear();
          SetPhaseVelocities().clear();
          if (!infile.good())
            {
              throw FatalException("Cannot open file " + filename);
            }
          while (infile.good())
            {
              infile >> currfreq >> currphase;
              if (infile.good())
                {
                  SetPeriods().push_back(1.0 / currfreq);
                  SetPhaseVelocities().push_back(currphase);
                }
            }
          if (GetPeriods().empty() || GetPhaseVelocities().empty())
            throw FatalException("Cannot read phase velocities from file: "
                + filename);
        }

      virtual void WriteAscii(const std::string &filename) const
        {
          std::ofstream outfile(filename.c_str());
          assert(GetPeriods().size() == GetPhaseVelocities().size());
          const unsigned int nelements = GetPeriods().size();
          for (unsigned int i = 0; i < nelements; ++i)
            {
              outfile << 1.0 / GetPeriods().at(i);
              outfile << " " << GetPhaseVelocities().at(i);
              outfile << std::endl;
            }
          if (!outfile.good())
            throw FatalException("Cannot write to file: " + filename);
        }

      ParkSurfaceWaveData();
      virtual ~ParkSurfaceWaveData();
      };
  /* @} */
  }
#endif /*PARKSURFACEWAVEDATA_H_*/
