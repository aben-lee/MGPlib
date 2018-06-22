#include <iostream>
#include <string>
#include "MTStationList.h"
#include "PTensorMTStation.h"
#include "Adaptors.h"
#include "Jacknife.h"
#include "MTSampleGenerator.h"
#include "Util.h"

using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file mtt2ptensor.cpp
 * Take a file containing impedances in one of the standard formats and convert it to phase tensor values with errors.
 * This is useful for inverting phase tensor quantities and processing different files based on phase tensor information.
 */


int main(int argc, char* argv[])
  {
    MTStationList MTSites;
    string infilename;
    string version =
        "$Id: mtt2ptensor.cpp 1849 2010-05-07 11:53:45Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << " Convert MT data files in .mtt .j .edi format to .ptensor format"
        << endl;
    cout << " This is needed in conjunction with the program ptselect " << endl;
    cout << "  to select similar sites." << endl;
    cout << endl << endl;

    if (argc == 2)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Input Filename: ");
      }
    MTSites.GetData(infilename);
    const unsigned int nsites = MTSites.GetList().size();
    const unsigned int ntestcases = 10000;
    for (unsigned int i = 0; i < nsites; ++i)
      {
        cout << "Writing site " << MTSites.GetList().at(i).GetName();
        PTensorMTStation PTData;
        const unsigned int nfreq = MTSites.at(i).GetMTData().size();
        for (unsigned j = 0; j < nfreq; ++j)
          {
            double JackMean, Phi11Var, Phi12Var, Phi21Var, Phi22Var;
            Jacknife<MTSampleGenerator> (ntestcases, MTSampleGenerator(
                &MTTensor::GetPhi11, MTSites.at(i).at(j))).CalcErrors(JackMean,
                Phi11Var);
            Jacknife<MTSampleGenerator> (ntestcases, MTSampleGenerator(
                &MTTensor::GetPhi21, MTSites.at(i).at(j))).CalcErrors(JackMean,
                Phi12Var);
            Jacknife<MTSampleGenerator> (ntestcases, MTSampleGenerator(
                &MTTensor::GetPhi12, MTSites.at(i).at(j))).CalcErrors(JackMean,
                Phi21Var);
            Jacknife<MTSampleGenerator> (ntestcases, MTSampleGenerator(
                &MTTensor::GetPhi22, MTSites.at(i).at(j))).CalcErrors(JackMean,
                Phi22Var);

            PTData.GetTensor().push_back(PTensorMTData(
                MTSites.at(i).at(j).GetFrequency(),
                MTSites.at(i).at(j).GetPhi11(), MTSites.at(i).at(j).GetPhi12(),
                MTSites.at(i).at(j).GetPhi21(), MTSites.at(i).at(j).GetPhi22(),
                sqrt(Phi11Var), sqrt(Phi12Var), sqrt(Phi21Var), sqrt(Phi22Var)));
            PTData.WriteData(MTSites.GetList().at(i).GetName());
          }
        cout << "    ... done" << endl;
      }
  }
/*@}*/
