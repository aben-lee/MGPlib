#ifndef SEISTOOLS_H_
#define SEISTOOLS_H_

#include <algorithm>
#include <cassert>
#include <boost/bind.hpp>
#include <vector>

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! Calculate density from a given S-velocity, the formula is taken from Owen et al. JGR 89,7783-7795 and modified for vs
    struct CalcDensity
      {
      double operator()(const double svel)
        {
          return (0.77 + 0.554 * svel);
        }
      };
      
    struct CalcAngle1 // we compute cos (2phi) to use formula Vapp = Viso + B*cos(2phi)
        {
        double operator()(const double phi)
          {
            return cos(2.0 * phi *M_PI /180.0);
          }
       };

    struct Pow10 // 10 exp (x)
            {
            double operator()(const double Temp2)
              {
                return pow(10,Temp2);
              }
           };
           
    inline void Normalize(std::vector<double> &Trace)
      {
    	const double maxtrace = *std::max_element(Trace.begin(), Trace.end());
    	assert(std::abs(maxtrace) > 0.0 );
        const double maxamp = 1. / maxtrace;
        std::transform(Trace.begin(), Trace.end(), Trace.begin(), boost::bind(
            std::multiplies<double>(), _1, maxamp));
      }
  /* @} */
  }
#endif /*SEISTOOLS_H_*/
