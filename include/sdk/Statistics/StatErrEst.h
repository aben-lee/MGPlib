#ifndef CMTERREST_H_
#define CMTERREST_H_
#include <boost/function.hpp>
#include <vector>

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    //! This class is used as a base for stochastic error estimation
    /*!  This base class is used for stochastic error estimation with Bootstrap, Jacknife or
     * similar methods. It takes a template parameter, the type of the function object
     * that generates individual samples for the analysis. The only requirement is, that
     * operator() returns a value that is convertible to a double.
     */
    template<class SampleGenerator>
    class StatErrEst
      {
    private:
      //! We store the sample generator in a private variable
      SampleGenerator Generator;
      //! Make the desired number of samples using the Generator function object
      void MakeSamples()
        {
          Samples.reserve(nrealizations);
          std::generate_n(back_inserter(Samples), nrealizations, Generator);
        }
      //! This is the only virtual function, it is overwritten by the derived class to implement the error calculation method
      virtual void CalcErrors_Imp(double &m, double &v) = 0;
    protected:
      //! How many samples are requested
      int nrealizations;
      //! the vector that holds the generated samples
      std::vector<double> Samples;
    public:
      //! public access function to generated samples
      std::vector<double> &GetSamples()
        {
          return Samples;
        }
      //! The main function, calculates the error, by generating samples and calling the derived function
      void CalcErrors(double &m, double &v)
        {
          MakeSamples();
          CalcErrors_Imp(m, v);
        }
      //! The constructor takes two parameters, the desired number of samples and the function object to generate them
      StatErrEst(const int nsamples, SampleGenerator TheGenerator) :
        Generator(TheGenerator), nrealizations(nsamples)
        {
        }
      ;
      virtual ~StatErrEst()
        {
        }
      ;
      };
  /* @} */
  }
#endif /*CMTERREST_H_*/
