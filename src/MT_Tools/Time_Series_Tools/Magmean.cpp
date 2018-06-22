/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * This program calculates the mean magnetic time series for several MT sites. The user has to input the number of sites and the
 * filename for each site. The program then writes a file 'magmean.out' in birrp ascii format that contains the average Hx,Hy and Hz for the input sites.
 */

#include <iostream>
#include <string>
#include <vector>
#include "TimeSeriesData.h"
#include "Util.h"
#include "convert.h"
#include "rapidjson/document.h"

using namespace std;
using namespace gplib;
using namespace rapidjson;

string version = "$Id: magmean.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*
     nfiles : ?
     ar :

*/

int main(int argc, char *argv[])
  {
    string infilename, outfilename;
    vector<TimeSeriesData> Sites;
    std::string prompt;

    unsigned int nfiles = 0;
try{
        if(argc != 2)
        {
    cout
        << "This is magmean: Calculate the mean magnetic time series from several stations"
        << endl<< endl;
    cout << "Usage: magmean" << endl;
    cout << "There are no command line arguments, only interactive mode"
        << endl<< endl;
    cout << "This is Version: " << version << endl << endl;
    cout << "How many stations: ";
    cin >> nfiles;

    for (unsigned int i = 0; i < nfiles; ++i)
      {

        std::string prompt = "Site File " + stringify(i+1) + " :";
        TimeSeriesData CurrSite;
        infilename = AskFilename(prompt);
        CurrSite.GetData(infilename);
        Sites.push_back(CurrSite);
      }
        }
        else
        {
            Document opt;
                        char* buffer = argv[1];
                        if(opt.Parse(buffer).HasParseError())
                        {
                            FILE *fp = fopen(argv[1], "r");
                            if (!fp) {
                                printf("file '%s' not found\n", argv[1]);
                                return -1;
                            }

                            fseek(fp, 0, SEEK_END);
                            size_t filesize = (size_t)ftell(fp);
                            fseek(fp, 0, SEEK_SET);
                            buffer = (char*)malloc(filesize + 1);
                            size_t readLength = fread(buffer, 1, filesize, fp);
                            buffer[readLength] = '\0';
                            fclose(fp);

                            opt.Parse(buffer);

                        }

                        {
                            printf("Input JSON is valid.\n");
                                            printf("\nAccess values in document:\n");
                                            assert(opt.IsObject());   // Document is a JSON value represents the root of DOM. Root can be either an object or array.



                                            assert(opt.HasMember("outfilename"));
                                            assert(opt["outfilename"].IsString());
                                            outfilename = opt["outfilename"].GetString();

                                            const Value& a = opt["arr"];
                                            assert(a.IsArray());

                        for (unsigned int i = 0; i < nfiles; ++i)
                          {
                            prompt = "Site File " + stringify(i+1) + a[i].GetString();
                            TimeSeriesData CurrSite;
                            infilename = AskFilename(prompt);
                            CurrSite.GetData(infilename);
                            Sites.push_back(CurrSite);
                          }
                        }
        }

    cout << "Calculating mean ... " << endl;

    for (unsigned int i = 1; i < nfiles; ++i)
      {
        Sites.at(0).GetData().GetHx() += Sites.at(i).GetData().GetHx();
        Sites.at(0).GetData().GetHy() += Sites.at(i).GetData().GetHy();
        Sites.at(0).GetData().GetHz() += Sites.at(i).GetData().GetHz();
      }
    Sites.at(0).GetData().GetHx() *= 1./nfiles;
    Sites.at(0).GetData().GetHy() *= 1./nfiles;
    Sites.at(0).GetData().GetHz() *= 1./nfiles;
    Sites.at(0).WriteAsBirrp("outfilename");
    cout << "... done " << endl;
    }


    catch( FatalException& fataException )
        {
            printf( "%s", fataException.what());
        }
        catch ( ... )
        {
            printf( "\nCaught unknown exception\n" );
        }

        cout << "End" << endl;
        system("pause");
        return 0;

  }
/*@}*/

