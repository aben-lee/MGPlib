#ifndef CUNIFORMRNG_H
#define CUNIFORMRNG_H

#include "GeneralRNG.h"
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/uniform_01.hpp>
#include <ctime>
#include <boost/cast.hpp>
using namespace std;

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! Generate uniformly distributed random numbers, this is basically a wrapper for the boost random number generators, that is a little easier to use
    /*! During the GA inversion we need a lot of uniformly distributed random numbers,
     * some between 0 and 1, some between a specified minimum and maximum.
     * This class provides a simple and consistent interface to the high quality
     * boost random number generator.
     *
     */
    class UniformRNG: public GeneralRNG
      {
    private:
      boost::lagged_fibonacci607 generator;
      boost::uniform_01<boost::lagged_fibonacci607> real_dist;
    public:
      //! Return a random float between low and high
      float GetNumber(const float low, const float high)
      {
        //return float between low and high
        return low + (high - low) * GetNumber();
      }
      //! Returns a random float between 0 and 1
      virtual float GetNumber()
      {
        //just forward the call to the boost random number generator
        return real_dist();
      }
      //! Return a random integer between 0 and max-1
      virtual unsigned int GetNumber(const unsigned int max)
      {
        //make an unsigned integer from the random float
        return (boost::numeric_cast<unsigned int>(max * real_dist()));
      }
      UniformRNG() :
          generator(static_cast<unsigned int> (std::time(NULL))), real_dist(
              generator)
          {

          }

      virtual ~UniformRNG();
      };
  /* @} */
  }
#endif // CUNIFORMRNG_H
