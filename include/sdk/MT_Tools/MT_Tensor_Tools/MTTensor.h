#ifndef CMTTENSOR_H_
#define CMTTENSOR_H_
#include <complex>
#include "NumUtil.h"
#include "miscfunc.h"

namespace gplib
  {
  /** \addtogroup mttools MT data analysis, processing and inversion */
  /* @{ */
    //! Stores MT-Tensor components at a single frequency, calculates derived quantities
    /*! This class stores the elements of the MT impedance tensor together with their
     * error estimates and rotation angle. Impedances are stored in field units, i.e. km/s
     * and the rotation angle in radian.
     */
    class MTTensor
      {
    private:
      //the impedance elements
      std::complex<double> Zxx;
      std::complex<double> Zxy;
      std::complex<double> Zyx;
      std::complex<double> Zyy;
      //and their errors
      double dZxx;
      double dZxy;
      double dZyx;
      double dZyy;
      double frequency;
      double rotangle;
      //! Coherency for the x direction
      double Rx;
      //! Coherency for the y direction
      double Ry;
      //! Number of degrees of freedom
      double Nu;
      //! Calculate apparent resistivity
      double CalcRho(const std::complex<double> &Z) const
        {
          return mu / (2 * PI * frequency) * (Z.real() * Z.real() + Z.imag()
              * Z.imag()) * 1000000.0;
        }
      //! Calculate Phase
      double CalcPhase(const std::complex<double> &Z) const
        {
          if (fcmp(Z.real(), 0.0, std::numeric_limits<double>::epsilon()) != 0) //if real part significantly different from 0.
            return atan2(Z.imag(), Z.real()) / PI * 180;
          else
            return 0.0;
        }
      //! Calculate Phase restricted to 0 to 90 degree range
      double CalcPhase90(const std::complex<double> &Z) const
        {
          if (fcmp(Z.real(), 0.0, std::numeric_limits<double>::epsilon()) != 0) //if real part significantly different from 0.
            return atan(Z.imag() / Z.real()) / PI * 180; // here we use atan instead of atan2
          else
            return 0.0;
        }
      //! Calculate Apparent Resistivity Error
      double CalcdRho(const std::complex<double> &Z, const double dZ) const
        {
          return mu / (PI * frequency) * std::abs(Z) * dZ * 1000000.0;
        }
      //! Calculate Phase Error
      double CalcdPhase(const std::complex<double> &Z, const double dZ) const
        {
          if (fcmp(std::abs(Z), 0.0, std::numeric_limits<double>::epsilon()) != 0) //if Z significantly different from 0.
            return dZ / std::abs(Z) / PI * 180;
          else
            return 0.0;
        }
      //! Calculate Schmucker's Z*
      double CalcZStar(const std::complex<double> &Z) const
        {
          return std::abs((I / (2.0 * PI * frequency) * Z * 1000.0).real());
        }
      //! Calculate Schmucker's Rho*
      double CalcRhoStar(const std::complex<double> &Z) const
        {
          double phase = CalcPhase(Z) / 180.0 * PI;
          if (phase > 45.0)
            return 2.0 * pow2(cos(phase)) * CalcRho(Z);
          else
            return 0.5 * 1. / pow2(sin(phase)) * CalcRho(Z);
        }
    public:
      //! Function for Errors that cannot be calculated analytically when we don't want Jacknife errors
      double GetdZero() const
        {
          return 0.0;
        }
      //! Set the errors for the impedance elements
      void SetErrors(double dxx, double dxy, double dyx, double dyy)
        {
          dZxx = dxx;
          dZxy = dxy;
          dZyx = dyx;
          dZyy = dyy;
        }
      //!Rotate by the given angle in radian
      void Rotate(double angle)
      {
        dcomp newxx, newxy, newyx, newyy;
        const double ca2 = pow(cos(angle), 2);
        const double sa2 = pow(sin(angle), 2);
        const double casa = sin(angle) * cos(angle);
        newxx = Zxx * ca2 - (Zxy + Zyx) * casa + Zyy * sa2;
        newxy = Zxy * ca2 + (Zxx - Zyy) * casa - Zyx * sa2;
        newyx = Zyx * ca2 + (Zxx - Zyy) * casa - Zxy * sa2;
        newyy = Zyy * ca2 + (Zxy + Zyx) * casa + Zxx * sa2;
        Zxx = newxx;
        Zxy = newxy;
        Zyx = newyx;
        Zyy = newyy;
        rotangle += angle;
      }
      ///!return the current angle in radian
      double GetRotangle() const
        {
          return rotangle;
        }
      //! Set the rotation angle, without performing the corresponding rotation
      double &SetRotangle()
        {
          return rotangle;
        }
      //! Get the frequency for the impedance
      double GetFrequency() const
        {
          return frequency;
        }
      //! Return tensor elements
      std::complex<double> GetZyy() const
        {
          return Zyy;
        }
      std::complex<double> GetZxx() const
        {
          return Zxx;
        }
      std::complex<double> GetZxy() const
        {
          return Zxy;
        }
      std::complex<double> GetZyx() const
        {
          return Zyx;
        }
      //! Write access to tensor elements
      std::complex<double> &SetZyy()
        {
          return Zyy;
        }
      std::complex<double> &SetZxx()
        {
          return Zxx;
        }
      std::complex<double> &SetZxy()
        {
          return Zxy;
        }
      std::complex<double> &SetZyx()
        {
          return Zyx;
        }
      //! Return tensor element errors
      double GetdZxx() const
        {
          return dZxx;
        }
      double GetdZxy() const
        {
          return dZxy;
        }
      double GetdZyx() const
        {
          return dZyx;
        }
      double GetdZyy() const
        {
          return dZyy;
        }
      //! Write access to errors
      double &SetdZyy()
        {
          return dZyy;
        }
      double &SetdZxx()
        {
          return dZxx;
        }
      double &SetdZxy()
        {
          return dZxy;
        }
      double &SetdZyx()
        {
          return dZyx;
        }
      //! Return apparent resistivity
      double GetRhoxx() const
        {
          return CalcRho(Zxx);
        }
      double GetRhoxy() const
        {
          return CalcRho(Zxy);
        }
      double GetRhoyx() const
        {
          return CalcRho(Zyx);
        }
      double GetRhoyy() const
        {
          return CalcRho(Zyy);
        }
      //! Return phase
      double GetPhixx() const
        {
          return CalcPhase(Zxx);
        }
      double GetPhixy() const
        {
          return CalcPhase(Zxy);
        }
      double GetPhiyx() const
        {
          return CalcPhase(Zyx);
        }
      double GetPhiyy() const
        {
          return CalcPhase(Zyy);
        }
      //! Return phase restricted to 0 to 90 degree range
      double GetPhi90xx() const
        {
          return CalcPhase90(Zxx);
        }
      double GetPhi90xy() const
        {
          return CalcPhase90(Zxy);
        }
      double GetPhi90yx() const
        {
          return CalcPhase90(Zyx);
        }
      double GetPhi90yy() const
        {
          return CalcPhase90(Zyy);
        }
      //! Return Rho Error for tensor elements
      double GetdRhoxx() const
        {
          return CalcdRho(Zxx, dZxx);
        }
      double GetdRhoxy() const
        {
          return CalcdRho(Zxy, dZxy);
        }
      double GetdRhoyx() const
        {
          return CalcdRho(Zyx, dZyx);
        }
      double GetdRhoyy() const
        {
          return CalcdRho(Zyy, dZyy);
        }
      //! return phase error for tensor elements
      double GetdPhixx() const
        {
          return CalcdPhase(Zxx, dZxx);
        }
      double GetdPhixy() const
        {
          return CalcdPhase(Zxy, dZxy);
        }
      double GetdPhiyx() const
        {
          return CalcdPhase(Zyx, dZyx);
        }
      double GetdPhiyy() const
        {
          return CalcdPhase(Zyy, dZyy);
        }
      //! Return Schmucker's rho* for tensor elements
      double GetRhoxxStar() const
        {
          return CalcRhoStar(Zxx);
        }
      double GetRhoxyStar() const
        {
          return CalcRhoStar(Zxy);
        }
      double GetRhoyxStar() const
        {
          return CalcRhoStar(Zyx);
        }
      double GetRhoyyStar() const
        {
          return CalcRhoStar(Zyy);
        }
      //! Return Schmucker's z* for tensor elements
      double GetZxxStar() const
        {
          return CalcZStar(Zxx);
        }
      double GetZxyStar() const
        {
          return CalcZStar(Zxy);
        }
      double GetZyxStar() const
        {
          return CalcZStar(Zyx);
        }
      double GetZyyStar() const
        {
          return CalcZStar(Zyy);
        }
      //! Some invariants and intermediate quantities for strike and skew calculation
      std::complex<double> GetS1() const
        {
          return Zxx + Zyy;
        }
      std::complex<double> GetS2() const
        {
          return Zxy + Zyx;
        }
      std::complex<double> GetD1() const
        {
          return Zxx - Zyy;
        }
      std::complex<double> GetD2() const
        {
          return Zxy - Zyx;
        }
      //! The Berdichevskyi invariant
      std::complex<double> GetBerd() const
        {
          return 0.5 * GetD2();
        }
      //! The error of the Berdichevskyi invariant
      double GetdBerd() const
        {
          return 0.5 * sqrt(dZxy * dZxy + dZyx * dZyx);
        }
      double GetRhoBerd() const
        {
          return CalcRho(GetBerd());
        }
      double GetPhi90Berd() const
        {
          return CalcPhase90(GetBerd());
        }
      double GetdRhoBerd() const
        {
          return CalcdRho(GetBerd(), GetdBerd());
        }
      double GetdPhi90Berd() const
        {
          return CalcdPhase(GetBerd(), GetdBerd());
        }
      //! The determinant
      std::complex<double> GetDet() const
        {
          return Zxx * Zyy - Zxy * Zyx;
        }
      //! The error of the determinant
      double GetdDet() const
        {
          return sqrt(abs(Zyy * Zyy) * dZxx * dZxx + abs(Zxx * Zxx) * dZyy
              * dZyy + abs(Zxy * Zxy) * dZyx * dZyx + abs(Zyx * Zyx) * dZxy
              * dZxy);
        }
      //! The determinant of the real parts of Z
      double GetDetreal() const
        {
          return Zxx.real() * Zyy.real() - Zxy.real() * Zyx.real();
        }
      //! Get the error of the determinant of the real part
      double GetdDetreal() const
        {
          return sqrt(pow2(Zyy.real()) * pow2(dZxx) + pow2(Zxx.real()) * pow2(
              dZyy) + pow2(Zxy.real()) * pow2(dZyx) + pow2(Zyx.real()) * pow2(
              dZxy));
        }
      //! Rotationally invariant phase difference
      double GetMu() const
        {
          return sqrt(std::abs(Commute(GetD1(), GetS2()) + Commute(GetS1(),
              GetD2()))) / abs(GetD2());
        }
      //! Swift's skew
      double GetKappa() const
        {
          return abs(GetS1()) / abs(GetD2());
        }
      double GetSigma() const
        {
          return (pow2(abs(GetD1())) + pow2(abs(GetS2()))) / pow2(abs(GetD2()));
        }
      //! Bahr's skew
      double GetEta() const
        {
          return sqrt(std::abs(Commute(GetD1(), GetS2()) - Commute(GetS1(),
              GetD2()))) / abs(GetD2());
        }
      //Bahr's phase sensitive strike angle
      double GetAlpha() const
        {
          double denominator = Commute(GetS1(), GetD1()) - Commute(GetS2(),
              GetD2());
          if (fcmp(denominator, 0.0, std::numeric_limits<double>::epsilon())
              != 0)
            return 0.5 * atan((Commute(GetS1(), GetS2()) - Commute(GetD1(),
                GetD2())) / (denominator));
          else
            return 0.0;
        }
      //! Calculate strike angle, so it points to high conductivity direction (Phixy > Phiyx)
      double GetAlphaHigh() const
        {
          double regalpha = GetAlpha(); // calculate strike angle
          MTTensor tmp(*this); //create local copy
          tmp.Rotate(regalpha); //rotate to new coordinate system
          if (tmp.GetPhiyx() > tmp.GetPhixy())
            regalpha += PI / 2.0;
          return regalpha;
        }
      //! Maximum phase difference
      double GetMaxPhiDiff() const
        {
          MTTensor tmp(*this); //create local copy
          tmp.Rotate(GetAlpha());
          return std::abs(tmp.GetPhixy() - tmp.GetPhiyx());
        }
      //! All the following quantities are defined in Caldwell GJI 158, 457-469, the phase tensor elements
      double GetPhi11() const
        {
          const double dr = GetDetreal();
          if (fcmp(dr, 0.0, std::numeric_limits<double>::epsilon()) != 0)
            return ((Zyy.real() * Zxx.imag() - Zxy.real() * Zyx.imag()) / dr);
          else
            return 0.0;
        }
      double GetPhi12() const
        {
          const double dr = GetDetreal();
          if (fcmp(dr, 0.0, std::numeric_limits<double>::epsilon()) != 0)
            return ((Zyy.real() * Zxy.imag() - Zxy.real() * Zyy.imag()) / dr);
          else
            return 0.0;
        }
      double GetPhi21() const
        {
          const double dr = GetDetreal();
          if (fcmp(dr, 0.0, std::numeric_limits<double>::epsilon()) != 0)
            return ((Zxx.real() * Zyx.imag() - Zyx.real() * Zxx.imag()) / dr);
          else
            return 0.0;
        }
      double GetPhi22() const
        {
          const double dr = GetDetreal();
          if (fcmp(dr, 0.0, std::numeric_limits<double>::epsilon()) != 0)
            return ((Zxx.real() * Zyy.imag() - Zyx.real() * Zxy.imag()) / dr);
          else
            return 0.0;
        }
      double GetAlpha_phi() const
        {
          const double diff = GetPhi11() - GetPhi22();
          if (fcmp(diff, 0.0, std::numeric_limits<double>::epsilon()) != 0)
            return 0.5 * atan2((GetPhi12() + GetPhi21()), diff);
          else
            return 0.0;
        }
      double GetBeta_phi() const
        {
          return 0.5 * atan2((GetPhi12() - GetPhi21()), (GetPhi11()
              + GetPhi22()));
        }
      double GetPi1() const
        {
          return 0.5 * sqrt(std::pow(GetPhi11() - GetPhi22(), 2) + std::pow(
              GetPhi12() + GetPhi21(), 2));
        }
      double GetPi2() const
        {
          return 0.5 * sqrt(std::pow(GetPhi11() + GetPhi22(), 2) + std::pow(
              GetPhi12() - GetPhi21(), 2));
        }
      double GetPhiStrike() const
        {
          return GetAlpha_phi() - GetBeta_phi();
        }
      double GetPhiMax() const
        {
          return GetPi2() + GetPi1();
        }
      double GetPhiMin() const
        {
          return GetPi2() - GetPi1();
        }
      double GettrPhi() const
        {
          return GetPhi11() + GetPhi22();
        }
      double GetskPhi() const
        {
          return GetPhi12() - GetPhi21();
        }
      double GetdetPhi() const
        {
          return GetPhi11() * GetPhi22() - GetPhi12() * GetPhi21();
        }
      double GetPhi1() const
        {
          return GettrPhi() / 2.;
        }
      double GetPhi2() const
        {
          return sqrt(std::abs(GetdetPhi()));
        }
      double GetPhi2Sq() const
        {
          return GetdetPhi();
        }
      double GetPhi3() const
        {
          return GetskPhi() / 2.;
        }
      double GetPhiEllip() const
        {
          return (GetPhiMax() - GetPhiMin()) / (GetPhiMax() + GetPhiMin());
        }
      //Here start the Weaver et al. invariants, equations taken from Marti, GJI 2004
      double GetXi1() const
        {
          return 0.5 * (Zxx.real() + Zyy.real());
        }
      double GetXi2() const
        {
          return 0.5 * (Zxy.real() + Zyx.real());
        }
      double GetXi3() const
        {
          return 0.5 * (Zxx.real() - Zyy.real());
        }
      double GetXi4() const
        {
          return 0.5 * (Zxy.real() - Zyx.real());
        }
      double GetEta1() const
        {
          return 0.5 * (Zxx.imag() + Zyy.imag());
        }
      double GetEta2() const
        {
          return 0.5 * (Zxy.imag() + Zyx.imag());
        }
      double GetEta3() const
        {
          return 0.5 * (Zxx.imag() - Zyy.imag());
        }
      double GetEta4() const
        {
          return 0.5 * (Zxy.imag() - Zyx.imag());
        }
      double GetI1() const
        {
          return sqrt(pow2(GetXi1()) + pow2(GetXi4()));
        }
      double GetI2() const
        {
          return sqrt(pow2(GetEta1()) + pow2(GetEta4()));
        }
      double GetI3() const
        {
          return sqrt(pow2(GetXi2()) + pow2(GetXi3())) / GetI1();
        }
      double GetI4() const
        {
          return sqrt(pow2(GetEta2()) + pow2(GetEta3())) / GetI2();
        }
      double GetI5() const
        {
          return (GetXi4() * GetEta1() + GetXi1() * GetEta4()) / (GetI1()
              * GetI2());
        }
      double GetI6() const
        {
          return (GetXi4() * GetEta1() - GetXi1() * GetEta4()) / (GetI1()
              * GetI2());
        }
      double Getd13() const
        {
          return (GetXi1() * GetEta3() - GetXi3() * GetEta1()) / (GetI1()
              * GetI2());
        }
      double Getd12() const
        {
          return (GetXi1() * GetEta2() - GetXi2() * GetEta1()) / (GetI1()
              * GetI2());
        }
      double Getd24() const
        {
          return (GetXi2() * GetEta4() - GetXi4() * GetEta2()) / (GetI1()
              * GetI2());
        }
      double Getd34() const
        {
          return (GetXi3() * GetEta4() - GetXi4() * GetEta3()) / (GetI1()
              * GetI2());
        }
      double Getd41() const
        {
          return (GetXi4() * GetEta1() - GetXi1() * GetEta4()) / (GetI1()
              * GetI2());
        }
      double Getd23() const
        {
          return (GetXi2() * GetEta3() - GetXi3() * GetEta2()) / (GetI1()
              * GetI2());
        }
      double GetQ() const
        {
          return sqrt(pow2(Getd12() - Getd34()) + pow2(Getd13() + Getd24()));
        }
      double GetI7() const
        {
          return (Getd41() + Getd23()) / GetQ();
        }
      double Geta() const
        {
          return pow2(GetI5() - GetI6());
        }
      double Getb() const
        {
          return 1.0 - GetI5() * GetI6() + sqrt(1.0 + pow2(GetI5()) * pow2(
              GetI6()) - pow2(GetI5()) - pow2(GetI6()));
        }
      double Getr() const
        {
          return GetI2() / GetI1();
        }
      //const std::complex<double> GetThetaBar(){}
      //const std::complex<double> GetdTheta(){}
      //const std::complex<double> GetZs(){}
      //const std::complex<double> GetZp(){}
      //! Return coherency for the x-direction
      double GetRx() const
        {
          return Rx;
        }
      //! Return coherency for the y-direction
      double GetRy() const
        {
          return Ry;
        }
      //! The degrees of freedom used for transfer function estimation
      double GetNu() const
        {
          return Nu;
        }
      friend class MTStation;
      friend class C1DMTSynthData;
      friend class JParser;
      friend class EDIParser;
      MTTensor():
          Zxx(0), Zxy(0), Zyx(0), Zyy(0), dZxx(0), dZxy(0), dZyx(0), dZyy(0), frequency(0),
          rotangle(0), Rx(0), Ry(0), Nu(0)
        {
        }

      MTTensor(const std::complex<double> &xx, const std::complex<double> &xy,
          const std::complex<double> &yx, const std::complex<double> &yy,
          const double freq = 1., const double angle = 0.0):
          Zxx(xx), Zxy(xy), Zyx(yx), Zyy(yy), dZxx(0), dZxy(0), dZyx(0), dZyy(0), frequency(
              freq), rotangle(angle), Rx(0), Ry(0), Nu(0)
        {
        }
      MTTensor& operator=(const MTTensor& source)
      {
        if (this == &source)
          return *this;
        Zxx = source.Zxx;
        Zxy = source.Zxy;
        Zyx = source.Zyx;
        Zyy = source.Zyy;
        dZxx = source.dZxx;
        dZxy = source.dZxy;
        dZyx = source.dZyx;
        dZyy = source.dZyy;
        frequency = source.frequency;
        rotangle = source.rotangle;
        Rx = source.Rx;
        Ry = source.Ry;
        Nu = source.Nu;
        return *this;
      }

      virtual ~MTTensor()
      {

      }
    };
    /* @} */
    std::complex<double> inline RhoPhiToZ(const double freq, const double rho,
        const double phi)
      {
        return sqrt(2 * PI * freq / mu) * 0.001 * sqrt(rho) * (cos(phi / 180
            * PI) + I * sin(phi / 180 * PI));
      }

  // This is some remnant code for parallel and serial transforms of the impedance tensor
  // only kept so I remember how they are calculated
  /*	temp1 = gsl_complex_rect(D1.at(i).real(),D1.at(i).imag());
   temp2 = gsl_complex_rect(S2.at(i).real(),S2.at(i).imag());
   temp3= gsl_complex_mul_real(gsl_complex_arctan(gsl_complex_div(gsl_complex_mul_real(temp1,-1.),temp2)),0.5);
   thetabar.at(i) = GSL_REAL(temp3);
   thetabar.at(i) += I*GSL_IMAG(temp3);
   temp1 = gsl_complex_rect(S1.at(i).real(),S1.at(i).imag());
   temp2 = gsl_complex_rect(D2.at(i).real(),D2.at(i).imag());
   temp3 = gsl_complex_arctan(gsl_complex_div(temp1,temp2));
   dtheta.at(i) = GSL_REAL(temp3);
   dtheta.at(i) += I*GSL_IMAG(temp3);
   //dtheta.at(i) = atan(S1.at(i)/D2.at(i))
   Zs.at(i) = sqrt((pow(DataXX.Z.at(i),2) + pow(DataXY.Z.at(i),2) + pow(DataYX.Z.at(i),2) + pow(DataYY.Z.at(i),2))/2.);
   Zp.at(i) = (DataXY.Z.at(i)*DataYX.Z.at(i)-DataXX.Z.at(i)*DataYY.Z.at(i))/Zs.at(i);
   rhos.at(i) = 1/(2 * PI * frequency.at(i)) * mu * (pow(Zs.at(i).real(),2)+pow(Zs.at(i).imag(),2)) * pow(1000.0,2);
   rhop.at(i) = 1/(2 * PI * frequency.at(i)) * mu * (pow(Zp.at(i).real(),2)+pow(Zp.at(i).imag(),2)) * pow(1000.0,2);
   phis.at(i) = atan(Zs.at(i).imag()/Zs.at(i).real());
   phip.at(i) = atan(Zp.at(i).imag()/Zp.at(i).real());
   dPhips.at(i) = phip.at(i) - phis.at(i);*/
  }

#endif /*CMTTENSOR_H_*/
