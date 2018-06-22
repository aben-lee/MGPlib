
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <numeric>
#include "Util.h"
#include "TimeSeriesData.h"
#include "statutils.h"
#include "FilterFunc.h"
#include "FatalException.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

using namespace std;
using namespace gplib;
using namespace rapidjson;

/*
 * {
 *      "infilename" : "....",
 *      "outfilename" : "....",
 *      "lowfreq"   : 0.1 ,
 *      "upfreq"    : 2,
 *      "npass"     : 1
 * }
*/
string version = "$Id: mtubandpass.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Apply a band pass filter to each component of the MT time series. The program
 * asks for the corner frequencies in Hz and the number of passes for the filter.
 * The output filename is determined by appending .fil to the input filename.
 */

int main(int argc, char *argv[])
  {
    string infilename;
    string outfilename;
    double lowfreq;
    double upfreq;
    // the more passes we do with this filter, the stronger the attenuation
    size_t npass = 1;

    try
    {
        if( argc != 2 )
        {
            cout << "This is mtufilter: Apply a band pass filter to MT time series"
                << endl << endl;
            cout << " Usage:      mtufilter infilename " << endl;
            cout << " Ending '.fil'  will be automatically assigned to outfilename"
                << endl << endl;
            cout << " This is Version: " << version << endl << endl;

            infilename = AskFilename(" Mtu-Filename: ");

            // get the lower corner frequency
            cout << "Lower Corner frequency [Hz]: ";
            cin >> lowfreq;

            // get the lower corner frequency
            cout << "Upper Corner frequency [Hz]: ";
            cin >> upfreq;

            cout << "Number of passes: ";
            cin >> npass;

            outfilename = AskFilename("Out-Filename: ");

        }
        else
        {
            // Read a JSON schema from file into Document
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

                assert(opt.HasMember("infilename"));
                assert(opt["infilename"].IsString());
                infilename = opt["infilename"].GetString();

                assert(opt.HasMember("outfilename"));
                assert(opt["outfilename"].IsString());
                outfilename = opt["outfilename"].GetString();

                assert(opt["lowfreq"].IsNumber());   // Number is a JSON type, but C++ needs more specific type.
//                assert(opt["lowfreq"].IsDouble());
                lowfreq = opt["lowfreq"].GetDouble(); // Alternative (double)document["lowfreq"]

                assert(opt["upfreq"].IsNumber());
//                assert(opt["upfreq"].IsDouble());
                upfreq = opt["upfreq"].GetDouble();

                assert(opt["npass"].IsNumber());
                assert(opt["npass"].IsInt());   // In this case, IsUint()/IsInt64()/IsUInt64() also return true.
                npass = opt["npass"].GetInt();
            }
            free(buffer);      // 释放json内存
        }

        cout << "Processing..." << endl;

        TimeSeriesData Data;
        Data.GetData(infilename);

        // calculate the dimensionless corner frequency for the filtering class
        const double lowfilfreq = lowfreq * Data.GetData().GetEx().GetSamplerate();
        const double upfilfreq = upfreq * Data.GetData().GetEx().GetSamplerate();
        // the more passes we do with this filter, the stronger the attenuation

        // make sure the all components have zero mean
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

        //we can do several passes of the filter to get strong attenuation of high frequencies
        for (size_t i = 0; i < npass; ++i)
          {
            // apply the filter to one component and store the result in that component
            transform(Data.GetData().GetEx().GetData().begin(),
                Data.GetData().GetEx().GetData().end(),
                Data.GetData().GetEx().GetData().begin(), SimpleBp(lowfilfreq,upfilfreq));
            transform(Data.GetData().GetEy().GetData().begin(),
                Data.GetData().GetEy().GetData().end(),
                Data.GetData().GetEy().GetData().begin(), SimpleBp(lowfilfreq,upfilfreq));
            transform(Data.GetData().GetHx().GetData().begin(),
                Data.GetData().GetHx().GetData().end(),
                Data.GetData().GetHx().GetData().begin(), SimpleBp(lowfilfreq,upfilfreq));
            transform(Data.GetData().GetHy().GetData().begin(),
                Data.GetData().GetHy().GetData().end(),
                Data.GetData().GetHy().GetData().begin(), SimpleBp(lowfilfreq,upfilfreq));
            transform(Data.GetData().GetHz().GetData().begin(),
                Data.GetData().GetHz().GetData().end(),
                Data.GetData().GetHz().GetData().begin(), SimpleBp(lowfilfreq,upfilfreq));
          }
        // write data in the same format that we read it in
        Data.WriteBack(outfilename);
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
