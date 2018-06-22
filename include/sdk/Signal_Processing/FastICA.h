#ifndef FASTICA_H_
#define FASTICA_H_
#include "VecMat.h"
#include <complex>
#include <iostream>
#include <cmath>
#include "PCA.h"

namespace ublas = boost::numeric::ublas;

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    void FastICA(rmat &input, rmat &source_estimate, rmat &mixing_matrix)
      {
        mixing_matrix = ublas::identity_matrix<double>(input.size1());
        rmat old_mix(mixing_matrix);
        rmat new_mix(mixing_matrix);
        rmat white_mat(mixing_matrix);
        cmat evec(input.size1(), input.size1());
        cvec eval(input.size1());
        PCA(input, evec, eval);
        white_mat = real(WhiteMat(evec, eval));
        std::cout << "white_mat: " << white_mat << std::endl;
        input = prod(white_mat, input);
        const int maxiterations = 1000;
        const double min_improv = 0.01;
        double improvement = 10.0;
        int niter = 0;
        while (niter < maxiterations)
          {
            //std::cout << std::endl << std::endl << "Iter: " << niter << std::endl;
            ublas::noalias(source_estimate) = ublas::prod(mixing_matrix, input);
            rmat pow3mat = prod(trans(input), mixing_matrix);

            for (size_t i = 0; i < pow3mat.size1(); ++i)
              {
                for (size_t j = 0; j < pow3mat.size2(); ++j)
                  pow3mat(i, j) = std::pow(pow3mat(i, j), 3);
              }
            new_mix = prod(input, pow3mat);
            new_mix /= input.size2();
            new_mix -= 3.0 * mixing_matrix;
            mixing_matrix = new_mix;

            rmat wwt = prod(mixing_matrix, trans(mixing_matrix));
            mixing_matrix /= sqrt(norm_inf(wwt));
            for (int i = 0; i < maxiterations; ++i)
              {
                rmat neww(mixing_matrix);
                wwt = prod(mixing_matrix, trans(mixing_matrix));
                neww *= 1.5;
                mixing_matrix = prod(wwt, mixing_matrix);
                mixing_matrix *= 0.5;
                neww -= mixing_matrix;
                mixing_matrix = neww;
                //std::cout << "neww: " << neww << std::endl;
              }

            ++niter;
          }

        noalias(source_estimate) = prod(trans(mixing_matrix), input);
        mixing_matrix = prod(trans(mixing_matrix), white_mat);
      }
  /* @} */
  }
//THIS IS FOR THE FUTURE
/*
 class FastICA
 {
 private:
 boost::numeric::ublas::matrix<double> Weights;
 public:
 void Separate(const boost::numeric::vector<double> &In,boost::numeric::vector<double> &Out);
 FastICA();
 virtual ~FastICA();
 };*/

#endif /*FASTICA_H_*/
