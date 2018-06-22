#include <iostream>
#include <string>
#include "Util.h"
#include "TimeSeriesData.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Cut a MT time series to a given number of points and (optionally) shift the beginning 
 * by some points.  
 */

string version = "$Id: mtucut.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

int main(int argc, char *argv[])
  {
    string infilename;
    size_t newlength, startindex;

    cout << "This is mtucut: Cut Phoenix time series to a given length" << endl
        << endl;
    cout
        << "Ending .cut + ending [ts3,ts4,ts5] will be automatically assigned to outfilename"
        << endl << endl;
    cout << "This is Version: " << version << endl << endl;

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
        infilename = AskFilename("Mtu-Filename: ");
      }

    TimeSeriesData Data;
    Data.GetData(infilename);
    cout << "Old length: " << Data.GetData().GetEx().GetData().size() << endl;
    cout << "Old Start time: " << Data.GetData().GetTime().front() << endl;
    cout << "Old End time: " << Data.GetData().GetTime().back() << endl;
    cout << "New length: ";
    cin >> newlength;
    cout << "Startindex: ";
    cin >> startindex;

    const size_t length = Data.GetData().GetEx().GetData().size();
    if (newlength + startindex > length)
      {
        cerr << "Selected segment is partially outside time series !";
        return 100;
      }
    else
      {
        // remove the data at the beginning that is not needed any more
        Data.GetData().erase(0, startindex);
        //remove the data at the end, that is not needed any more
        Data.GetData().erase(Data.GetData().Size() - (Data.GetData().Size()
            - newlength), Data.GetData().Size());
        Data.WriteAsMtu(infilename + ".cut");
      }

    cout << "New Start time: " << Data.GetData().GetTime().front() << endl;
    cout << "New End time: " << Data.GetData().GetTime().back() << endl;

  }
/*@}*/
