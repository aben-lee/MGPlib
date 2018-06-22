#include "ThreeDMTModel.h"
#include "FatalException.h"
#include "netcdfcpp.h"
#include <fstream>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
using namespace std;
using namespace boost::lambda;

namespace gplib
  {
    ThreeDMTModel::ThreeDMTModel()
      {
        airlayers = 0;
      }

    ThreeDMTModel::~ThreeDMTModel()
      {
      }

    double ThreeDMTModel::LookupResistivity(const int index)
      {
        return Resistivities[index];
      }

    int ThreeDMTModel::LookupIndex(const double resistivity)
      {
        const size_t nresistivity = Resistivities.size();
        for (size_t i = 0; i < nresistivity; ++i)
          if (Resistivities[i] == resistivity)
            return i;

        Resistivities.push_back(resistivity);
        return (nresistivity);
      }

    void ThreeDMTModel::ReadWinGLink(std::string filename)
      {
        ifstream infile(filename.c_str());
        size_t xlength, ylength, zlength = 0;
        int currentlayer = 0;
        size_t i, j, k = 0;
        double currentres = 0;
        char dummy[255];
        infile >> xlength >> ylength >> zlength >> airlayers;
        if (infile.fail())
          throw FatalException("Cannot read file: " + filename);
        infile.getline(dummy, 255);

        Model.resize(boost::extents[xlength][ylength][zlength]);
        xsize.resize(xlength);
        ysize.resize(ylength);
        zsize.resize(zlength);

        for (i = 0; i < xlength; ++i)
          infile >> xsize[i];
        for (i = 0; i < ylength; ++i)
          infile >> ysize[i];
        for (i = 0; i < zlength; ++i)
          infile >> zsize[i];

        for (i = 0; i < zlength; ++i)
          {
            infile >> currentlayer;
            for (j = 0; j < ylength; ++j)
              for (k = 0; k < xlength; ++k)
                {
                  infile >> currentres;
                  Model[k][j][currentlayer - 1] = LookupIndex(currentres);
                }
          }
        //Resistivities.resizeAndPreserve(nresistivity);
        if (infile.fail())
          throw FatalException("Problem reading file: " + filename);
      }

    void ThreeDMTModel::ReadMackie(std::string filename)
      {
        ifstream infile(filename.c_str());
        size_t xlength, ylength, zlength;
        int currentlayer;
        size_t i, j, k;

        infile >> xlength >> ylength >> zlength;
        if (infile.fail())
          throw FatalException("Cannot read file: " + filename);
        Model.resize(boost::extents[xlength][ylength][zlength]);
        xsize.resize(xlength);
        ysize.resize(ylength);
        zsize.resize(zlength);

        for (i = 0; i < xlength; ++i)
          infile >> xsize[i];
        for (i = 0; i < ylength; ++i)
          infile >> ysize[i];
        for (i = 0; i < zlength; ++i)
          infile >> zsize[i];

        for (i = 0; i < zlength; ++i)
          {
            infile >> currentlayer;
            for (j = 0; j < ylength; ++j)
              for (k = 0; k < xlength; ++k)
                infile >> Model[k][j][currentlayer - 1];
          }

        while (infile.good())
          {
            double currvalue = 0.0;
            infile >> currvalue;
            Resistivities.push_back(currvalue);
          }

        if (!infile.eof())
          throw FatalException("Problem reading file: " + filename);

      }

    void ThreeDMTModel::WriteWinGLink(std::string filename)
      {
        ofstream outfile(filename.c_str());
        size_t i, j, k;
        const size_t xlength = xsize.size();
        const size_t ylength = ysize.size();
        const size_t zlength = zsize.size();
        //write out the number of cells in each direction and the number of airlayers
        //followed by the keyword values
        outfile << xlength << " " << ylength << " " << zlength << " "
            << airlayers << " VALUES" << endl;
        //write out the cell sizes in x-direction
        std::copy(xsize.begin(), xsize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the cell sizes in y-direction
        std::copy(ysize.begin(), ysize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the cell sizes in z-direction
        std::copy(zsize.begin(), zsize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the resistivity values for each cell
        //by looking up the resistivity from the index of each cell
        for (i = 0; i < zlength; ++i)
          {
            outfile << i + 1 << endl;
            for (j = 0; j < ylength; ++j)
              {
                for (k = 0; k < xlength; ++k)
                  outfile << LookupResistivity(Model[k][j][i]) << " ";
                outfile << endl;
              }
          }
        if (outfile.fail())
          throw FatalException("Problem writing file: " + filename);
      }

    void ThreeDMTModel::WriteMackie(std::string filename)
      {
        ofstream outfile(filename.c_str());
        size_t i, j, k;
        const size_t xlength = xsize.size();
        const size_t ylength = ysize.size();
        const size_t zlength = zsize.size();
        //write out the number of values in each direction
        outfile << xlength << " " << ylength << " " << zlength << endl;
        //write out the cell sizes in x-direction
        std::copy(xsize.begin(), xsize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the cell sizes in y-direction
        std::copy(ysize.begin(), ysize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the cell sizes in z-direction
        std::copy(zsize.begin(), zsize.end(), std::ostream_iterator<double>(
            outfile, " "));
        outfile << endl;
        //write out the resistivity index for each cell
        for (i = 0; i < zlength; ++i)
          {
            outfile << i + 1 << endl;
            for (j = 0; j < ylength; ++j)
              {
                for (k = 0; k < xlength; ++k)
                  outfile << Model[k][j][i] << " ";
                outfile << endl;
              }
          }
        //write out the resistivities that correspond to each index
        std::copy(Resistivities.begin(), Resistivities.end(),
            std::ostream_iterator<double>(outfile, " "));
        if (outfile.fail())
          throw FatalException("Problem writing file: " + filename);
      }

    void ThreeDMTModel::WriteNetCDF(std::string filename)
      {
        //prepare the netcdf file object
        NcFile cdf(filename.c_str(), NcFile::Replace);
        if (!cdf.is_valid())
          throw FatalException("Problem writing cdf file");
        //write dimension information
        NcDim* xd = cdf.add_dim("x", xsize.size());
        NcDim* yd = cdf.add_dim("y", ysize.size());
        NcDim* zd = cdf.add_dim("z", zsize.size());
        NcVar* x = cdf.add_var("x", ncDouble, xd);
        //write some attributes to make the file understandable
        x->add_att("units", "meters");
        x->add_att("long_name", "x-coordinate in Cartesian system");
        NcVar* y = cdf.add_var("y", ncDouble, yd);
        y->add_att("units", "meters");
        y->add_att("long_name", "y-coordinate in Cartesian system");
        NcVar* z = cdf.add_var("z", ncDouble, zd);
        z->add_att("units", "meters");
        z->add_att("long_name", "z-coordinate in Cartesian system");
        z->add_att("positive", "down");
        NcVar* res = cdf.add_var("res", ncDouble, xd, yd, zd);
        res->add_att("units", "ohm meters");
        res->add_att("long_name", "Resistivity");
        res->add_att("coordinates", "x y z");
        std::vector<double> xvals, yvals, zvals, resvals;
        //the netcdf file need the coordinates not the sizes
        std::partial_sum(xsize.begin(), xsize.end(), std::back_inserter(xvals));
        std::partial_sum(ysize.begin(), ysize.end(), std::back_inserter(yvals));
        std::partial_sum(zsize.begin(), zsize.end(), std::back_inserter(zvals));
        const size_t nres = Model.num_elements();
        //get the resistivity values from the indices
        std::transform(Model.origin(), Model.origin() + nres, back_inserter(
            resvals), _1 = var(Resistivities)[_1]);
        //store everything in the file
        x->put(&xvals[0], xd->size());
        y->put(&yvals[0], yd->size());
        z->put(&zvals[0], zd->size());
        res->put(&resvals[0], res->edges());
      }

    void ThreeDMTModel::WriteVTK(std::string filename)
      {
        ofstream outfile(filename.c_str());
        //write header information for the vtk file
        //this is the legacy vtk format
        outfile << "# vtk DataFile Version 2.0" << endl;
        outfile << "3D Model data" << endl;
        outfile << "ASCII" << endl;
        outfile << "DATASET RECTILINEAR_GRID" << endl;
        //we want to write grid cells, so we need one more value than cells
        //this is for the left/right boundaries
        outfile << "DIMENSIONS " << xsize.size() + 1 << " " << ysize.size() + 1
            << " " << zsize.size() + 1 << endl;
        //write out the information for each coordinate axis
        outfile << "X_COORDINATES " << xsize.size() + 1 << " double" << endl;
        double currcoord = 0.0;
        outfile << currcoord << " ";
        std::partial_sum(xsize.begin(),xsize.end(),std::ostream_iterator<double>(outfile," "));
        outfile << endl;
        outfile << "Y_COORDINATES " << ysize.size() + 1 << " double" << endl;
        currcoord = 0;
        outfile << currcoord << " ";
        std::partial_sum(ysize.begin(),ysize.end(),std::ostream_iterator<double>(outfile," "));
        outfile << endl;
        outfile << "Z_COORDINATES " << zsize.size() + 1 << " double" << endl;
        currcoord = 0;
        outfile << currcoord << " ";
        std::partial_sum(zsize.begin(),zsize.end(),std::ostream_iterator<double>(outfile," "));
        outfile << endl;
        outfile << "CELL_DATA " << xsize.size() * ysize.size() * zsize.size()
            << endl;
        outfile << "SCALARS Resistivity double" << endl;
        outfile << "LOOKUP_TABLE default" << endl;
        //and finally write out the resistivity values, x varies fastest
        for (size_t i = 0; i < zsize.size(); ++i)
          {
            for (size_t j = 0; j < ysize.size(); ++j)
              {
                for (size_t k = 0; k < xsize.size(); ++k)
                  {
                    outfile << LookupResistivity(Model[k][j][i]) << " ";
                  }
                outfile << endl;
              }
          }
        if (outfile.fail())
          throw FatalException("Problem writing vtk  file");
      }
  }
