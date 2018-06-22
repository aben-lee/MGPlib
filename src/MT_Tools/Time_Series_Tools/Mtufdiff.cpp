#include <iostream>
#include <string>
#include <numeric>
#include "Util.h"
#include "TimeSeriesData.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
using namespace gplib;
string version = "$Id: mtu2birrp.cpp 651 2006-10-10 14:46:53Z max $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate the first difference for all components of a MT time-series. 
 */

int main(int argc, char *argv[])
  {
    string infilename;
    if (argc == 2)
      {
        Document opt;
                char* buffer = argv[1];
                if(opt.Parse(buffer).HasParseError())
                {
                    FILE *fp = fopen(argv[1], "r");
                    if (!fp)
                    {
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

                    assert(opt.HasMember("infilename"));
                    assert(opt["infilename"].IsString());
                    infilename = opt["infilename"].GetString();
                }
                free(buffer);      // 释放json内存
      }
    else
      {
        cout
            << "This is mtufdiff: Calculate first difference of  Phoenix time series"
            << endl << endl;
        cout << " Usage:      mtufdiff infilename " << endl;
        cout
            << " Ending '.fdiff'  will be automatically assigned to outfilename"
            << endl << endl;
        cout << " This is Version: " << version << endl << endl;
        infilename = AskFilename(" Mtu-Filename: ");
      }

    TimeSeriesData Data;

    Data.GetData(infilename);
    adjacent_difference(Data.GetData().GetEx().GetData().begin(),
        Data.GetData().GetEx().GetData().end(),
        Data.GetData().GetEx().GetData().begin());
    adjacent_difference(Data.GetData().GetEy().GetData().begin(),
        Data.GetData().GetEy().GetData().end(),
        Data.GetData().GetEy().GetData().begin());
    adjacent_difference(Data.GetData().GetHx().GetData().begin(),
        Data.GetData().GetHx().GetData().end(),
        Data.GetData().GetHx().GetData().begin());
    adjacent_difference(Data.GetData().GetHy().GetData().begin(),
        Data.GetData().GetHy().GetData().end(),
        Data.GetData().GetHy().GetData().begin());
    Data.WriteBack(infilename + ".fdiff");
  }
/*@}*/
