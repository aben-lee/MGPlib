#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TimeFrequency.h"
#include "WFunc.h"
#include "TimeSeriesData.h"
#include "netcdfcpp.h"
#include "VecMat.h"
#include "Util.h"

using namespace std;
using namespace gplib;

string version =
    "$Id: mtutimefrequency.cpp 1850 2010-05-18 09:13:13Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate a time-frequency diagram for each component of a MT time-series file.
 * Output is 4 netcdf file where the ending signals the component.
 */

void CalcTfAndWrite(ttsdata Data, const double samplerate, const int seglength,
    const int timeavg, const string name)
  {

    gplib::cmat result = TimeFrequency(Data.begin(), Data.end(), seglength,
        Steep());
    const size_t ylength = result.size2() - timeavg;
    NcFile combrescdf(name.c_str(), NcFile::Replace);
    NcDim* xd = combrescdf.add_dim("x", result.size1());
    NcDim* yd = combrescdf.add_dim("y", ylength);
    NcVar* x = combrescdf.add_var("x", ncFloat, xd);
    NcVar* y = combrescdf.add_var("y", ncFloat, yd);
    NcVar* z = combrescdf.add_var("z", ncFloat, xd, yd);
    float *xvals = new float[xd->size()];
    float *yvals = new float[yd->size()];
    float *zvals = new float[xd->size() * yd->size()];
    float avg = 0.0;
    for (size_t i = 0; i < result.size1(); ++i) // time index
      {
        xvals[i] = i;

        for (size_t j = 0; j < ylength; ++j) //frequency index
          {
            avg = 0.0;
            for (int k = 0; k < timeavg; ++k)
              {
                avg += abs(result(i, j + k));
              }
            zvals[i * ylength + j] = log10(avg);
          }

      }
    for (size_t j = 0; j < ylength; ++j)
      yvals[j] = j * samplerate / seglength;
    x->put(xvals, xd->size());
    y->put(yvals, yd->size());
    z->put(zvals, z->edges());
  }

int main(int argc, char *argv[])
  {
    TimeSeriesData TsData;

    string infilename;
    size_t timeavg = 5;
    size_t seglength = 2400;
    cout
        << "This is mtutf: Calculate time frequency matrix from  Phoenix time series"
        << endl << endl;
    cout << " Usage:      mtutf filename" << endl;
    cout << "if no filename given, the program will ask for one" << endl;
    cout
        << " Output will be 4 netcdf files with ending _tfex.nc, _tfey.nc etc."
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    if (argc == 2)
      {
        infilename = argv[1];
      }
    else
      {
        cout << "Infilename: ";
        cin >> infilename;
      }
    TsData.GetData(infilename);
    cout << "Length of individual segments in points: ";
    cin >> seglength;
    cout << "Number of segments for time averaging: ";
    cin >> timeavg;
    const double samplerate = TsData.GetData().GetSamplerate();
    CalcTfAndWrite(TsData.GetData().GetEx().GetData(), samplerate, seglength,
        timeavg, (infilename + "_tfex.nc"));
    CalcTfAndWrite(TsData.GetData().GetEy().GetData(), samplerate, seglength,
        timeavg, (infilename + "_tfey.nc"));
    CalcTfAndWrite(TsData.GetData().GetHx().GetData(), samplerate, seglength,
        timeavg, (infilename + "_tfhx.nc"));
    CalcTfAndWrite(TsData.GetData().GetHy().GetData(), samplerate, seglength,
        timeavg, (infilename + "_tfhy.nc"));

  }
/*@}*/
