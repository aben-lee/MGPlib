#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include "statutils.h"
#include "Util.h"

using namespace std;
using namespace gplib;
/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Find the model from the .final output file of 1dinvga with minimal squared sum of objective functions.
 * The current version assumes 4 objective functions. 
 */

int main(int argc, char *argv[])
  {
    string infilename, outfilename;
    string version =
        "$Id: sumobjective.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Sum up the objective function values as output by the Pareto-GA"
        << endl;
    cout << "and find the model with smallest distance from origin. " << endl;
    cout
        << "The program expects a file that contains exactly 4 objective function values per line. "
        << endl;
    cout << "If your program output differs, you have to adjust your file.  "
        << endl;
    cout
        << "The name of the output file is the same is the inputfile + .sum.  "
        << endl;
    if (argc > 1)
      {
        infilename = argv[1];
      }
    else
      {
        infilename = AskFilename("Infile name:");
      }

    outfilename = infilename + ".sum";

    ifstream objfile(infilename.c_str());
    vector<double> objvalues;
    copy(istream_iterator<double> (objfile), istream_iterator<double> (),
        back_inserter(objvalues));

    if ((objvalues.size() % 4) != 0)
      {
        cerr << "Not 4 objective function values ! " << endl;
        return 100;
      }
    size_t index = 0;
    vector<double> sumvalues, first, second, third, fourth;
    ofstream sumfile(outfilename.c_str());
    while (index <= objvalues.size() - 4)
      {
        first.push_back(objvalues.at(index));
        second.push_back(objvalues.at(index + 1));
        third.push_back(objvalues.at(index + 2));
        fourth.push_back(objvalues.at(index + 3));
        index += 4;
      }
    //	double firstmean = Mean(first.begin(),first.end());
    //	double secondmean = Mean(second.begin(),second.end());
    //	double thirdmean = Mean(third.begin(),third.end());
    //	double fourthmean = Mean(fourth.begin(),fourth.end());

    for (size_t i = 0; i < first.size(); ++i)
      {
        double sum = 0;
        sum = pow(first.at(i), 2) + pow(second.at(i), 2) + pow(third.at(i), 2)
            + pow(fourth.at(i), 2);
        sumvalues.push_back(sum / 4);
        sumfile << i << " " << sum / 4 << endl;
      }

    vector<double>::iterator minref = min_element(sumvalues.begin(),
        sumvalues.end());
    index = distance(sumvalues.begin(), minref);
    cout << "Minimum: " << *minref << " at index  " << index << endl;
    cout << "Objective Function values: ";
    for (size_t i = index * 4; i < index * 4 + 4; ++i)
      cout << objvalues.at(i) << " ";
    cout << endl;
    ofstream namefile((infilename + ".name").c_str());
    namefile << "best_" << index << ".mtt";
  }
/*@}*/
