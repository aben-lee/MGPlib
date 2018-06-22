#include <iostream>
#include "MtuFormat.h"
#include "Util.h"

using namespace std;
using namespace gplib;

string version = "$Id: mtugood.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Remove the "bad" flag from all records of a Phoenix mtu time-series. 
 */

void WriteInfoAndAsk(string &infilename, string &outfilename)
  {
    cout << "This is mtugood: mark all records of  Phoenix time series as good"
        << endl << endl;
    cout << " Usage: mtugood infilename outfilename ! " << endl;
    cout
        << " If no outfilename given ending '.good'  will be automatically appended to infilename"
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;
    infilename = AskFilename("Infilename: ");
    outfilename = infilename + ".good";
  }

int main(int argc, char *argv[])
  {
    string infilename, outfilename;
    switch (argc)
      {
    case 2:
      infilename = argv[1];
      outfilename = string(argv[1]) + ".good";
      break;
    case 3:
      infilename = argv[1];
      outfilename = argv[2];
      break;
    default:
      WriteInfoAndAsk(infilename, outfilename);
      break;
      }
    MtuFormat Data;
    Data.GetData(infilename);
    Data.MakeGood();
    Data.WriteData(outfilename);
  }
/*@}*/
