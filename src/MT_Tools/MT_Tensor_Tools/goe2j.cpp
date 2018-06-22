#include <iostream>
#include <iterator>
#include "MTStationList.h"
#include "Util.h"

using namespace std;
using namespace gplib;

int main(int argc, char* argv[])
  {
    string version = "$Id: goe2j.cpp 1842 2010-04-09 14:30:17Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << " Convert edi files to .mtt and .j format." << endl;
    cout
        << " Input is a file that contains the names of the edi files to convert."
        << endl;
    cout << " For each file two new files in .j and .mtt format are written."
        << endl;
    cout << endl << endl;
    MTStationList MTSites;
    string infilename;
    if (argc > 1)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Input Filename: ");
      }

    MTSites.GetData(infilename);
    for (unsigned int i = 0; i < MTSites.GetList().size(); ++i)
      {
        cout << "Writing site " << MTSites.GetList().at(i).GetName();
        MTSites.at(i).WriteAsMtt(MTSites.GetList().at(i).GetName());
        MTSites.at(i).WriteAsJ(MTSites.GetList().at(i).GetName());
        cout << "    ... done" << endl;
      }
    if (!MTSites.GetList().empty())
      {
        cout << "Common frequencies: ";
        copy(MTSites.GetCommonFrequencies().begin(),
            MTSites.GetCommonFrequencies().end(), ostream_iterator<double> (
                cout, " "));
        for (unsigned int j = 0; j < MTSites.GetCommonFrequencies().size(); ++j)
          cout << MTSites.GetCommonFrequencies().at(j) << " ";
        cout << endl;
        MTSites.WriteList(infilename + "_mtt");
      }
    else
      {
        cout << "Could not find any files !" << std::endl;
      }
  }

