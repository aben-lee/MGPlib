/*! 
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate apparent resistivity and phase from a .mtt, .edi or .j file and write 
 * one file with error information for each component to use for plotting. The program
 * will automatically append .rxx, .rxy, .ryx and .ryy for the four apparent resistivities and
 * .pxx, .pxy, .pyx and .pyy for the four phases respectively. It also outputs the apparent resistivity and phases of the 
 * Berdichevskiy invariant in the files .rberd and .pberd, respectively.
 * Each file contains lines with Period in seconds, the respective datum and its error.
 */
#include "MTStation.h"
#include <boost/function.hpp>
#include "Util.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace gplib;

void WriteToFile(string filename,
    boost::function<double(const MTTensor*)> datafunc, boost::function<double(
        const MTTensor*)> errfunc, const MTStation &Data)
  {
    ofstream outfile(filename.c_str());
    const size_t ndata = Data.GetMTData().size();
    for (size_t i = 0; i < ndata; ++i)
      {
        outfile << setw(15) << setfill(' ') << setprecision(4) << 1. / Data.at(
            i).GetFrequency();
        outfile << setw(15) << setfill(' ') << setprecision(4) << datafunc(
            &Data.at(i));
        outfile << setw(15) << setfill(' ') << setprecision(4) << errfunc(
            &Data.at(i)) << endl;
      }
  }

int main(int argc, char *argv[])
  {
    string version = "$Id: plotmtt.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout
        << "Write out impedance phase and apparent resistivity for plotting.  "
        << endl;
    cout
        << "Will create 8 files starting with Infilename and endings r** for apparent resistivity components  "
        << endl;
    cout << " and p** for phase components." << endl << endl;
    string infilename;
    MTStation Data;
    if (argc == 2)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Infilename: ");
      }
    Data.GetData(infilename);
    WriteToFile(infilename + ".rxx", &MTTensor::GetRhoxx, &MTTensor::GetdRhoxx,
        Data);
    WriteToFile(infilename + ".rxy", &MTTensor::GetRhoxy, &MTTensor::GetdRhoxy,
        Data);
    WriteToFile(infilename + ".ryx", &MTTensor::GetRhoyx, &MTTensor::GetdRhoyx,
        Data);
    WriteToFile(infilename + ".ryy", &MTTensor::GetRhoyy, &MTTensor::GetdRhoyy,
        Data);
    WriteToFile(infilename + ".pxx", &MTTensor::GetPhi90xx,
        &MTTensor::GetdPhixx, Data);
    WriteToFile(infilename + ".pxy", &MTTensor::GetPhi90xy,
        &MTTensor::GetdPhixy, Data);
    WriteToFile(infilename + ".pyx", &MTTensor::GetPhi90yx,
        &MTTensor::GetdPhiyx, Data);
    WriteToFile(infilename + ".pyy", &MTTensor::GetPhi90yy,
        &MTTensor::GetdPhiyy, Data);
    WriteToFile(infilename + ".rberd", &MTTensor::GetRhoBerd,
        &MTTensor::GetdRhoBerd, Data);
    WriteToFile(infilename + ".pberd", &MTTensor::GetPhi90Berd,
        &MTTensor::GetdPhi90Berd, Data);

  }
/*@}*/
