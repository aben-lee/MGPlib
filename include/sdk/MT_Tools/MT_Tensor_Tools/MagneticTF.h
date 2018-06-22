#ifndef CMAGNETICTF_H_
#define CMAGNETICTF_H_
#include <complex>

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */
    //! Store th local magnetic transfer function (tipper)
    class MagneticTF
      {
    private:
      std::complex<double> Tx;
      std::complex<double> Ty;
      double dTx;
      double dTy;
      double Rz;
      double frequency;
    public:
      std::complex<double> GetTx() const
        {
          return Tx;
        }
      std::complex<double> GetTy() const
        {
          return Ty;
        }
      //! Coherency for the z-direction (Vertical magnetic field)
      double GetRz() const
        {
          return Rz;
        }
      double GetdTx() const
        {
          return dTx;
        }
      double GetdTy() const
        {
          return dTy;
        }
      friend class MTStation;
      MagneticTF(): Tx(0), Ty(0), dTx(0), dTy(0), Rz(0), frequency(0)
      {
      }
      virtual ~MagneticTF()
      {

      }
    };
  /* @} */
  }
#endif /*CMAGNETICTF_H_*/
