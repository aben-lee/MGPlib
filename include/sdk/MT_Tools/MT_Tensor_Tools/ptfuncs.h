#ifndef PTFUNCS_H_
#define PTFUNCS_H_

#include <cmath>

namespace gplib
  {
    /*! /file
     * This header file provides some function to calculate phase tensor quantities that are used in MTTensor and PTensorMTData
     */


    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! return the phase tensor rotation angle as a function of the four phase tensor elements
    double inline Alpha_phi(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return 0.5 * atan2(phi12 + phi21, phi11 - phi22);
      }
    //! return the phase tensor skew angle as a function of the four phase tensor elements
    double inline Beta_phi(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return 0.5 * atan2(phi12 - phi21, phi11 + phi22);
      }
    //! return the phase tensor rotational invariant \f$ \Pi_1 \f$ as a function of the four phase tensor elements
    double inline Pi1(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return 0.5 * sqrt(std::pow(phi11 - phi22, 2) + std::pow(phi12 + phi21, 2));
      }
    //! return the phase tensor rotational invariant \f$ \Pi_2 \f$ as a function of the four phase tensor elements
    double inline Pi2(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return 0.5 * sqrt(std::pow(phi11 + phi22, 2) + std::pow(phi12 - phi21, 2));
      }
    //! return the phase tensor strike angle as a function of the four phase tensor elements
    double inline PhiStrike(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return Alpha_phi(phi11, phi12, phi21, phi22) - Beta_phi(phi11, phi12,
            phi21, phi22);
      }
    //! Return the maximum principal component of the phase tensor
    double inline PhiMax(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return Pi2(phi11, phi12, phi21, phi22)
            + Pi1(phi11, phi12, phi21, phi22);
      }
    //! Return the mimum principal component of the phase tensor
    double inline PhiMin(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return Pi2(phi11, phi12, phi21, phi22)
            - Pi1(phi11, phi12, phi21, phi22);
      }
    //! Return the trace of the phase tensor
    double inline trPhi(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return phi11 + phi22;
      }
    //! Return the skew of the phase tensor
    double inline skPhi(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return phi12 - phi21;
      }
    //! Return the determinant of the phase tensor
    double inline detPhi(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return phi11 * phi22 - phi12 * phi21;
      }

    double inline Phi1(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return trPhi(phi11, phi12, phi21, phi22) / 2.;
      }

    double inline Phi2(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return sqrt(std::abs(detPhi(phi11, phi12, phi21, phi22)));
      }

    double inline GetPhi2Sq(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return detPhi(phi11, phi12, phi21, phi22);
      }

    double inline GetPhi3(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return skPhi(phi11, phi12, phi21, phi22) / 2.;
      }
    //! Return the ellipticity of the phase tensor
    double inline GetPhiEllip(const double phi11, const double phi12,
        const double phi21, const double phi22)
      {
        return (PhiMax(phi11, phi12, phi21, phi22) - PhiMin(phi11, phi12,
            phi21, phi22)) / (PhiMax(phi11, phi12, phi21, phi22) + PhiMin(
            phi11, phi12, phi21, phi22));
      }
  /* @} */
  }
#endif /*PTFUNCS_H_*/
