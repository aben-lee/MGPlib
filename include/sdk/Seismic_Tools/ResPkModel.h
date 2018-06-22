#ifndef CRESPKMODEL_H
#define CRESPKMODEL_H

#include <vector>
#include "SeismicModel.h"
#include "FatalException.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <boost/cast.hpp>
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class stores and writes model for the respktn 1D seismic code that we use for receiver function calculations
    /*! Our joint inversion uses respktn from C. Ammon to calculate synthetics for receiver function inversion.
     * This class stores the description of this model and provides methods to read such models, write such models
     * and generate scripts that calculate synthetic for such a model.
     *
     */
    class ResPkModel: public SeismicModel
      {
    private:
      double slowness;
      trealdata Strike;
      trealdata Dip;
    public:
      //! Get the slowness in s/km for the synthetic forward calculation
      double GetSlowness() const
        {
          return slowness;
        }
      //! Set the slowness in s/km for the synthetic forward calculation
      void SetSlowness(const double s)
        {
          slowness = s;
        }
      //! Read-only access to the vector of Strikes in each layer
      const trealdata &GetStrike() const
        {
          return Strike;
        }
      //! Read-write access to the vector of Strikes in each layer
      trealdata &SetStrike()
        {
          return Strike;
        }
      //! Read-only access to the vector of Dips in each layer
      const trealdata &GetDip() const
        {
          return Dip;
        }
      //! Read-write access to the vector of Dips in each layer
      trealdata &SetDip()
        {
          return Dip;
        }
      //! Read the model in its native format from a file
      virtual void ReadModel(const std::string filename)
      {
        ifstream infile(filename.c_str());
        char dummy[255];
        double number;
        int nlayers = -1;
        infile >> nlayers;
        infile.getline(dummy, 255);
        if (nlayers < 1)
          throw FatalException("Problem reading file: " + filename);
        Init(nlayers);
        int i = 0;
        while (infile.good())
          {
            //we throw away the layer number
            infile >> number;
            //if the layer number read succeeded we read in the rest
            if (infile.good())
              {
                infile >> SetPVelocity().at(i) >> SetSVelocity().at(i)
                    >> SetDensity().at(i) >> SetThickness().at(i)
                    >> SetQp().at(i) >> SetQs().at(i);
                infile >> SetStrike().at(i) >> SetDip().at(i) >> number;
                ++i;
              }
          }
        if (i != nlayers)
          throw FatalException("Problem reading file: " + filename);
      }

      //! Write the model in its native format to a file
      virtual void WriteModel(const std::string filename)
      {
        ofstream neu; //the file to write the model to

        neu.open(filename.c_str()); //open file for writing
        const unsigned int nlayers = GetPVelocity().size();
        if (Dip.size() != nlayers)
          {
            Dip.assign(nlayers, 0.0);
          }
        if (Strike.size() != nlayers)
          {
            Strike.assign(nlayers, 0.0);
          }
        neu << setw(3) << nlayers << " " << filename << endl;

        for (unsigned int i = 0; i < nlayers; ++i) //write all layers
          {
            neu.setf(ios::fixed);
            neu << setw(3);
            //we write out everything with a precision of 4 digits to make
            //sure that we represent the values well
            //only thickness only has a precision of 2 to allow value > 100
            //also 10m precision is sufficient for layer thickness
            //respktn is picky about formatting
            neu << i + 1 << setw(8) << setprecision(4) << GetPVelocity().at(i);
            neu << setw(8) << setprecision(4) << GetSVelocity().at(i)
                << setw(8) << setprecision(4) << GetDensity().at(i);
            neu << setw(8) << setprecision(2) << GetThickness().at(i)
                << setw(8) << setprecision(4) << GetQp().at(i);
            neu << setw(8) << setprecision(4) << GetQs().at(i);
            neu << setw(8) << setprecision(4) << GetStrike().at(i) << setw(8)
                << setprecision(4) << GetDip().at(i) << "  0.2500" << endl;
          }
        neu.close(); //close file
      }
      //! Write out a script that performs a forward calculation for the current model
      virtual void WriteRunFile(const std::string &filename)
      {
        const unsigned int mintime = 200; //the minimum time the seismogram has to have to be correct
        ofstream runfile;
        runfile.open(filename.c_str());
        runfile << "#!/bin/bash" << endl;
        runfile << "respknt 2>&1> /dev/null << eof" << endl;
        runfile << filename + ".mod" << endl;
        runfile << "n" << endl;
        runfile << "1" << endl;
        runfile << GetDt() << endl;
        runfile << max(boost::numeric_cast<unsigned int>((GetNpts() - 1)
            * GetDt()), mintime) << endl;
        runfile << GetSlowness() << endl;
        runfile << "f" << endl;
        runfile << "y" << endl;
        runfile << "eof" << endl;
        runfile.close();
      }
      ResPkModel();
      ResPkModel(const int nlayers):
          SeismicModel(nlayers)
          {

          }


      ResPkModel(const SeismicModel& source)
      {
        this->SeismicModel::operator=(source);
      }

      ResPkModel(const ResPkModel& source)
      {
        this->SeismicModel::operator=(source);
        this->slowness = source.slowness;
        copy(source.Strike.begin(), source.Strike.end(), back_inserter(
            this->Strike));
        copy(source.Dip.begin(), source.Dip.end(), back_inserter(this->Dip));
      }
      ResPkModel& operator=(const ResPkModel& source)
      {
        if (this == &source)
          return *this;
        this->SeismicModel::operator=(source);
        this->slowness = source.slowness;
        Strike.assign(source.Strike.size(), 0);
        Dip.assign(source.Dip.size(), 0);
        copy(source.Strike.begin(), source.Strike.end(), Strike.begin());
        copy(source.Dip.begin(), source.Dip.end(), Dip.begin());
        return *this;
      }
      virtual ~ResPkModel();
      };
  /* @} */
  }
#endif // CRESPKMODEL_H
