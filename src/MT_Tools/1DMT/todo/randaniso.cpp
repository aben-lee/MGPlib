#include <iostream>
#include <string>
#include "C1DAnisoMTSynthData.h"
#include "UniformRNG.h"
#include "convert.h"
#include <iterator>

using namespace std;
using namespace gplib;

int main(void)
  {
    string version = "$Id: randaniso.cpp 1844 2010-04-12 11:34:25Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout
        << "Generates completely random anisotropic models and writes their response "
        << endl;

    C1DAnisoMTSynthData Synthetic; // create Object for Calculation of Synthetics
    UniformRNG Random;

    try
      {
        const unsigned int nlayers = 15;
        const unsigned int nmodels = 100;
        const double minres = -1;
        const double maxres = 3;
        const double minthick = 10;
        const double maxthick = 30;
        const double minangle = 0;
        const double maxangle = 90;
        trealdata currthick(nlayers);
        trealdata currrho1(nlayers);
        trealdata currrho2(nlayers);
        trealdata currstrike(nlayers);
        trealdata zeros(nlayers);
        for (unsigned int i = 0; i < nlayers; ++i)
          zeros.at(i) = 0.0;
        Synthetic.SetDips(zeros);
        Synthetic.SetSlants(zeros);
        string mttfilename = "out";
        const float ten = 10.0;

        for (unsigned int i = 0; i < nmodels; ++i)
          {
            for (unsigned int j = 0; j < nlayers; ++j)
              {
                currthick.at(j) = Random.GetNumber(minthick, maxthick);
                currrho1.at(j) = std::pow(ten, Random.GetNumber(minres, maxres));
                currrho2.at(j) = std::pow(ten, Random.GetNumber(minres, maxres));
                currstrike.at(j) = Random.GetNumber(minangle, maxangle);
              }
            Synthetic.SetRho1(currrho1);
            Synthetic.SetRho2(currrho2);
            Synthetic.SetRho3(currrho2);
            Synthetic.SetStrikes(currstrike);
            Synthetic.SetThicknesses(currthick);
            Synthetic.GetData();
            Synthetic.WriteAsMtt(mttfilename + stringify(i)); // Write out Mtt file
          }
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      }
  }
