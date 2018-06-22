#ifndef MTFUNCS_H_
#define MTFUNCS_H_
#include <complex>
#include "miscfunc.h"

namespace gplib
  {
    //double CalcRhoa(const  MTTensor &Z){
    //return 1./(2 * PI * Z.frequency) * mu * (pow(Z.real(),2)+pow(Z.at(k).imag(),2)) * pow(1000.0,2);
    //}
    class MTTensor;
    double CalcPhi(const std::complex<double> &Z)
      {
        return atan(Z.imag() / Z.real()) / PI * 180;
      }

    std::complex<double> CalcS1(const MTTensor &Z)
      {
        return Z.GetZxx() + Z.GetZyy();
      }
  /*


   S1.at(i) = DataXX.Z.at(i) + DataYY.Z.at(i);
   S2.at(i) = DataXY.Z.at(i) + DataYX.Z.at(i);
   D1.at(i) = DataXX.Z.at(i) - DataYY.Z.at(i);
   D2.at(i) = DataXY.Z.at(i) - DataYX.Z.at(i);
   Berd.at(i) = 0.5 * D2.at(i);
   dBerd.at(i) = sqrt(0.5*pow(DataXY.dZ.at(i),2)+pow(DataYX.dZ.at(i),2));
   alpha.at(i) = 0.5 * atan((Commute(S1.at(i),S2.at(i))-Commute(D1.at(i),D2.at(i)))/(Commute(S1.at(i),D1.at(i))-Commute(S2.at(i),D2.at(i))));
   eta.at(i)   = sqrt(abs(Commute(D1.at(i),S2.at(i))-Commute(S1.at(i),D2.at(i))))/abs(D2.at(i));
   det = DataXX.Z.at(i).real() * DataYY.Z.at(i).real() - DataXY.Z.at(i).real() * DataYX.Z.at(i).real();
   detreal.at(i) = det;
   Phi11.at(i) = (DataYY.Z.at(i).real() * DataXX.Z.at(i).imag() - DataXY.Z.at(i).real() * DataYX.Z.at(i).imag())/det;
   Phi12.at(i) = (DataYY.Z.at(i).real() * DataXY.Z.at(i).imag() - DataXY.Z.at(i).real() * DataYY.Z.at(i).imag())/det;
   Phi21.at(i) =  (DataXX.Z.at(i).real() * DataYX.Z.at(i).imag() - DataYX.Z.at(i).real() * DataXX.Z.at(i).imag())/det;
   Phi22.at(i) = (DataXX.Z.at(i).real() * DataYY.Z.at(i).imag() - DataYX.Z.at(i).real() * DataXY.Z.at(i).imag())/det;
   alpha_phi.at(i) = 0.5 * atan((Phi12.at(i) + Phi21.at(i))/(Phi11.at(i) - Phi22.at(i)));
   beta_phi.at(i) = 0.5 * atan((Phi12.at(i) - Phi21.at(i))/(Phi11.at(i) + Phi22.at(i)));
   trPhi.at(i) = (Phi11.at(i) + Phi22.at(i));
   skPhi.at(i) = Phi12.at(i) - Phi21.at(i);
   detPhi.at(i) = Phi11.at(i) * Phi22.at(i) - Phi12.at(i) * Phi21.at(i);
   Phi1.at(i) = trPhi.at(i) / 2.;
   Phi2.at(i) = sqrt(detPhi.at(i));
   Phi3.at(i) = skPhi.at(i) / 2.;
   Phimax.at(i) = sqrt( pow(Phi1.at(i),2) + pow(Phi3.at(i),2)) + sqrt(pow(Phi1.at(i),2)+pow(Phi3.at(i),2) - pow(Phi2.at(i),2));
   Phimin.at(i) = sqrt( pow(Phi1.at(i),2) + pow(Phi3.at(i),2)) - sqrt(pow(Phi1.at(i),2)+pow(Phi3.at(i),2) - pow(Phi2.at(i),2));
   PhiEllip.at(i) = (Phimax.at(i)- Phimin.at(i))/ (Phimax.at(i)+Phimin.at(i));
   temp1 = gsl_complex_rect(D1.at(i).real(),D1.at(i).imag());
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
   dPhips.at(i) = phip.at(i) - phis.at(i);
   */
  }
#endif /*MTFUNCS_H_*/
