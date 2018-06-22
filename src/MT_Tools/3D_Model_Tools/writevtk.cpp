#include <iostream>
#include <string>
#include "ThreeDMTModel.h"
#include "FatalException.h"
#include "Util.h"
#include <fstream>

using namespace std;
using namespace gplib;

string version = "$Id: writevtk.cpp 1849 2010-05-07 11:53:45Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file writevtk.cpp
 * Write a 3D model from WInGLink or Mackie to a .vtk file for plotting with paraview or visit.
 */


int main(void)
  {
    cout
        << " This is writevtk, convert Mackie or WinGlink model files to vtk format for display"
        << endl;
    cout
        << " Output format is legacy VTK format, ending '.vtk' is appended to output"
        << endl;
    cout << " This is Version: " << version << endl << endl;
    ThreeDMTModel Model;
    string infilename, outfilename;

    int mode;
    //get the name of the model file and which format it is stored in
    infilename = AskFilename("Modelfile: ");
    cout << "Type 1 for old Mackie, 2 for Winglink: ";
    cin >> mode;
    //the start of the name of the output files
    cout << "Outfile root: ";
    cin >> outfilename;
    try
      {
        //read in the model in the specified format
        if (mode == 1)
          Model.ReadMackie(infilename);
        else
          Model.ReadWinGLink(infilename);
        //write .vtk and netcdf files for the whole model
        Model.WriteVTK(outfilename + ".vtk");
        Model.WriteNetCDF(outfilename + ".nc");
      } catch (const FatalException &e)
      {
        cerr << e.what() << endl;
      }
  }
/*@}*/
