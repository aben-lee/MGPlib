#ifndef CRFSPECELEMENT_H_
#define CRFSPECELEMENT_H_
#include <functional>
#include "types.h"

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! This class calculates one spectral element of the receiver function from the two input spectral elements
    /*! The constructor takes the absolute value of the waterlevel, the overloaded operator() takes
     * two complex numbers as arguments to calculate the resulting spectral value of the receiver function
     * and can be used with standard algorithms like transform
     */
    class CalcSpectralElement: public std::binary_function<tcomp, tcomp, tcomp>
      {
    private:
      tcomp DivThreshold;
    public:
      CalcSpectralElement(tcomp t) :
        DivThreshold(t)
        {
        }
      tcomp operator()(const tcomp rad, const tcomp ver) const
        {
          return rad * conj(ver) / std::max(std::abs(ver * conj(ver)), std::abs(
              DivThreshold));
        }
      };
  /* @} */
  }
#endif /*CRFSPECELEMENT_H_*/
