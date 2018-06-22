#ifndef CGENERALRNG_H
#define CGENERALRNG_H
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! The base class for all random number generators, defines the basic interface
    class GeneralRNG
      {
    public:
      virtual float GetNumber() = 0;
      virtual unsigned int GetNumber(const unsigned int max) = 0;
      GeneralRNG();
      virtual ~GeneralRNG();
      };
  /* @} */
  }
#endif // CGENERALRNG_H
