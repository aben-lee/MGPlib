#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "StackedSpectrum.h"
#include "WFunc.h"
#include "TimeSeriesData.h"
#include "Util.h"
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: mtupspec.cpp 1857 2010-11-03 14:55:32Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Calculate the power spectra for the 4 horizontal components in a MT time-series.
 * Output is in ascii format for plotting with xmgrace etc.
 */

//! Calculate the power spectrum and write it to an ascii file
void CalcPSpecAndWrite(ttsdata Data, const double samplerate,
    const int seglength, const string name)
  {
    vector<complex<double> > Spectrum(seglength / 2 + 1);
    StackedSpectrum(Data.begin(), Data.end(), Spectrum.begin(), seglength,
        Hanning());
    ofstream outfile(name.c_str());
    for (unsigned int i = 1; i < Spectrum.size(); ++i) //we do not output the static contribution (0 frequency)
      outfile << i * samplerate / seglength << " " << abs(Spectrum.at(i))
          << endl;
  }

int main(int argc, char *argv[])
  {
    TimeSeriesData TsData;

    string infilename;
    size_t seglength = 2400;
    cout
        << "This is mtupspec: Calculate power spectra from  Phoenix time series"
        << endl << endl;
    cout
        << " Usage      mtupspec filename     if no filename given, the program will ask for one"
        << endl;
    cout << " Output will be 4 ascii file with ending _specex, _specey etc."
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    //get the filename information

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
                    assert(opt.IsObject());

                    assert(opt.HasMember("infilename"));
                    assert(opt["infilename"].IsString());
                   infilename = opt["infilename"].GetString();

                }
                free(buffer);      // 释放json内存
      }
    else
      {
        infilename = AskFilename("Infilename: ");
      }

    //get the length of th individual segments for the fouries transform
    cout << "Length for each segment: ";
    cin >> seglength;
    // we need at least 2 points in each segment
    if (seglength < 2)
      {
        std::cerr << "Segment must be longer than 2 !";
        return 100;
      }
    // the segment length cannot be longer than the time series
    if (seglength > TsData.GetData().GetEx().GetData().size())
      {
        std::cerr << "Segment must shorter than the time series !";
        return 200;
      }
    TsData.GetData(infilename);

    const double samplerate = TsData.GetData().GetSamplerate();
    //calculate the power spectra for each component and write them to a file
    CalcPSpecAndWrite(TsData.GetData().GetEx().GetData(), samplerate,
        seglength, (infilename + "_specex"));
    CalcPSpecAndWrite(TsData.GetData().GetEy().GetData(), samplerate,
        seglength, (infilename + "_specey"));
    CalcPSpecAndWrite(TsData.GetData().GetHx().GetData(), samplerate,
        seglength, (infilename + "_spechx"));
    CalcPSpecAndWrite(TsData.GetData().GetHy().GetData(), samplerate,
        seglength, (infilename + "_spechy"));
    CalcPSpecAndWrite(TsData.GetData().GetHz().GetData(), samplerate,
        seglength, (infilename + "_spechz"));

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
