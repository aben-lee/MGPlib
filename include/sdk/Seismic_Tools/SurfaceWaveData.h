#ifndef SURFACEWAVEDATA_H_
#define SURFACEWAVEDATA_H_
#include <string>
#include "types.h" 
#include <fstream>
#include <iomanip>
#include "FatalException.h"
#include <cassert>
#include "Util.h"
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */
    //! A class to read, write and store fundamental mode surface wave dispersion data
    class SurfaceWaveData
      {
    private:
      trealdata periods;
      trealdata phasevelocities;
    public:
      //! Read-only access to the vector of phase velocities
      const trealdata &GetPhaseVelocities() const
        {
          return phasevelocities;
        }
      //! Read-only access to the vector of periods for the phase velocities
      const trealdata &GetPeriods() const
        {
          return periods;
        }
      //! Read-write access to phase velocities, the format might be changed in the future
      trealdata &SetPhaseVelocities()
        {
          return phasevelocities;
        }
      //! Read-write access to periods, the format might be changed in the future
      trealdata &SetPeriods()
        {
          return periods;
        }
      //! Read data from file, depending on the extension
      /*! Read data from file, depending on the extension
       * it will either call ReadAscii (for ending .asc), or ReadSurf96
       * (for any other ending).*/
      void ReadFile(const std::string &filename)
      {
        std::string ending = GetFileExtension(filename);
        if (ending == ".asc")
          {
            ReadAscii(filename);
          }
        else
          {
            ReadSurf96(filename);
          }
      }
      //! Read a file in general ascii format, i.e lines with period velocity each
      virtual void ReadAscii(const std::string &filename)
      {
        ifstream infile(filename.c_str());
        double currperiod, currphase;
        periods.clear();
        phasevelocities.clear();
        while (infile.good())
          {
            infile >> currperiod >> currphase;
            if (infile.good())
              {
                periods.push_back(currperiod);
                phasevelocities.push_back(currphase);
              }
          }
        if (periods.empty() || phasevelocities.empty() || periods.size() != phasevelocities.size())
          throw FatalException("Cannot read phase velocities from file: "
              + filename);
      }
      //! read data as produced by the computer programs in seismology codes ascii
      void ReadSurf96(const std::string &filename)
      {
        ifstream infile(filename.c_str());
        double currperiod, currphase, dummy;
        periods.clear();
        phasevelocities.clear();

        char line[255];
        infile.getline(line, 255);//we ignore the first line
        while (infile.good())
          {
            infile >> dummy >> dummy >> currperiod >> dummy >> currphase;
            if (infile.good())
              {
                periods.push_back(currperiod);
                phasevelocities.push_back(currphase);
              }
          }
        if (periods.empty() || phasevelocities.empty() || periods.size() != phasevelocities.size())
          throw FatalException("Cannot read phase velocities from file: "
              + filename);
      }
      //! Write the data in simple ascii format
      virtual void WriteAscii(const std::string &filename) const
      {
        ofstream outfile(filename.c_str());
        assert(periods.size() == phasevelocities.size());
        const unsigned int nelements = periods.size();
        for (unsigned int i = 0; i < nelements; ++i)
          {
            outfile << setw(10) << setprecision(5) << periods.at(i);
            outfile << setw(10) << setprecision(5) << phasevelocities.at(i);
            outfile << endl;
          }
      }
      SurfaceWaveData& operator=(const SurfaceWaveData& source)
      {
        if (this == &source)
          return *this;
        periods.clear();
        phasevelocities.clear();
        copy(source.periods.begin(), source.periods.end(), back_inserter(
            periods));
        copy(source.phasevelocities.begin(), source.phasevelocities.end(),
            back_inserter(phasevelocities));
        return *this;
      }
      SurfaceWaveData(const SurfaceWaveData &Old):
          periods(Old.periods), phasevelocities(Old.phasevelocities)
          {

          }

      SurfaceWaveData();
      virtual ~SurfaceWaveData();
      };
  /* @} */
  }
#endif /*SURFACEWAVEDATA_H_*/
