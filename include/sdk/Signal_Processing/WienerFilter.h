#ifndef CWIENERFILTER_H_
#define CWIENERFILTER_H_

#include "AdaptiveFilter.h"
#include "VecMat.h"
#include "miscfunc.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
 #include <boost/numeric/ublas/triangular.hpp>
 #include <boost/numeric/ublas/lu.hpp>
 #include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

namespace gplib
  {

    /** \addtogroup sigproc Signal processing methods */
    /* @{ */
    //! This class is currently broken !!!!!
    class WienerFilter: public AdaptiveFilter
      {
        template<class InMatrix, class OutMatrix>
        bool InvertMatrix(InMatrix& input, OutMatrix& inverse)
          {
            using namespace boost::numeric::ublas;
            typedef permutation_matrix<std::size_t> pmatrix;

            // create a permutation matrix for the LU-factorization
            pmatrix pm(input.size1());

            // perform LU-factorization
            int res = lu_factorize(input, pm);
            if (res != 0)
              return false;

            // create identity matrix of "inverse"
            inverse.assign(boost::numeric::ublas::identity_matrix<double>(
                input.size1()));

            // backsubstitute to get the inverse
            lu_substitute(input, pm, inverse);

            return true;
          }
    private:
      gplib::rmat CorrMatrix;
      gplib::rvec Weights;
      double lambda;
    public:
      virtual void PrintWeights(std::ostream &output)
      {
        std::copy(Weights.begin(), Weights.end(),
            std::ostream_iterator<double>(output, "\n"));
      }
      virtual void
      AdaptFilter(const gplib::rvec &Input, const gplib::rvec &Desired)
      {
        const int inputsize = Input.size();
        vector<double> Cross(Input.size());
        vector<double> Auto(Input.size());
        Correl(Desired, Desired, Auto);
        Correl(Input, Desired, Cross);
        for (int i = 0; i < inputsize; ++i)
          for (int j = i; j < inputsize; ++j)
            {
              CorrMatrix(i, j) = Auto(j - i);
              CorrMatrix(j, i) = Auto(j - i);
            }
        CorrMatrix += lambda * identity_matrix<double> (inputsize);
        matrix<double> Inverse(inputsize, inputsize);

        InvertMatrix(CorrMatrix,Inverse);


        axpy_prod(Inverse, Cross, Weights, true);

      }
      virtual void CalcOutput(const gplib::rvec &Input, gplib::rvec &Output)
      {
        vector<double> output(Input.size());
        Convolve(Input, Weights, Output);
        SetOutput(Output);
      }
      void SetLambda(const double mylambda)
        {
          lambda = mylambda;
        }
      WienerFilter(const int inputsize):
          AdaptiveFilter(inputsize, inputsize), CorrMatrix(inputsize, inputsize),
              Weights(inputsize), lambda(0)
          {
          }

      virtual ~WienerFilter();
      };
  /* @} */
  }
#endif /*CWIENERFILTER_H_*/
