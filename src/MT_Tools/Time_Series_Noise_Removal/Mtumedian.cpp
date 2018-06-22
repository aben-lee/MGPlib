#include <iostream>
#include <string>
#include <numeric>
#include "statutils.h"
#include "TimeSeriesData.h"
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: ";

int main(int argc, char *argv[])
  {
    string infilename;
    size_t seglength = 0;
    if (argc == 2)
      {
        Document opt;
               char* buffer = argv[1];
               if(opt.Parse(buffer).HasParseError())
               {
                   FILE *fp = fopen(argv[1], "rb");
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

                   assert(opt["seglength"].IsInt());
                   seglength = opt["seglength"].GetInt();
               }
               free(buffer);      // 释放json内存
      }
    else
      {
        cout
            << "This is mtumedian: Apply a median filter to  Phoenix time series"
            << endl << endl;
        cout << " Usage:      mtumedian infilename " << endl;
        cout << " Ending '.med'  will be automatically assigned to outfilename"
            << endl << endl;
        cout << " This is Version: " << version << endl << endl;
        cout << " Mtu-Filename: ";
        cin >> infilename;

        cout << "Segment length for Median: ";
        cin >> seglength;
      }


    TimeSeriesData Data;

    Data.GetData(infilename);
    size_t datalength = Data.GetData().GetEx().GetData().size();
    for (size_t i = seglength / 2; i < datalength - seglength / 2; ++i)
      {
        const size_t startindex = i - seglength / 2;
        const size_t endindex = i + seglength / 2;
        Data.GetData().GetEx().GetData().at(i) = Median(
            Data.GetData().GetEx().GetData().begin() + startindex,
            Data.GetData().GetEx().GetData().begin() + endindex);
        Data.GetData().GetEx().GetData().at(i) = Median(
            Data.GetData().GetEy().GetData().begin() + startindex,
            Data.GetData().GetEy().GetData().begin() + endindex);
        Data.GetData().GetEx().GetData().at(i) = Median(
            Data.GetData().GetHx().GetData().begin() + startindex,
            Data.GetData().GetHx().GetData().begin() + endindex);
        Data.GetData().GetEx().GetData().at(i) = Median(
            Data.GetData().GetHy().GetData().begin() + startindex,
            Data.GetData().GetHy().GetData().begin() + endindex);
      }
    Data.WriteAsMtu(infilename + ".med");
  }
