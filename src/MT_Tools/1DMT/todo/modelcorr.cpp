#include <iostream>
#include "C1DMTSynthData.h"
#include "ResPkModel.h"
#include <string>
#include <numeric>

using namespace std;
using namespace gplib;

string version = "$Id: modelcorr.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

int main()
  {
    ResPkModel SeismicModel;
    C1DMTSynthData MTModel;
    string inputbase;

    cout
        << " This is modelcorr: Calculate 'correlation' of seismic and MT model"
        << endl; // write some info
    cout
        << " Input files are assumed to be have the name inputbase+_rec.mod and inputbase+_mt.mod"
        << endl;
    cout << " for seismic and MT models, respectively. " << endl;
    cout << " This is Version: " << version << endl << endl;

    cout << "Inputbase: ";
    cin >> inputbase;
    SeismicModel.ReadModel(inputbase + "_rec.mod");
    MTModel.ReadModel(inputbase + "_mt.mod");

    trealdata mtthickness(MTModel.GetThicknesses());
    trealdata seismicthickness(SeismicModel.GetThickness());
    trealdata mtdepth(mtthickness.size()),
        seismicdepth(seismicthickness.size());
    trealdata resistivity(MTModel.GetResistivities());
    trealdata svelocity(SeismicModel.GetSVelocity());
    partial_sum(mtthickness.begin(), mtthickness.end(), mtdepth.begin());
    partial_sum(seismicthickness.begin(), seismicthickness.end(),
        seismicdepth.begin());
    mtthickness.back() += 10000.0;
    seismicthickness.back() += 10000.0;
    bool finished = false;
    size_t mtindex = 0;
    size_t seismicindex = 0;
    const double depththreshold = 0.05;
    double mtdifferencemeasure = 0.0;
    double seismicdifferencemeasure = 0.0;
    int mtinterfaces = 0;
    int seismicinterfaces = 0;
    int corrinterfaces = 0;
    while (!finished)
      {
        double reldepthdiff = (mtdepth.at(mtindex) - seismicdepth.at(
            seismicindex)) / min(mtdepth.at(mtindex), seismicdepth.at(
            seismicindex));
        if (reldepthdiff > depththreshold && seismicindex < svelocity.size()
            - 1) //mt layer deeper
          {
            seismicdifferencemeasure += abs(svelocity.at(seismicindex)
                - svelocity.at(seismicindex + 1));
            ++seismicindex;
            ++seismicinterfaces;
          }
        else if (reldepthdiff < -depththreshold && mtindex < resistivity.size()
            - 1) //seismic layer deeper
          {
            mtdifferencemeasure += abs(resistivity.at(mtindex)
                - resistivity.at(mtindex + 1));
            ++mtindex;
            ++mtinterfaces;
          }
        else //both about the same
          {
            ++mtindex;
            ++seismicindex;
            ++corrinterfaces;
          }
        if (mtindex >= resistivity.size() || seismicindex >= svelocity.size())
          {
            finished = true;
          }
      }
    cout << "Seismic depths: ";
    copy(seismicdepth.begin(), seismicdepth.end(), ostream_iterator<double> (
        cout, " "));
    cout << endl;
    cout << "MT depths: ";
    copy(mtdepth.begin(), mtdepth.end(), ostream_iterator<double> (cout, " "));
    cout << endl;
    cout << "MT difference: " << mtdifferencemeasure << " Seismic difference: "
        << seismicdifferencemeasure << endl;
    cout << "MT only interfaces: " << mtinterfaces
        << " Seismic only interfaces: " << seismicinterfaces
        << " Common interfaces: " << corrinterfaces << endl;
  }
