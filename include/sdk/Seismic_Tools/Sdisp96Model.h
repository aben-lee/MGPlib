#ifndef SDISP96MODEL_H_
#define SDISP96MODEL_H_

#include "SurfaceWaveModel.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <iterator>
#include <iomanip>
#include <boost/filesystem.hpp>
#include "FatalException.h"
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class can write files specific for the synthetic surface wave codes that are part of the computer programs in seismology
    class Sdisp96Model: public SurfaceWaveModel
      {
    private:
      bool isSpherical;
    public:
      //! Do we want a spherical model or a flat earth model
      void SetSpherical(const bool s)
        {
          isSpherical = s;
        }
      //! Read the model from a file
      virtual void ReadModel(const std::string &filename);
      //! Write them model to a file so that the forward codes can use it
      virtual void WriteModel(const std::string &filename) const
      {
        CheckConsistency();
        ofstream outfile(filename.c_str());
        outfile << "MODEL" << endl;
        outfile << GetName() << endl;
        outfile << "ISOTROPIC" << endl;
        outfile << "KGS" << endl;
        if (isSpherical)
          {
            outfile << "SPHERICAL EARTH" << endl;
          }
        else
          {
            outfile << "FLAT EARTH" << endl;
          }
        outfile << "1-D" << endl;
        outfile << "CONSTANT VELOCITY" << endl;
        outfile << "LINE08" << endl;
        outfile << "LINE09" << endl;
        outfile << "LINE10" << endl;
        outfile << "LINE11" << endl;
        outfile
            << "HR         VP         VS     RHO    QP    QS   ETAP    ETAS    FREFP    FREFS"
            << endl;
        const int nlayers = GetPvVelocities().size();
        for (int i = 0; i < nlayers; ++i)
          {
            outfile << setw(7) << setprecision(2) << GetThicknesses().at(i);
            outfile << setw(7) << setprecision(3) << GetPvVelocities().at(i);
            outfile << setw(7) << setprecision(3) << GetSvVelocities().at(i);
            outfile << setw(7) << setprecision(3) << GetDensities().at(i);
            outfile << setw(7) << setprecision(3) << GetQkappa().at(i);
            outfile << setw(7) << setprecision(3) << GetQmu().at(i);
            outfile << setw(7) << setprecision(3) << GetEta().at(i);
            outfile << setw(7) << setprecision(3) << GetEta().at(i);
            outfile << " 1.0  1.0" << endl;
          }
        if (!outfile.good())
          throw FatalException("Problem writing to file: " + filename);
      }
      //! Write out a script file that when run creates synthetic data with the name filename+'.asc'
      virtual void WriteRunFile(const std::string &filename, const std::vector<
          double> periods) const
      {
        CheckConsistency();
        assert(periods.size() > 0);
        ofstream runfile(filename.c_str());
        ofstream periodfile((filename + ".per").c_str());
        copy(periods.begin(), periods.end(), ostream_iterator<double> (
            periodfile, "\n"));
        boost::filesystem::path Path(filename);
        string dirname(filename + "_dir");
        runfile << "#!/bin/bash" << endl;
        runfile << "mkdir " << dirname << endl;
        runfile << "mv " << filename << ".* " << dirname << endl;
        runfile << "cd " << dirname << endl;
        runfile << "sprep96  -M " << Path.leaf() << ".mod" << " -R -PARR "
            << Path.leaf() << ".per -NMOD 1 2>&1> /dev/null" << endl;
        runfile << "sdisp96 2>&1> /dev/null" << endl;
        runfile << "sdpsrf96 -R -ASC 2>&1> /dev/null" << endl;
        runfile << "cp SDISPR.ASC ../" << filename + ".asc96" << endl;

        if (!runfile.good())
          throw FatalException("Problem writing to file: " + filename);
      }
      Sdisp96Model& operator=(const Sdisp96Model& source)
      {
        if (this == &source)
          return *this;
        SurfaceWaveModel::operator=(source);
        isSpherical = source.isSpherical;
        return *this;
      }
      Sdisp96Model(const Sdisp96Model &Old) :
          SurfaceWaveModel(Old), isSpherical(Old.isSpherical)
          {

          }
      Sdisp96Model(const SurfaceWaveModel &Old) :
        SurfaceWaveModel(Old)
        {
        }
      ;
      Sdisp96Model() :
          isSpherical(true)
          {
          }
      virtual ~Sdisp96Model();
      };
  /* @} */
  }
#endif /*SDISP96MODEL_H_*/
