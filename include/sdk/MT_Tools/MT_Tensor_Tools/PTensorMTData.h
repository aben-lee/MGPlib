#ifndef PTENSORMTDATA_H_
#define PTENSORMTDATA_H_

#include "ptfuncs.h"

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! This class is for the special case where we only have phase tensor data and errors, but not the full impedance
    class PTensorMTData
      {
    private:
      double phi11;
      double phi12;
      double phi21;
      double phi22;
      double dphi11;
      double dphi12;
      double dphi21;
      double dphi22;
      double frequency;
    public:
      double GetPhi11() const
        {
          return phi11;
        }
      void SetPhi11(const double p)
        {
          phi11 = p;
        }
      double GetPhi12() const
        {
          return phi12;
        }
      void SetPhi12(const double p)
        {
          phi12 = p;
        }
      double GetPhi21() const
        {
          return phi21;
        }
      void SetPhi21(const double p)
        {
          phi21 = p;
        }
      double GetPhi22() const
        {
          return phi22;
        }
      void SetPhi22(const double p)
        {
          phi22 = p;
        }
      double GetdPhi11() const
        {
          return dphi11;
        }
      void SetdPhi11(const double p)
        {
          dphi11 = p;
        }
      double GetdPhi12() const
        {
          return dphi12;
        }
      void SetdPhi12(const double p)
        {
          dphi12 = p;
        }
      double GetdPhi21() const
        {
          return dphi21;
        }
      void SetdPhi21(const double p)
        {
          dphi21 = p;
        }
      double GetdPhi22() const
        {
          return dphi22;
        }
      void SetdPhi22(const double p)
        {
          dphi22 = p;
        }
      double GetFrequency() const
        {
          return frequency;
        }
      void SetFrequency(const double f)
        {
          frequency = f;
        }
      PTensorMTData(const double f, const double p11, const double p12,
          const double p21, const double p22, const double dp11,
          const double dp12, const double dp21, const double dp22):
          phi11(p11), phi12(p12), phi21(p21), phi22(p22), dphi11(dp11),
              dphi12(dp12), dphi21(dp21), dphi22(dp22), frequency(f)
          {

          }
      PTensorMTData():
          phi11(0.0), phi12(0.0), phi21(0.0), phi22(0.0), dphi11(0.0), dphi12(0.0),
              dphi21(0.0), dphi22(0.0), frequency(0.0)
          {
          }
      virtual ~PTensorMTData();
      };
  /* @} */
  }
#endif /*PTENSORMTDATA_H_*/
