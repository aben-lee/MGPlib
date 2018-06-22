#include "VecMat.h"
#include "NetCDFTools.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/minmax_element.hpp>
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace gplib;

int main()
  {
    string infilename, outfilename;

    string version = "$Id: 1dinvga.cpp 1136 2007-05-15 22:27:10Z max $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout
        << "Create a two dimensional density plot from the models in the input file."
        << endl;
    cout << "This would usually be a concatenation of several '.plot' files "
        << endl;
    cout << "Specify the input file name and the output file name. " << endl;
    cout << "Output is in netcdf format. " << endl;
    cout << endl << endl;

    cout << "Input file: ";
    cin >> infilename;
    bool wantlogparm = false;
    string logchoice;
    cout << "Do you want the logarithm of the parametervalue plotted (y/n): ";
    cin >> logchoice;
    string yes("y");
    if (boost::is_equal()(logchoice, yes))
      {
        wantlogparm = true;
        cout << "Y-Axis will be logarithmic !" << endl;
      }
    ifstream infile(infilename.c_str());
    std::vector<double> depth, parmvalue;
    double currdepth, currparmvalue;
    while (infile.good())
      {
        infile >> currdepth >> currparmvalue;
        if (infile.good())
          {
            depth.push_back(currdepth);
            parmvalue.push_back(currparmvalue);
          }
      }
    if (depth.size() != parmvalue.size())
      {
        cerr << "Problem reading file !" << endl;
        return 100;
      }
    else
      {
        cerr << "Read in file." << endl;
      }
    typedef vector<double>::const_iterator it;
    pair<it, it> depthminmax =
        boost::minmax_element(depth.begin(), depth.end());
    pair<it, it> parmminmax = boost::minmax_element(parmvalue.begin(),
        parmvalue.end());
    const double depthstep = 1.0;
    const double parmstep = 0.1;
    const double logparmstep = 0.1;
    const double deptheps = *(depthminmax.second) * 0.1;
    const double parmeps = *(parmminmax.second) * 0.1;
    const double mindepth = *(depthminmax.first);
    const double maxdepth = *(depthminmax.second) + deptheps;
    double minparm;
    if (*(parmminmax.first) > 0.0)
      minparm = *(parmminmax.first) * 0.9;
    else
      minparm = *(parmminmax.first) * 1.1;
    const double maxparm = *(parmminmax.second) + parmeps;
    const unsigned int ndepths = (maxdepth - mindepth) / depthstep;
    unsigned int temp = 0;
    if (wantlogparm)
      {
        temp = (log10(maxparm) - log10(minparm)) / logparmstep + 1;
      }
    else
      {
        temp = (maxparm - minparm) / parmstep + 1;
      }
    const unsigned int nparms = temp;
    gplib::rmat Density(ndepths, nparms);

    fill_n(Density.data().begin(), ndepths * nparms, 0.0);
    ;
    for (unsigned int i = 0; i < depth.size() - 1; ++i)
      {
        double nextdepth = depth.at(i + 1);
        if (nextdepth < depth.at(i))
          {
            nextdepth = maxdepth;
          }
        unsigned int depthindex = (depth.at(i) - mindepth) / depthstep;
        unsigned int nextdepthindex = (nextdepth - mindepth) / depthstep - 1;
        unsigned int parmindex;
        if (wantlogparm)
          {
            parmindex = (log10(parmvalue.at(i)) - log10(minparm)) / logparmstep;
          }
        else
          {
            parmindex = (parmvalue.at(i) - minparm) / parmstep;
          }
        for (unsigned int j = depthindex; j < nextdepthindex; ++j)
          Density(j, parmindex) += 1.0;
      }

    gplib::rvec depthvals(ndepths);
    gplib::rvec parmvals(nparms);
    for (unsigned int i = 0; i < ndepths; ++i)
      depthvals(i) = -1.0 * i * depthstep;
    for (unsigned int i = 0; i < nparms; ++i)
      {
        if (wantlogparm)
          {
            parmvals(i) = log10(minparm) + (i + 0.5) * logparmstep;
          }
        else
          {
            parmvals(i) = minparm + (i + 0.5) * parmstep;
          }
      }
    cout << "Output file: ";
    cin >> outfilename;
    ofstream avgfile((outfilename + ".avg").c_str());
    for (unsigned int i = 0; i < ndepths; ++i) // for all depths
      {
        double avg = 0.0;
        unsigned int count = 0;
        for (unsigned int j = 0; j < nparms; ++j)
          {
            avg += Density(i, j) * parmvals(j);
            count += Density(i, j);
          }
        avgfile << depthvals(i) << " " << avg / count << endl;
      }
    Write2DDataAsNetCDF(outfilename, Density, depthvals, parmvals, "Depth");

  }

