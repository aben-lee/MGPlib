#ifndef COMPLEXICA_H_
#define COMPLEXICA_H_
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>
#include <iostream>
#include "PCA.h"
#include "VecMat.h"

namespace gplib
  {
    namespace ublas = boost::numeric::ublas;
    std::complex<double> sign(const std::complex<double> &z)
      {
        if (abs(z) == 0)
          return std::complex<double>(0.0, 0.0);
        else
          return z / abs(z);
      }

    double non_lin(const double x)
      {
        return (1.0 - exp(-x)) / (1.0 + exp(x));
      }

    void ComplexICA(cmat &input, cmat &source_estimate, cmat &mixing_matrix)
      {
        mixing_matrix = ublas::identity_matrix<double>(input.size1());
        cmat mix_grad(input.size1(), input.size1());
        const int maxiterations = 100;
        const double min_improv = 0.01;
        double improvement = 10.0;
        int niter = 0;

        cmat white_mat(mixing_matrix);
        cmat evec(input.size1(), input.size1());
        cvec eval(input.size1());
        PCA(input, evec, eval);
        white_mat = WhiteMat(evec, eval);
        std::cout << "white_mat: " << white_mat << std::endl;
        input = prod(white_mat, input);

        while (improvement > min_improv && niter < maxiterations)
          {
            std::cout << std::endl << std::endl << "Iter: " << niter
                << std::endl;
            ublas::noalias(source_estimate) = ublas::prod(mixing_matrix, input);
            cmat outer_expect(input.size1(), input.size1());
            cmat v(input.size1(), input.size2());
            for (size_t i = 0; i < v.size1(); ++i)
              {
                for (size_t j = 0; j < v.size2(); ++j)
                  v(i, j) = sign(source_estimate(i, j)) * non_lin(abs(
                      source_estimate(i, j)));
              }
            for (size_t i = 0; i < input.size2(); ++i)
              {
                outer_expect += ublas::outer_prod(ublas::column(v, i),
                    ublas::herm(ublas::column(source_estimate, i)));
              }
            outer_expect /= input.size2();
            mix_grad = mixing_matrix;
            ublas::axpy_prod(-outer_expect, mixing_matrix, mix_grad);
            mixing_matrix += real(mix_grad);
            //std::cout << "source: " << source_estimate << std::endl;
            std::cout << "mixing: " << mixing_matrix << std::endl;
            std::cout << "mix_grad: " << mix_grad << std::endl;
            std::cout << "Norm(mix_grad): " << ublas::norm_inf(mix_grad)
                << std::endl;
            std::cout << "outer_expect: " << outer_expect << std::endl;
            improvement = ublas::norm_inf(mix_grad) / ublas::norm_inf(
                mixing_matrix);
            std::cout << "improvement: " << improvement << std::endl;
            ++niter;
          }
      }
  }
#endif /*COMPLEXICA_H_*/
