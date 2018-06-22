#include <iostream>
#include <string>
#include <iterator>
#include <gplib/Util>
#include <gplib/MTStation>
#include <gplib/PTensorMTStation>
#include <gplib/C1DAnisoMTSynthData>

using namespace std;
using namespace gplib;

int main(int argc, char *argv[])
  {
    try
      {
        if (argc == 1) //if we have no additional command line arguments, output some info

          {
            string version =
                "$Id: anisomt.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";
            cout << endl << endl;
            cout << "Program " << version << endl;
            cout
                << "Calculates 1D MT Responses with Anisotropy from input models "
                << endl;
            cout << "Based on Pek and Santos code. " << endl;
            cout << "You can give up to 3 command line parameters: " << endl;
            cout << "  anisomt modelfilename outfilebase masterfile " << endl
                << endl;
            cout
                << "  Modelfilename: The name of the file containing the model"
                << endl << endl;
            cout
                << "  Outfilebase: The name of the outputfiles without ending,"
                << endl;
            cout
                << "  the code will produce 2 files with additional endings .mtt and .ptensor"
                << endl << endl;
            cout
                << "  Masterfile: A regular MT data file, the frequencies in this files "
                << endl;
            cout
                << "  will be used as the frequencies for the forward calculation "
                << endl << endl;
            cout
                << "If not command line parameters are given the program will ask for the first two parameters"
                << endl;
            cout << "and use a standard set of frequencies. " << endl << endl;
          }

        C1DAnisoMTSynthData Synthetic; // create Object for Calculation of Synthetics

        string modelfilename, mttfilename;

        if (argc > 1) // if we have at least one additional command line parameter

          {
            modelfilename = argv[1]; // interpret the first one as a model file name
          }
        else //ask for model file interactively

          {
            modelfilename = AskFilename("Model filename: ");
          }

        Synthetic.ReadModel(modelfilename); // read in model
        if (argc > 2)//if we have at least two command line parameters

          {
            mttfilename = argv[2]; //interpret the second one as the name of the output file
          }
        else
          {
            cout << "Output Format is .mtt ! Do not append ending. " << endl;
            mttfilename = AskFilename("Output Filename: ");
          }
        if (argc > 3) //if we have 3 command line parameters

          {
            MTStation Masterfile(argv[3]); //read data from filename 
            Synthetic.SetFrequencies(Masterfile.GetFrequencies()); //set the calculation frequencies to master frequencies
          }
        Synthetic.GetData(); // Calculate Model
        Synthetic.WriteAsMtt(mttfilename); // Write out Mtt file
        PTensorMTStation Tensor;
        Tensor = Synthetic;
        Tensor.WriteData(mttfilename);
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      } catch (...)
      {
        cerr << "Fatal Error, aborting !" << endl;
        return 100;
      }
  }
