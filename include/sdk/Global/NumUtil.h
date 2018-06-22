//============================================================================
// Name        : NumUtil.h
// Author      : Nov 3, 2009
// Version     : 
// Copyright   : 2009, mmoorkamp
//============================================================================


#ifndef NUMUTIL_H_
#define NUMUTIL_H_
#include<math.h>

namespace gplib
  {
  /** \addtogroup genfunc General functions from various areas */
  /* @{ */
    //! Calculate the square of a value by multiplication instead of the pow function
    template<typename NumericType> NumericType pow2(const NumericType Value)
      {
        return Value * Value;
      }
    //! Floating point comparison with tolerance epsilon, this is the implementation from the GNU Scientific library
    int fcmp (const double x1, const double x2, const double epsilon)
    {
        if (abs(x1 - x2) < epsilon)
            return 1;
        else
            return 0;
    }

    /* @} */
  }

#endif /* NUMUTIL_H_ */
