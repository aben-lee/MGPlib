#include "MTStation.h"
#include "Util.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace gplib;

string version = "$Id: printrhostar.cpp 1845 2010-04-12 11:55:22Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Print Schmucker's \f$z^\ast\f$ and \f$\rho^\ast\f$ for the off-diagonal components of an MT Site.
 * All components are written to the same file as a function of Period.
 */

void PrintRhosZs(const MTTensor &Elem)
  {
    cout << setw(10) << 1. / Elem.GetFrequency() << " Zxy*: ";
    cout << setw(10) << Elem.GetZxyStar() << " Zyx*: ";
    cout << setw(10) << Elem.GetZyxStar() << " Rhoxy*: ";
    cout << setw(10) << Elem.GetRhoxyStar() << " Rhoyx*: ";
    cout << setw(10) << Elem.GetRhoyxStar() << endl;
  }

int main(int argc, char *argv[])
  {
    string infilename;
    MTStation Data;
    cout
        << " This is printrhostar: Print Schmucker's rho* z* for a single site"
        << endl; // write some info
    cout << " Reads in a single station file and prints values to screen"
        << endl;
    cout
        << " Usage: printrhostar filename or just printrhostar for interactive mode"
        << endl;
    cout << " This is Version: " << version << endl << endl;
    if (argc == 2)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Input filename: ");
      }
    Data.GetData(infilename);
    for_each(Data.GetMTData().begin(), Data.GetMTData().end(), PrintRhosZs);

  }
/*@}*/
