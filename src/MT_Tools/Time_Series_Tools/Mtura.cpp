#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include "Util.h"
#include "TimeSeriesData.h"
#include "miscfunc.h"
#include "WFunc.h"
#include "statutils.h"
#include <boost/bind.hpp>
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: mtura.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate the a running average for each component of the input file.
 */

int main(int argc, char *argv[])
  {
    string infilename;
    cout << "This is mtura: Calculate a running average of MT time series"
        << endl << endl;
    cout << " Usage:      mtura infilename " << endl;
    cout << " Ending '.ra'  will be automatically assigned to outfilename"
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    try
    {

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

                }
                free(buffer);      // 释放json内存
      }
    else
      {

        infilename = AskFilename(" Mtu-Filename: ");
      }

    TimeSeriesData Data;
    Data.GetData(infilename);

    // get the width of the averaging window from the user
    size_t windowlength;
    cout << "Window length: ";
    cin >> windowlength;

    //construct the window time series
    const size_t tslength = Data.GetData().GetEx().GetData().size();
    TimeSeriesComponent WindowTS;
    // set the time series to zero
    WindowTS.GetData().assign(tslength, 0.0);
    const size_t windowstart = 0;
    // put ones where we want non-zero values
    fill_n(WindowTS.GetData().begin() + windowstart, windowlength, 1.0);
    //and apply the window function
    ApplyWindow(WindowTS.GetData().begin() + windowstart,
        WindowTS.GetData().begin() + windowstart + windowlength,
        WindowTS.GetData().begin() + windowstart, Hanning());
    // normalize,
    //this should be improved
    transform(WindowTS.GetData().begin() + windowstart,
        WindowTS.GetData().begin() + windowstart + windowlength,
        WindowTS.GetData().begin() + windowstart, boost::bind(
            multiplies<double> (), _1, 1. / double(windowlength)));

    // make sure all components have zero mean to avoid offsets after windowing
    SubMean(Data.GetData().GetEx().GetData().begin(),
        Data.GetData().GetEx().GetData().end());
    SubMean(Data.GetData().GetEy().GetData().begin(),
        Data.GetData().GetEy().GetData().end());
    SubMean(Data.GetData().GetHx().GetData().begin(),
        Data.GetData().GetHx().GetData().end());
    SubMean(Data.GetData().GetHy().GetData().begin(),
        Data.GetData().GetHy().GetData().end());
    SubMean(Data.GetData().GetHz().GetData().begin(),
        Data.GetData().GetHz().GetData().end());

    // convolve the averaging time series with all components
    Convolve(Data.GetData().GetEx().GetData(), WindowTS.GetData(),
        Data.GetData().GetEx().GetData());
    Convolve(Data.GetData().GetEy().GetData(), WindowTS.GetData(),
        Data.GetData().GetEy().GetData());
    Convolve(Data.GetData().GetHx().GetData(), WindowTS.GetData(),
        Data.GetData().GetHx().GetData());
    Convolve(Data.GetData().GetHy().GetData(), WindowTS.GetData(),
        Data.GetData().GetHy().GetData());
    Convolve(Data.GetData().GetHz().GetData(), WindowTS.GetData(),
        Data.GetData().GetHz().GetData());

    //correct for the shift introduced by the convolution
    rotate(Data.GetData().GetEx().GetData().begin(),
        Data.GetData().GetEx().GetData().begin() + windowlength / 2,
        Data.GetData().GetEx().GetData().end());
    rotate(Data.GetData().GetEy().GetData().begin(),
        Data.GetData().GetEy().GetData().begin() + windowlength / 2,
        Data.GetData().GetEy().GetData().end());
    rotate(Data.GetData().GetHx().GetData().begin(),
        Data.GetData().GetHx().GetData().begin() + windowlength / 2,
        Data.GetData().GetHx().GetData().end());
    rotate(Data.GetData().GetHy().GetData().begin(),
        Data.GetData().GetHy().GetData().begin() + windowlength / 2,
        Data.GetData().GetHy().GetData().end());
    rotate(Data.GetData().GetHz().GetData().begin(),
        Data.GetData().GetHz().GetData().begin() + windowlength / 2,
        Data.GetData().GetHz().GetData().end());
    Data.WriteBack(infilename + ".ra");
    }

    catch( FatalException& fataException )
           {
               printf( "%s", fataException.what());
           }
           catch ( ... )
           {
               printf( "\nCaught unknown exception\n" );
           }

  }
/*@}*/
