#include <iostream>
#include <fstream>
#include "MTStation.h"
#include "MTSampleGenerator.h"
#include "Jacknife.h"
#include <boost/function.hpp>
#include "Util.h"

using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate various dimensionality indicators for MT data and their errors and write them to a file
 */

//! This helper function calculates the errors for a single parameter and writes the values to a file in ascii format
void WriteParameterToFile(const MTStation &Data, const string &filename,
    boost::function<double (const MTTensor*)> f)
  {
    // we use a fixed number of samples for the jacknifing
    const int errorcases = 10000;
    const double errorfloor = 0.02;
    double JackMean, JackErr;
    ofstream muoutfile(filename.c_str());
    //for each period
    for (size_t i = 0; i < Data.GetMTData().size(); ++i)
      {
        //calculate the error
        MTSampleGenerator Generator(f, Data.GetMTData().at(i), errorfloor);
        Jacknife<MTSampleGenerator> ErrEst(errorcases, Generator);
        ErrEst.CalcErrors(JackMean, JackErr);
        // and write period, data, error to a file
        muoutfile << 1. / Data.GetMTData().at(i).GetFrequency();
        muoutfile << " " << f(&Data.GetMTData().at(i)) << " " << sqrt(JackErr)
            << endl;
      }
  }

int main(int argc, char *argv[])
  {
    string infilename;
    MTStation Data;
    // find out which file to work on
    if (argc == 2)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Infilename: ");
      }
    //read in the data from the file
    Data.GetData(infilename);
    //write out various dimensionality indicators
    WriteParameterToFile(Data, infilename + ".mu", &MTTensor::GetMu);
    WriteParameterToFile(Data, infilename + ".kappa", &MTTensor::GetKappa);
    WriteParameterToFile(Data, infilename + ".sigma", &MTTensor::GetSigma);
    WriteParameterToFile(Data, infilename + ".eta", &MTTensor::GetEta);
    WriteParameterToFile(Data, infilename + ".Q", &MTTensor::GetQ);
    WriteParameterToFile(Data, infilename + ".I1", &MTTensor::GetI1);
    WriteParameterToFile(Data, infilename + ".I2", &MTTensor::GetI2);
    WriteParameterToFile(Data, infilename + ".I3", &MTTensor::GetI3);
    WriteParameterToFile(Data, infilename + ".I4", &MTTensor::GetI4);
    WriteParameterToFile(Data, infilename + ".I5", &MTTensor::GetI5);
    WriteParameterToFile(Data, infilename + ".I6", &MTTensor::GetI6);
    WriteParameterToFile(Data, infilename + ".I7", &MTTensor::GetI7);
    //we cannot write this with WriteParameterToFile, so we do it separately
    ofstream muoutfile((infilename + ".d2").c_str());
    for (size_t i = 0; i < Data.GetMTData().size(); ++i)
      {
        muoutfile << 1. / Data.GetMTData().at(i).GetFrequency();
        muoutfile << " " << 2 * Data.GetMTData().at(i).GetdBerd()
            / Data.GetMTData().at(i).GetD2() << endl;
      }

  }
/*@}*/

