#ifndef MTSAMPLEGENERATOR_H_
#define MTSAMPLEGENERATOR_H_
#include <boost/function.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <complex>
#include "MTTensor.h"
#include <algorithm>
#include <ctime>

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */

    //! Generate random elements of a calculated quantity for MT impedance data
    /*! This class is used for error analysis of MT data using the Bootstrap or Jacknife method.
     * The constructor takes a pointer to a member function of MTTensor f, a Tensor element Z and an errorlevel
     * and generates random  samples f(Z) within the errorlevel for the impedance.
     * Each call to operator() yields a new sample
     */
    class MTSampleGenerator
      {
    private:
      boost::lagged_fibonacci607 generator;
      boost::normal_distribution<> Zxxr_dist;
      boost::normal_distribution<> Zxxi_dist;
      boost::normal_distribution<> Zxyr_dist;
      boost::normal_distribution<> Zxyi_dist;
      boost::normal_distribution<> Zyxr_dist;
      boost::normal_distribution<> Zyxi_dist;
      boost::normal_distribution<> Zyyr_dist;
      boost::normal_distribution<> Zyyi_dist;

      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zxxr;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zxxi;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zxyr;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zxyi;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zyxr;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zyxi;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zyyr;
      boost::variate_generator<boost::lagged_fibonacci607&,
          boost::normal_distribution<> > Zyyi;
      boost::function<double(const MTTensor*)> func;
      MTTensor Data;
    public:
      //! The constructor needs a pointer to a member function of MTTensor that returns a double, an impedance element and an errolevel for all elements
      /*! For example MTSampleGenerator(&MTTensor::GetRhoxy,DistData) creates a distribution of Zxy apparent resistivity
       * values that is purely based on the impedance errors in DistData, if an errorlevel was specified this
       * would be the error floor.*/
      MTSampleGenerator(boost::function<double(const MTTensor*)> f,
          const MTTensor &Z, const double errorlevel = 0.0):
          generator(static_cast<unsigned int> (std::time(0))), Zxxr_dist(
              Z.GetZxx().real(), max(Z.GetdZxx(), Z.GetZxx().real() * errorlevel)),
              Zxxi_dist(Z.GetZxx().imag(), max(Z.GetdZxx(), Z.GetZxx().imag()
                  * errorlevel)), Zxyr_dist(Z.GetZxy().real(), max(Z.GetdZxy(),
                  Z.GetZxy().real() * errorlevel)), Zxyi_dist(Z.GetZxy().imag(),
                  max(Z.GetdZxy(), Z.GetZxy().imag() * errorlevel)), Zyxr_dist(
                  Z.GetZyx().real(), max(Z.GetdZyx(), Z.GetZyx().real()
                      * errorlevel)), Zyxi_dist(Z.GetZyx().imag(), max(Z.GetdZyx(),
                  Z.GetZyx().imag() * errorlevel)), Zyyr_dist(Z.GetZyy().real(),
                  max(Z.GetdZyy(), Z.GetZyy().real() * errorlevel)), Zyyi_dist(
                  Z.GetZyy().imag(), max(Z.GetdZyy(), Z.GetZyy().imag()
                      * errorlevel)), Zxxr(generator, Zxxr_dist), Zxxi(generator,
                  Zxxi_dist), Zxyr(generator, Zxyr_dist),
              Zxyi(generator, Zxyi_dist), Zyxr(generator, Zyxr_dist), Zyxi(
                  generator, Zyxi_dist), Zyyr(generator, Zyyr_dist), Zyyi(
                  generator, Zyyi_dist), func(f), Data(Z)
          {
          }
      //! each call to operator() returns a new random sample
      double operator()()
      {
        MTTensor Point(std::complex<double>(Zxxr(), Zxxi()), std::complex<
            double>(Zxyr(), Zxyi()), std::complex<double>(Zyxr(), Zyxi()),
            std::complex<double>(Zyyr(), Zyyi()), Data.GetFrequency());
        return func(&Point);
      }
      virtual ~MTSampleGenerator();
      };
  /* @} */
  }
#endif /*MTSAMPLEGENERATOR_H_*/
