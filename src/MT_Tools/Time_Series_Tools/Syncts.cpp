#include <iostream>
#include <string>
#include <numeric>
#include "TimeSeriesData.h"
#include "FatalException.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Util.h"

using namespace std;
using namespace gplib;

string version = "$Id: syncts.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Synchronize 2 files so that they have exactly the same start time and end time. This program
 * does not fix gaps that are only present in one file !
 */

int main(int argc, char *argv[])
  {
    string infilename1, infilename2;

    cout << "This is syncts: Synchronize the start of two time series" << endl
        << endl;
    cout << "Usage: syncts filename1 filename2" << endl;
    cout << "The outputfiles will have the starttime of whatever starts later"
        << endl;
    cout << "They will have the same name as the input files + .sync " << endl
        << endl;
    cout << "This is Version: " << version << endl << endl;
    if (argc == 3)
      {
        infilename1 = argv[1];
        infilename2 = argv[2];
      }
    else
      {
        infilename1 = AskFilename("First Input Filename: ");
        infilename2 = AskFilename("Second Input Filename:  ");

      }
    cout << "Synchronizing ... " << endl;
    TimeSeriesData Data1, Data2;
    try
      {
        Data1.GetData(infilename1);
        Data2.GetData(infilename2);
        cout << "Start time file 1: " << Data1.GetData().GetTime().front()
            << endl;
        cout << "Start time file 2: " << Data2.GetData().GetTime().front()
            << endl << endl;
        Synchronize(Data1.GetData(), Data2.GetData());
        Data1.WriteAsBirrp(infilename1 + ".sync");
        Data2.WriteAsBirrp(infilename2 + ".sync");
        cout << "New start time file 1: " << Data1.GetData().GetTime().front()
            << endl;
        cout << "New start time file 2: " << Data2.GetData().GetTime().front()
            << endl;
      } catch (const FatalException &e)
      {
        cerr << e.what() << endl;
      }
    cout << "... done " << endl;
  }
/*@}*/
