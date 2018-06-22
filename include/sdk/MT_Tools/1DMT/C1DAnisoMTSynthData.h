#ifndef C1DANISOMTSYNTHDATA_H_
#define C1DANISOMTSYNTHDATA_H_

#include "MTStation.h"
#include "VecMat.h"
#include <cassert>
#include <limits>
#include <fstream>
#include "NumUtil.h"
#include "FatalException.h"

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */
    //! Calculate response of a 1D anisotropic model, code is based on Pek and Santos fortran code
    class C1DAnisoMTSynthData: public MTStation
      {
        const int frequenzen = 50;
        const float T[frequenzen] =
          { 0.0025, 0.00308337, 0.00513901, 0.00625, 0.0104167, 0.0125, 0.0208333,
              0.025, 0.0416667, 0.05, 0.0833333, 0.1, 0.166667, 0.2, 0.333333, 0.4,
              0.667, 0.64, 1.06667, 1.29333, 2.15554, 2.59997, 4.33332, 5.19994,
              8.66701, 10.666667, 16.000, 21.333, 32.000, 42.667, 64.0, 85.332,
              127.992, 170.678, 256.016, 341.297, 512.033, 682.594, 1023.541,
              1366.120, 2049.180, 2732.240, 4098.361, 5464.481, 8196.722,
              10869.565, 16393.443, 28800, 43200, 86400 };
    private:
      trealdata calc_frequencies;
      trealdata thicknesses; // Thickness for each layer
      trealdata strikes;
      trealdata slants;
      trealdata dips;
      trealdata rho1;
      trealdata rho2;
      trealdata rho3;
      trealdata effcond1;
      trealdata effcond2;
      trealdata effstrike;

      //! Transform angles and resistivities into effective horizontal values, has to be called before CalcZ
      void TransformRho()
      {
        assert(rho1.size() == rho2.size());
        assert(rho1.size() == rho3.size());
        assert(rho1.size() == strikes.size());
        assert(rho1.size() == slants.size());
        assert(rho1.size() == dips.size());

        const unsigned int nlayers = rho1.size();
        effcond1.assign(nlayers, 0.0);
        effcond2.assign(nlayers, 0.0);
        effstrike.assign(nlayers, 0.0);
        for (unsigned int i = 0; i < nlayers; ++i)
          {
            double s1 = 1. / rho1.at(i);//transform to conductivity
            double s2 = 1. / rho2.at(i);
            double s3 = 1. / rho3.at(i);
            double strike = PI * strikes.at(i) / 180.0; //transform angles to radian
            double dip = PI * dips.at(i) / 180.0;
            double slant = PI * slants.at(i) / 180.0;
            //calculate some frequently used sines and cosines
            double sps = sin(strike);
            double cps = cos(strike);
            double sth = sin(dip);
            double cth = cos(dip);
            double sfi = sin(slant);
            double cfi = cos(slant);
            double pom1 = s1 * cfi * cfi + s2 * sfi * sfi;
            double pom2 = s1 * sfi * sfi + s2 * cfi * cfi;
            double pom3 = (s1 - s2) * sfi * cfi;
            double c2ps = cps * cps;
            double s2ps = sps * sps;
            double c2th = cth * cth;
            double s2th = sth * sth;
            double csps = cps * sps;
            double csth = cth * sth;
            //contruct the conductivity tensor elements
            double sg11 = pom1 * c2ps + pom2 * s2ps * c2th - 2. * pom3 * cth
                * csps + s3 * s2th * s2ps;
            double sg12 = pom1 * csps - pom2 * c2th * csps + pom3 * cth * (c2ps
                - s2ps) - s3 * s2th * csps;
            double sg13 = -pom2 * csth * sps + pom3 * sth * cps + s3 * csth
                * sps;
            double sg21 = sg12;
            double sg22 = pom1 * s2ps + pom2 * c2ps * c2th + 2. * pom3 * cth
                * csps + s3 * s2th * c2ps;
            double sg23 = pom2 * csth * cps + pom3 * sth * sps - s3 * csth
                * cps;
            double sg31 = sg13;
            double sg32 = sg23;
            double sg33 = pom2 * s2th + s3 * c2th;
            double axx = sg11 - sg13 * sg31 / sg33;
            double axy = sg12 - sg13 * sg32 / sg33;
            double ayx = sg21 - sg31 * sg23 / sg33;
            double ayy = sg22 - sg23 * sg32 / sg33;
            //calculate effective horizontal conductivity
            double da12 = sqrt((axx - ayy) * (axx - ayy) + 4.0 * axy * ayx);
            effcond1.at(i) = (0.5 * (axx + ayy + da12));
            effcond2.at(i) = (0.5 * (axx + ayy - da12));
            if (fcmp(da12, 0.0, std::numeric_limits<double>::epsilon()) != 0)
              {
                effstrike.at(i) = 0.5 * acos((axx - ayy) / da12);
              }
            else
              {
                effstrike.at(i) = 0.0;
              }
            if (axy < 0.0)
              effstrike.at(i) *= -1.0;
            //std::cout << effcond1.at(i) << " " << effcond2.at(i) << " " << effstrike.at(i)*180./PI << std::endl;

          }
      }
      //! Calculate the response

      inline dcomp dfp(const dcomp x)
        {
          //std::cout << 1.0 + exp(-2.0 * x) << std::endl;
          return 1.0 + exp(-2.0 * x);
        }

      inline dcomp dfm(const dcomp x)
        {
          //std::cout << 1.0 - exp(-2.0 * x) << std::endl;
          return 1.0 - exp(-2.0 * x);
        }
      void CalcZ()
      {
        dcomp omegamu;
        const double convfactor = 1. / (1000. * mu);

        for (unsigned int i = 0; i < calc_frequencies.size(); ++i)
          {
            omegamu = -I * 8e-7 * PI * PI * calc_frequencies.at(i);
            dcomp k0 = (1. - I) * 2.0e-3 * PI * sqrt(calc_frequencies.at(i)
                / 10.0);
            dcomp zxyrot = k0 / sqrt(effcond1.back());
            dcomp zyxrot = -k0 / sqrt(effcond2.back());
            double currstrike = effstrike.back();
            MTTensor CurrZ(dcomp(0.0, 0.0), zxyrot, zyxrot, dcomp(0.0, 0.0),
                calc_frequencies.at(i));
            for (int layerindex = thicknesses.size() - 2; layerindex >= 0; --layerindex)
              {
                double currthick = 1000.0 * thicknesses.at(layerindex);
                if (currstrike != effstrike.at(layerindex) && effcond1.at(layerindex)
                    != effcond2.at(layerindex))
                  {
                    CurrZ.Rotate(effstrike.at(layerindex) - currstrike);
                    currstrike = effstrike.at(layerindex);
                  }
                MTTensor BottomZ(CurrZ);
                //std::cout << CurrZ.GetZxy() * convfactor<< " " << CurrZ.GetZyx() * convfactor << std::endl;
                dcomp dz1 = k0 / sqrt(effcond1.at(layerindex));
                dcomp dz2 = k0 / sqrt(effcond2.at(layerindex));
                dcomp ag1 = k0 * sqrt(effcond1.at(layerindex)) * currthick;
                dcomp ag2 = k0 * sqrt(effcond2.at(layerindex)) * currthick;

                dcomp detzbottom = BottomZ.GetDet();
                dcomp denominator = detzbottom * dfm(ag1) * dfm(ag2) / (dz1
                    * dz2) + BottomZ.GetZxy() * dfm(ag1) * dfp(ag2) / dz1
                    - BottomZ.GetZyx() * dfp(ag1) * dfm(ag2) / dz2 + dfp(ag1)
                    * dfp(ag2);
                //std::cout << dz1 << dz2 << ag1 << ag2 << detzbottom << denominator << std::endl;
                CurrZ.SetZxx() = 4.0 * BottomZ.GetZxx() * exp(-ag1 - ag2)
                    / denominator;
                CurrZ.SetZxy() = (BottomZ.GetZxy() * dfp(ag1) * dfp(ag2)
                    - BottomZ.GetZyx() * dfm(ag1) * dfm(ag2) * dz1 / dz2
                    + detzbottom * dfp(ag1) * dfm(ag2) / dz2 + dfm(ag1) * dfp(
                    ag2) * dz1) / denominator;
                CurrZ.SetZyx() = (BottomZ.GetZyx() * dfp(ag1) * dfp(ag2)
                    - BottomZ.GetZxy() * dfm(ag1) * dfm(ag2) * dz2 / dz1
                    - detzbottom * dfm(ag1) * dfp(ag2) / dz1 - dfp(ag1) * dfm(
                    ag2) * dz2) / denominator;
                CurrZ.SetZyy() = 4.0 * BottomZ.GetZyy() * exp(-ag1 - ag2)
                    / denominator;
              }
            CurrZ.SetRotangle() = currstrike;
            CurrZ.SetZxx() = convfactor * conj(CurrZ.SetZxx());
            CurrZ.SetZxy() = convfactor * conj(CurrZ.SetZxy());
            CurrZ.SetZyx() = convfactor * conj(CurrZ.SetZyx());
            CurrZ.SetZyy() = convfactor * conj(CurrZ.SetZyy());
            //std::cout << CurrZ.GetZxy() << " " << CurrZ.GetZyx() << std::endl << std::endl;
            CurrZ.Rotate(-CurrZ.GetRotangle());
            //
            SetMTData().at(i) = CurrZ;
            /*std::copy(effstrike.begin(),effstrike.end(),std::ostream_iterator<double>(std::cout," "));
             std::cout << std::endl;
             std::copy(effcond1.begin(),effcond1.end(),std::ostream_iterator<double>(std::cout," "));
             std::cout << std::endl;
             std::copy(effcond2.begin(),effcond2.end(),std::ostream_iterator<double>(std::cout," "));
             std::cout << std::endl;*/

          }
      }
    public:
      //! Set the anisotropy strike for each layer in degree
      void SetStrikes(const trealdata &a)
        {
          strikes = a;
        }
      //! Set the anisotropy slant for each layer in degree
      void SetSlants(const trealdata &a)
        {
          slants = a;
        }
      //! Set the anisotropy dip for each layer in degree
      void SetDips(const trealdata &a)
        {
          dips = a;
        }
      //! Set the first principal resistivity for each layer in Ohm.m
      void SetRho1(const trealdata &a)
        {
          rho1 = a;
        }
      //! Set the second principal resistivity for each layer in Ohm.m
      void SetRho2(const trealdata &a)
        {
          rho2 = a;
        }
      //! Set the first principal resistivity for each layer in Ohm.m
      void SetRho3(const trealdata &a)
        {
          rho3 = a;
        }
      //! Set the thicknes in km
      void SetThicknesses(const trealdata &thick)
        {
          thicknesses = thick;
        }
      const trealdata &GetThicknesses()
        {
          return thicknesses;
        }
      using MTStation::GetData;
      //! Calculate the synthetic data given the previously set parameters
      virtual void GetData()
      {

        calc_frequencies = GetFrequencies();
        if (calc_frequencies.empty())
          {
            for (int i = 0; i < frequenzen; ++i)
              calc_frequencies.push_back(1.0 / T[i]);
          }
        Assign(calc_frequencies.size());
        TransformRho();
        CalcZ();
        Update();

      }
      //! write model into file
      gplib::rvec GetModelVector()
      {
        TransformRho();
        assert(effcond1.size() == thicknesses.size());
        assert(effcond2.size() == thicknesses.size());
        assert(effstrike.size() == thicknesses.size());
        const unsigned int length = thicknesses.size();
        gplib::rvec result(length * 4);
        for (unsigned int i = 0; i < length; ++i)
          {
            result(i) = log10(1. / effcond1.at(i));
            result(i + length) = thicknesses.at(i);
            result(i + 2 * length) = log10(effcond1.at(i) / effcond2.at(i));
            result(i + 3 * length) = effstrike.at(i) * 180. / PI;
          }
        return result;
      }
      void WriteModel(std::string filename)
      {
        assert(rho1.size() == thicknesses.size());
        assert(rho2.size() == thicknesses.size());
        assert(rho3.size() == thicknesses.size());
        assert(strikes.size() == thicknesses.size());
        assert(slants.size() == thicknesses.size());
        assert(dips.size() == thicknesses.size());
        std::ofstream outfile(filename.c_str());
        if (outfile)
          {
            outfile << thicknesses.size() << std::endl;
            for (unsigned int i = 0; i < thicknesses.size(); ++i)
              {
                outfile << thicknesses.at(i) << "  " << rho1.at(i) << " ";
                outfile << rho2.at(i) << "  " << rho3.at(i) << " ";
                outfile << strikes.at(i) << "  " << slants.at(i) << " ";
                outfile << dips.at(i) << std::endl;
              }
          }
        else
          {
            throw FatalException("Problem writing to file: " + filename);
          }

      }
      void ReadModel(std::string filename)
      {

        int layers;
        double currthick, currho1, currho2, currho3, currstrike, currslant,
            currdip;
        int i = 0;

        std::ifstream infile(filename.c_str());
        infile >> layers;
        if (!infile.good() || layers < 0)
          throw FatalException("Problem reading file: " + filename);
        thicknesses.reserve(layers);
        rho1.reserve(layers);
        rho2.reserve(layers);
        rho3.reserve(layers);
        strikes.reserve(layers);
        slants.reserve(layers);
        dips.reserve(layers);
        while (infile.good())
          {
            infile >> currthick >> currho1 >> currho2 >> currho3 >> currstrike
                >> currslant >> currdip;
            if (infile.good())
              {
                thicknesses.push_back(currthick);
                rho1.push_back(currho1);
                rho2.push_back(currho2);
                rho3.push_back(currho3);
                strikes.push_back(currstrike);
                slants.push_back(currslant);
                dips.push_back(currdip);
                ++i;
              }
          }
        assert(rho1.size() == thicknesses.size());
        assert(rho2.size() == thicknesses.size());
        assert(rho3.size() == thicknesses.size());
        assert(strikes.size() == thicknesses.size());
        assert(slants.size() == thicknesses.size());
        assert(dips.size() == thicknesses.size());
        assert(i==layers);
      }
      void WritePlot(std::string filename)
      {
        std::ofstream outfile(filename.c_str());
        double cumthick = 0;
        TransformRho();
        assert(effcond1.size() == thicknesses.size());
        assert(effcond2.size() == thicknesses.size());
        assert(effstrike.size() == thicknesses.size());
        for (unsigned int i = 0; i < thicknesses.size(); ++i)
          {
            outfile << cumthick << "  " << 1. / effcond1.at(i) << " ";
            outfile << 1. / effcond2.at(i) << "  " << effstrike.at(i) * 180.
                / PI;
            outfile << std::endl;
            cumthick += thicknesses.at(i);
            outfile << cumthick << "  " << 1. / effcond1.at(i) << " ";
            outfile << 1. / effcond2.at(i) << "  " << effstrike.at(i) * 180.
                / PI;
            outfile << std::endl;
          }
      }
      virtual C1DAnisoMTSynthData *clone() const
        {
          return new C1DAnisoMTSynthData(*this);
        }
      C1DAnisoMTSynthData(const C1DAnisoMTSynthData &old):
          MTStation(old), calc_frequencies(old.calc_frequencies), thicknesses(
              old.thicknesses), strikes(old.strikes), slants(old.slants), dips(
              old.dips), rho1(old.rho1), rho2(old.rho2), rho3(old.rho3), effcond1(
              old.effcond1), effcond2(old.effcond2), effstrike(old.effstrike)
          {

          }
      C1DAnisoMTSynthData();
      virtual ~C1DAnisoMTSynthData();
      };
  /* @} */
  }
#endif /*C1DANISOMTSYNTHDATA_H_*/
