#ifndef NETCDFTOOLS_H_
#define NETCDFTOOLS_H_
#include "netcdfcpp.h"
#include "VecMat.h"
#include "FatalException.h"
#include <string>

namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    //! Write a ublas matrix as a netcdf file, the indexing of the columns in the file is opposite to the index of the matrix for better plotting
    void WriteMatrixAsNetCDF(const std::string name, const gplib::rmat &Matrix)
      {
        NcFile mtrescdf(name.c_str(), NcFile::Replace);
        NcDim* xd = mtrescdf.add_dim("x", Matrix.size1());
        NcDim* yd = mtrescdf.add_dim("y", Matrix.size2());
        NcVar* x = mtrescdf.add_var("x", ncFloat, xd);
        NcVar* y = mtrescdf.add_var("y", ncFloat, yd);
        NcVar* z = mtrescdf.add_var("z", ncFloat, xd, yd);
        float *xvals = new float[xd->size()];
        float *yvals = new float[yd->size()];
        float *zvals = new float[xd->size() * yd->size()];
        for (size_t i = 0; i < Matrix.size1(); ++i)
          {
            xvals[i] = i;
            for (size_t j = 0; j < Matrix.size2(); ++j)
              {
                yvals[j] = j;
                zvals[(Matrix.size1() - 1 - i) * Matrix.size2() + j] = Matrix(
                    i, j);
              }
          }
        x->put(xvals, xd->size());
        y->put(yvals, yd->size());
        z->put(zvals, z->edges());
        delete xvals;
        delete yvals;
        delete zvals;
      }

    //! Write two dimensional data stored in a Matrix to a netcdf file
    /*! This is an extension to WriteMatrixAsNetCDF. It takes two mandantory and three optional additional arguments
     * @param xvals the axis values for each matrix row
     * @param yvals the axis valzes for each matrix column
     * @param xlabel the label associated with xvals
     * @param ylabel the label associated with yvals
     * @param zlabel the label for the data values stored in the matrix
     */
    void Write2DDataAsNetCDF(const std::string name, const gplib::rmat &Matrix,
        const gplib::rvec &xvals, const gplib::rvec &yvals,
        const char xlabel[] = "x", const char ylabel[] = "y",
        const char zlabel[] = "z")
      {
        if (xvals.size() != Matrix.size1() || yvals.size() != Matrix.size2())
          throw FatalException("Matrix size not compatible with axis values !");
        NcFile mtrescdf(name.c_str(), NcFile::Replace);
        NcDim* xd = mtrescdf.add_dim(xlabel, Matrix.size1());
        NcDim* yd = mtrescdf.add_dim(ylabel, Matrix.size2());
        NcVar* x = mtrescdf.add_var(xlabel, ncFloat, xd);
        NcVar* y = mtrescdf.add_var(ylabel, ncFloat, yd);
        NcVar* z = mtrescdf.add_var(zlabel, ncFloat, xd, yd);
        float *xvalues = new float[xd->size()];
        float *yvalues = new float[yd->size()];
        float *zvalues = new float[xd->size() * yd->size()];
        for (size_t i = 0; i < Matrix.size1(); ++i)
          {
            xvalues[i] = xvals(i);
            for (size_t j = 0; j < Matrix.size2(); ++j)
              {
                yvalues[j] = yvals(j);
                zvalues[i * Matrix.size2() + j] = Matrix(i, j);
              }
          }
        x->put(xvalues, xd->size());
        y->put(yvalues, yd->size());
        z->put(zvalues, z->edges());
        delete xvalues;
        delete yvalues;
        delete zvalues;
      }
  /* @} */
  }
#endif /*NETCDFTOOLS_H_*/
