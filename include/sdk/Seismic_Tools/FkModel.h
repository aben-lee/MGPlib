#ifndef CFKMODEL_H
#define CFKMODEL_H

#include "SeismicModel.h"
#include <fstream>
#include <iomanip>
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! A model for forward calculations with a wavenumber integration code, currently not in use and might be removed in a later version
    class FkModel: public SeismicModel
      {
    private:
      trealdata RecDist;
    public:
      //! Read-only access to the vector of receiver distances
      const trealdata &GetRecDist() const
        {
          return RecDist;
        }
      //! Read-write access to the vector of receiver distances
      trealdata &SetRecDist()
        {
          return RecDist;
        }
      //! Read the model in its native format from a file
      virtual void ReadModel(const std::string filename)
      {
        ifstream infile(filename.c_str());
        char dummy[255];
        double number;
        int nlayers, nstat;
        double SourceDepth, dt;
        int npts;
        infile.getline(dummy, 255);
        infile.getline(dummy, 255);
        infile.getline(dummy, 255);
        infile >> number >> SourceDepth >> number >> number >> npts >> dt
            >> nlayers >> number;
        infile.getline(dummy, 255);
        infile.getline(dummy, 255);
        SetSourceDepth(SourceDepth);
        SetNpts(npts);
        SetDt(dt);
        Init(nlayers);
        for (int i = 0; i < nlayers; ++i)
          infile >> SetThickness().at(i) >> SetPVelocity().at(i)
              >> SetSVelocity().at(i) >> SetDensity().at(i) >> SetQp().at(i)
              >> SetQs().at(i);
        infile >> number;
        infile.getline(dummy, 255);
        infile.getline(dummy, 255);
        infile >> nstat >> number >> number >> number >> number;
        SetRecDist().assign(nstat, 0);
        for (int i = 0; i < nstat; ++i)
          infile >> SetRecDist().at(i) >> number >> number;
      }
      //! Write the model in its native format to a file
      virtual void WriteModel(const std::string filename)
      {
        ofstream neu(filename.c_str()); //the file to write the model to
        int sourceindex = 0; // the index of the source layer
        double sourcethickness = 0; //thickness of the layer above the source (FK needs dummy layer)
        double totalthickness = 0; // counter to add up thicknesses to calculate sourcethickness
        unsigned int totallayers = GetThickness().size();

        sourceindex = FindLayer(GetSourceDepth()); //find out in which layer the source lies
        for (int i = 0; i < sourceindex; ++i)
          totalthickness += GetThickness().at(i); // add up the thickness of all layers above the source (without sourcelayer)
        sourcethickness = GetSourceDepth() - totalthickness; //calculate the thickness of the sourcelayer so that source lies
        // at lower boundary
        neu
            << ".F.                                                                             \n"; //write File header
        neu
            << "    0   64                                                                      \n"; //FK-Code is VERY
        neu << "GREEN.1\n"; //picky about spaces etc. !!
        neu << "    6.0      " << setprecision(1) << setiosflags(
            ios::scientific) << GetSourceDepth() << resetiosflags(
            ios::scientific) << "    1" << setw(5) << setfill(' ')
            << setprecision(8) << GetNpts() / 2 << setw(5) << setfill(' ')
            << GetNpts() << "    " << setprecision(3)
            << setiosflags(ios::fixed) << GetDt() << resetiosflags(ios::fixed)
            << setfill(' ') << setw(6) << totallayers << "    1\n"; //see documentation
        // of FK for meaning
        neu
            << "    1    1    1    1    1    1    1    1    1    1    0                         \n";

        for (unsigned int i = 0; i < totallayers; ++i) //write all layers
          {
            neu << setprecision(4) << setiosflags(ios::scientific) << " "
                << GetThickness().at(i) << " " << GetPVelocity().at(i) << " ";
            neu << GetSVelocity().at(i) << " " << GetDensity().at(i) << " "
                << GetQp().at(i) << " " << GetQs().at(i) << endl;
          }

        neu << "   " << sourceindex + 1
            << "                                                                           \n";
        neu << "  0.4000000E+03  1.500000E+00         0\n"; //write epilogue for FK-Code
        neu << setw(5) << setfill(' ') << GetRecDist().size()
            << "  10000.0     30.0      0.4       0.3\n";
        for (unsigned int i = 0; i < GetRecDist().size(); ++i)
          neu << "   " << setw(3) << setprecision(3) << setiosflags(ios::fixed
              | ios::showpoint) << GetRecDist().at(i)
              << "       0.0    9999.0 \n";
        neu << "    " << flush;
        neu << "\n";
      }
      FkModel():
          SeismicModel()
          {
          }
      virtual ~FkModel();
      };
  /* @} */
  }
#endif // CFKMODEL_H
