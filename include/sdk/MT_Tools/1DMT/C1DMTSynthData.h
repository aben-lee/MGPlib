#ifndef C1DMTSYNTHDATA_H
#define C1DMTSYNTHDATA_H

#include "MTStation.h"
#include "types.h"
#include <vector>
#include <string>
#include "VecMat.h"
#include <fstream>
#include <algorithm>
#include <cassert>
#include "FatalException.h"

namespace gplib
  {
  /** \addtogroup mttools MT data analysis, processing and inversion */
  /* @{ */
    const int frequenzen = 50;
    //these are the frequencies we calculate the response at, if no frequencies are set before the calculation
    const float T[frequenzen] =
      { 0.0025, 0.00308337, 0.00513901, 0.00625, 0.0104167, 0.0125, 0.0208333,
          0.025, 0.0416667, 0.05, 0.0833333, 0.1, 0.166667, 0.2, 0.333333, 0.4,
          0.667, 0.64, 1.06667, 1.29333, 2.15554, 2.59997, 4.33332, 5.19994,
          8.66701, 10.666667, 16.000, 21.333, 32.000, 42.667, 64.0, 85.332,
          127.992, 170.678, 256.016, 341.297, 512.033, 682.594, 1023.541,
          1366.120, 2049.180, 2732.240, 4098.361, 5464.481, 8196.722,
          10869.565, 16393.443, 28800, 43200, 86400 };

//! Calculate synthetic MT data for a 1D model using Cagniard's algorithm
    class C1DMTSynthData: public MTStation
      {

     private:
      tcompdata Z;
      void Calc()
      {
        dcomp omegamu;
        dcomp kcurr, klow;
        dcomp xi;
        vector<dcomp> alpha(thickness.size(), 0);
        dcomp adm;
        double d;
        double sigmacurr, sigmalow;
        Z.clear();
        for (unsigned int i = 0; i < calc_frequencies.size(); ++i)
          {
            omegamu = -I * 8e-7 * PI * PI * calc_frequencies.at(i);
            fill(alpha.begin(), alpha.end(), 0);
            sigmacurr = 1.0 / resistivity.back();
            kcurr = sqrt(omegamu * sigmacurr);
            for (int layerindex = thickness.size() - 2; layerindex >= 0; --layerindex)
              {
                sigmalow = 1.0 / resistivity.at(layerindex + 1);
                sigmacurr = 1.0 / resistivity.at(layerindex);
                kcurr = sqrt(omegamu * sigmacurr);
                klow = sqrt(omegamu * sigmalow);
                if (kcurr.real() < 0.0)
                  {
                    kcurr *= -1.0;
                    klow *= -1.0;
                  }
                xi = omegamu * (sigmacurr - sigmalow) / std::pow(kcurr + klow, 2);
                alpha.at(layerindex + 1) = (xi + alpha.at(layerindex + 1)) / (1. + xi * alpha.at(
                    layerindex + 1));
                d = thickness.at(layerindex) * 1000.0;
                alpha.at(layerindex) = alpha.at(layerindex + 1) * exp(-2. * kcurr * d);
              }
            adm = kcurr / (-I * 2. * PI * calc_frequencies.at(i)) * ((1.
                - alpha.at(0)) / (1. + alpha.at(0)));
            Z.push_back(conj(1. / (1000.0 * adm)));

          }
      }
      trealdata calc_frequencies;
      trealdata resistivity; //
      trealdata thickness; // Thickness for each layer
      trealdata reserrors; // the errors of the model parameters, only used for plotting
      trealdata thickerrors;
    public:
      //! Read only access to the vector of resistivities for the 1D model from top to bottom in Ohmm
      const trealdata &GetResistivities()
        {
          return resistivity;
        }
      //! Read only access to the vector of layer thicknesses for the 1D model from top to bottom in km
      const trealdata &GetThicknesses()
        {
          return thickness;
        }
      //! Read-write access to the vector of resistivities for the 1D model from top to bottom in Ohmm
      void SetResistivities(const trealdata &res)
        {
          resistivity = res;
        }
      //! Read only access to the vector of layer thicknesses for the 1D model from top to bottom in km
      void SetThicknesses(const trealdata &thick)
        {
          thickness = thick;
        }
      //! Set the error on the resistivities this is purely for plotting of inversion results
      void SetResistivityErrors(const trealdata &re)
        {
          reserrors = re;
        }
      //! Set the error on the thicknesses this is purely for plotting of inversion results
      void SetThicknessErrors(const trealdata &te)
        {
          thickerrors = te;
        }
      //! Return the model as a single vector first log10 of all resistivities, then all thicknesses in km
      gplib::rvec GetModelVector()
      {
        assert(resistivity.size() == thickness.size());
        const int length = resistivity.size();
        gplib::rvec result(length * 2);
        for (int i = 0; i < length; ++i)
          {
            result(i) = log10(resistivity.at(i));
            result(i + length) = thickness.at(i);
          }
        return result;
      }
      //! Write model into file for cagniard algorithm
      void WriteModel(std::string filename)
      {
        assert(resistivity.size() == thickness.size());
        ofstream outfile(filename.c_str());

        outfile << thickness.size() << endl;
        for (unsigned int i = 0; i < thickness.size(); ++i)
          {
            outfile << thickness.at(i) << "  " << resistivity.at(i) << endl;
          }
      }
      //! Read the model from a file
      void ReadModel(std::string filename)
      {
        int layers;
        double currthick, curres;
        int i = 0;

        ifstream infile(filename.c_str());
        infile >> layers;
        if (!infile.good() || layers < 0)
          throw FatalException("Problem reading file: " + filename);
        thickness.reserve(layers);
        resistivity.reserve(layers);
        while (infile.good())
          {
            infile >> currthick >> curres;
            if (infile.good())
              {
                thickness.push_back(currthick);
                resistivity.push_back(curres);
                ++i;
              }
          }
        assert(resistivity.size() == thickness.size());
        assert(i==layers);
      }
      //! Write out a file that can be used for plotting with xmgrace first column depth, second column resistivity
      void WritePlot(std::string filename)
      {
        ofstream outfile(filename.c_str());
        double cumthick = 0;
        assert(resistivity.size() == thickness.size());

        for (unsigned int i = 0; i < thickness.size(); ++i)
          {
            outfile << cumthick << "  " << resistivity.at(i);
            if (!thickerrors.empty() || !reserrors.empty())
              outfile << " " << thickerrors.at(i) << " " << reserrors.at(i);
            outfile << endl;
            cumthick += thickness.at(i);
            outfile << cumthick << " " << resistivity.at(i);
            if (!thickerrors.empty() || !reserrors.empty())
              outfile << " " << thickerrors.at(i) << " " << reserrors.at(i);
            outfile << endl;
          }
      }
      //! Calculate the synthetic data given the previously set parameters
      virtual void CalcSynthetic()
      {
        assert(resistivity.size() == thickness.size());
        calc_frequencies = GetFrequencies();
        if (calc_frequencies.empty())
          {
            for (int i = 0; i < frequenzen; ++i)
              calc_frequencies.push_back(1.0 / T[i]);
          }
        Calc();
        Assign(calc_frequencies.size());
        for (unsigned int i = 0; i < calc_frequencies.size(); ++i)
          {
            MTData.at(i).frequency = calc_frequencies.at(i);
            MTData.at(i).Zxy = Z.at(i);
            MTData.at(i).Zyx = -Z.at(i);
          }
        Update();
      }
      //! Provide a "virtual copy constructor"
      virtual C1DMTSynthData *clone() const
        {
          return new C1DMTSynthData(*this);
        }
      C1DMTSynthData(const C1DMTSynthData &old) :
          MTStation(old), Z(old.Z), calc_frequencies(old.calc_frequencies),
              resistivity(old.resistivity), thickness(old.thickness), reserrors(
                  old.reserrors), thickerrors(old.thickerrors)
          {

          }

      C1DMTSynthData()
      {

      }
      virtual ~C1DMTSynthData()
      {

      }
    };
    /* @} */
  }
#endif
