#include <iostream>
#include <string>
#include "ThreeDMTModel.h"
#include <fstream>
#include "types.h"
#include <boost/filesystem/operations.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/multi_array.hpp>
#include "netcdfcpp.h"
#include "Util.h"

using namespace std;
using namespace boost::filesystem;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file plotlayer.cpp
 * Write a single layer of a WinGLink or Mackie 3D model into a netcdf file for plotting with GMT.
 */


int main(void)
  {
    string version = "$Id: plotlayer.cpp 1849 2010-05-07 11:53:45Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Reads in WinGLink or old Mackie format 3D Model grids " << endl;
    cout
        << "and outputs the resistivity of a single layer for plotting with GMT "
        << endl;
    cout << "No input parameters supported " << endl;

    string infilename, outfilename;
    double maxdepth;

    double latmin, lonmin;
    int mode;
    //read in the  filename and some information about the format
    //as we cannot guess the format from the ending or typical information in the file
    infilename = AskFilename("Modelfile name: ");
    cout << "Type 1 for old Mackie, 2 for Winglink format: ";
    cin >> mode;
    //get information about what to plot
    cout << "Depth of layer to plot: ";
    cin >> maxdepth;
    cout << "Latitude of lower border: ";
    cin >> latmin;
    cout << "Longitude of left border: ";
    cin >> lonmin;
    outfilename = AskFilename("Outfile name: ");
    ThreeDMTModel Model;
    //this is for the very basic conversion from
    //a rectangular grid to latitude longitude , could be refined in the future.
    const double kmlatitude = 111194;
    const double kmlongitude = cos(latmin / 180. * PI) * kmlatitude;
    //read in the model
    if (mode == 1)
      Model.ReadMackie(infilename);
    else
      Model.ReadWinGLink(infilename);
    //setup the axis in x and y direction
    const int xsize = Model.GetXSizes().size();
    const int ysize = Model.GetYSizes().size();
    typedef boost::multi_array<double, 1> tscalearray;
    tscalearray lonscale(boost::extents[xsize]),
        latscale(boost::extents[ysize]);
    double currentdepth = 0;
    int layerindex = 0;
    //find out the index of the layer that lies in the depth we want to plot
    while (currentdepth < maxdepth)
      {
        currentdepth += Model.GetZSizes()[layerindex] / 1000;
        cout << currentdepth << endl;
        ++layerindex;
      }
    lonscale[0] = 0.0;
    latscale[0] = 0.0;
    //convert the model axes and write the model to a file
    //in the form lon lat resistivity
    // this can be used for example in GMT
    for (int i = 1; i < ysize; ++i)
      latscale[i] = latscale[i - 1] + Model.GetYSizes()[i - 1];
    for (int i = 1; i < xsize; ++i)
      lonscale[i] = lonscale[i - 1] + Model.GetXSizes()[i - 1];
    ofstream outfile(outfilename.c_str());
    for (int i = 0; i < xsize; ++i)
      for (int j = 0; j < ysize; ++j)
        {
          outfile << lonmin + lonscale[i] / kmlongitude << " " << latmin
              + latscale[ysize - 1 - j] / kmlatitude << " "
              << Model.GetResistivities()[Model.GetModel()[i][j][layerindex]]
              << endl;
        }
    //also create a netcdf file with the same information
    NcFile cdf((outfilename + ".nc").c_str(), NcFile::Replace);
    NcDim* latd = cdf.add_dim("lat", ysize);
    NcDim* lond = cdf.add_dim("lon", xsize);

    NcVar* lat = cdf.add_var("lat", ncFloat, latd);
    lat->add_att("units", "degrees_north");
    lat->add_att("long_name", "longitude");

    NcVar* lon = cdf.add_var("lon", ncFloat, lond);
    lon->add_att("units", "degrees_east");
    lon->add_att("long_name", "latitude");
    NcVar* res = cdf.add_var("res", ncFloat, latd, lond);
    res->add_att("units", "ohm meters");
    res->add_att("long_name", "Resistivity");
    res->add_att("coordinates", "lon lat");
    float *lonvals = new float[lond->size()];
    float *latvals = new float[latd->size()];

    float *resvals = new float[latd->size() * lond->size()];

    for (int i = 0; i < xsize; ++i)
      {
        lonvals[i] = lonmin + lonscale[i] / kmlongitude;
      }
    for (int i = 0; i < ysize; ++i)
      {
        latvals[i] = latmin + latscale[i] / kmlatitude;
      }
    for (int i = 0; i < xsize; ++i)
      {
        for (int j = 0; j < ysize; ++j)
          {
            resvals[(ysize - j - 1) * xsize + i]
                = Model.GetResistivities()[Model.GetModel()[i][j][layerindex]];
            //resvals[(ysize-j-1)*ysize+i] = Model.GetResistivities()[Model.GetModel()[i][j][layerindex]];
          }
      }
    lon->put(lonvals, lond->size());
    lat->put(latvals, latd->size());
    res->put(resvals, res->edges());
  }
/*@}*/
