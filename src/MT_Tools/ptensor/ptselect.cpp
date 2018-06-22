#include <grace_np.h>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/convenience.hpp"
#include <iostream>
#include <string>
#include "PTensorMTStation.h"
#include "Util.h"

namespace fs = boost::filesystem;
using namespace std;
using namespace gplib;

int main(int argc, char* argv[])
  {
    PTensorMTStation Data;

    string version = "$Id: ptselect.cpp 1870 2011-04-01 11:55:47Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout
        << " Display all phase tensor files in a directory and select good and bad ones "
        << endl;
    cout << " Files are identified by file ending '.ptensor' " << endl;
    cout << " Type 'g' for good or 'b' for bad after data is displayed "
        << endl;
    cout << endl << endl;

    //if they do not exist,
    //we create two directories, baddir for the files we sort out
    //and gooddir for the files we want to use
    const std::string baddir = "bad";
    const std::string gooddir = "good";
    if (!fs::exists(baddir))
      fs::create_directory(baddir);
    if (!fs::exists(gooddir))
      fs::create_directory(gooddir);
    fs::path full_path(fs::initial_path());

    if (!fs::exists(full_path))
      {
        std::cout << "\nNot found: " << full_path
            << std::endl;
        return 1;
      }
    //we compare all data with the data from one site
    //this makes it easier to see differences and similarities
    std::string mastersite = AskFilename("Enter site for permanent display: ");
    //initialize xmgrace which we use for displaying the data
    if (GraceOpen(2048) == -1)
      {
        fprintf(stderr, "Can't run Grace. \n");
        exit(EXIT_FAILURE);
      }
    fs::directory_iterator end_iter;
    std::string response;
    Data.GetData(mastersite);
    //plot phase tensor elements for master site
    for (unsigned int i = 0; i < Data.GetTensor().size() && GraceIsOpen(); i++)
      {
        GracePrintf("g0.s0 point %f, %f", 1. / Data.at(i).GetFrequency(),
            Data.at(i).GetPhi11());
        GracePrintf("g0.s1 point %f, %f", 1. / Data.at(i).GetFrequency(),
            Data.at(i).GetPhi12());
        GracePrintf("g0.s2 point %f, %f", 1. / Data.at(i).GetFrequency(),
            Data.at(i).GetPhi21());
        GracePrintf("g0.s3 point %f, %f", 1. / Data.at(i).GetFrequency(),
            Data.at(i).GetPhi22());
      }
    GracePrintf("xaxes scale logarithmic");
    GracePrintf("autoscale");
    GracePrintf("redraw");
    cin >> response;
    //plot the other elements
    for (fs::directory_iterator dir_itr(full_path); //for all files in current directory
    dir_itr != end_iter; ++dir_itr)
      {
        if (extension(*dir_itr) == ".ptensor")
          {
            std::string currentname(dir_itr->path().filename().string());
            Data.GetData(currentname);
            for (unsigned int i = 0; i < Data.GetTensor().size()
                && GraceIsOpen(); i++)
              {
                GracePrintf("g0.s4 point %f, %f", 1.
                    / Data.at(i).GetFrequency(), Data.at(i).GetPhi11());
                GracePrintf("g0.s5 point %f, %f", 1.
                    / Data.at(i).GetFrequency(), Data.at(i).GetPhi12());
                GracePrintf("g0.s6 point %f, %f", 1.
                    / Data.at(i).GetFrequency(), Data.at(i).GetPhi21());
                GracePrintf("g0.s7 point %f, %f", 1.
                    / Data.at(i).GetFrequency(), Data.at(i).GetPhi22());
              }

            GraceCommand(("title \" " + currentname + " \" ").c_str());
            GracePrintf("redraw");
            std::cin >> response;

            if (response == "b")
              fs::rename(currentname, baddir);
            else if (response == "g")
              fs::rename(currentname, gooddir);
            else
              cout << "Invalid reply, ignoring file !" << endl;
            GracePrintf("KILL g0.s4");
            GracePrintf("KILL g0.s5");
            GracePrintf("KILL g0.s6");
            GracePrintf("KILL g0.s7");
            //GraceFlush();
          }

      }
    if (GraceIsOpen())
      GraceClose();
  }
