#include <iostream>
#include <iterator>
#include "MTStationList.h"
#include "Util.h"

using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Swap the phase of the impedance by 180 degrees. This is useful
 * when the responses assume a different time dependeny for the harmonic
 * fields.
 */

int main()
  {
    MTStationList MTSites;

    cout << " Swap all phases by 180 degrees." << endl;
    string infilename = AskFilename("Input Filename: ");
    MTSites.GetData(infilename);
    for (unsigned int i = 0; i < MTSites.GetList().size(); ++i)
      {
        cout << "Working on  site " << MTSites.GetList().at(i).GetName();
        for (unsigned int j = 0; j < MTSites.GetList().at(i).GetMTData().size(); ++j)
          {
            MTSites.GetList().at(i).SetMTData().at(j).SetZxx() *= -1.0;
            MTSites.GetList().at(i).SetMTData().at(j).SetZxy() *= -1.0;
            MTSites.GetList().at(i).SetMTData().at(j).SetZyx() *= -1.0;
            MTSites.GetList().at(i).SetMTData().at(j).SetZyy() *= -1.0;
          }
        MTSites.at(i).WriteAsJ(MTSites.GetList().at(i).GetName());
        cout << "    ... done" << endl;
      }
  }
/*@}*/
