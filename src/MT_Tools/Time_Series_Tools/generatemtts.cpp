//============================================================================
// Name        : generatemtts.cpp
// Author      : May 7, 2010
// Version     : 
// Copyright   : 2010, mmoorkamp
//============================================================================

#include "rapidjson/document.h"
#include "Util.h"
#include "TimeSeriesData.h"
#include "TsSpectrum.h"
#include "WFunc.h"
#include "statutils.h"
#include "C1DMTSynthData.h"

using namespace gplib;
using namespace std;
using namespace rapidjson;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file generatemtts.cpp
 * Generate a synthetic MT times series from a recorded magnetic field
 * and a 1D model.
 */

string version =
    "$Id: generatemtts.cpp 1852 2010-05-20 09:14:53Z mmoorkamp $";

int main(int argc, char *argv[])
  {
    std::string intsname;
    string modelfilename;
    try
    {
        if(argc != 2)
        {
    cout
        << "This is generatemtts: Generate a synthetic MT time series."
        << endl << endl;
    cout << " You will have to input the name of a time series with two magnetic time series\n";
    cout << " and a model file\n";
    cout << " Output will have the same name as the modelfile with _ts.asc appended\n  ";
    cout << " and will contain the magnetic field and an electric field obeying the impedance \n  ";
    cout << " relationship calculate from the 1D model. \n  ";
    cout << " This is Version: " << version << endl << endl;

    intsname = AskFilename(
        "File with magnetic field times series: ");

    modelfilename = AskFilename("Model filename: ");
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

                                            assert(opt.HasMember("intsname"));
                                            assert(opt["intsname"].IsString());
                                            intsname = opt["intsname"].GetString();

                                            assert(opt.HasMember("modelfilename"));
                                            assert(opt["modelfilename"].IsString());
                                            modelfilename = opt["modelfilename"].GetString();
                                        }
                                        free(buffer);      // 释放json内存
                        }

    TimeSeriesData HTsData;
    HTsData.GetData(intsname);

    TsSpectrum SpecCalc;
    const size_t nsamples = HTsData.GetData().GetHx().GetData().size();
    const size_t nfreq = nsamples / 2 + 1;
    cvec HxSpec(nfreq), HySpec(nfreq), ExSpec(nfreq), EySpec(nfreq);

    SubMean(HTsData.GetData().GetHx().GetData().begin(),
        HTsData.GetData().GetHx().GetData().end());
    SubMean(HTsData.GetData().GetHy().GetData().begin(),
        HTsData.GetData().GetHy().GetData().end());

    ApplyWindow(HTsData.GetData().GetHx().GetData().begin(),
        HTsData.GetData().GetHx().GetData().end(),
        HTsData.GetData().GetHx().GetData().begin(), Hamming());
    ApplyWindow(HTsData.GetData().GetHy().GetData().begin(),
        HTsData.GetData().GetHy().GetData().end(),
        HTsData.GetData().GetHy().GetData().begin(), Hamming());

    SpecCalc.CalcSpectrum(HTsData.GetData().GetHx().GetData().begin(),
        HTsData.GetData().GetHx().GetData().end(), HxSpec.begin(), HxSpec.end());
    SpecCalc.CalcSpectrum(HTsData.GetData().GetHy().GetData().begin(),
        HTsData.GetData().GetHy().GetData().end(), HySpec.begin(), HySpec.end());


    C1DMTSynthData Synthetic;
    Synthetic.ReadModel(modelfilename);

    double samplerate = 1.0;
    const double eps = 1e-5;
    const size_t samplelength = nsamples;
    const double freqstep = samplerate / samplelength;
    trealdata frequency;
    frequency.push_back(eps); //zero frequency means not valid so we use a small value for the static
    for (size_t i = 1; i < samplelength / 2 +1; ++i) // add frequencies
      {
        frequency.push_back(freqstep * i);
      }
    Synthetic.SetFrequencies(frequency);//copy them to forward calculation object
    Synthetic.CalcSynthetic();
    for (size_t i = 0; i < nfreq; ++i)
      {
        ExSpec(i) = Synthetic.at(i).GetZxy() * HySpec(i);
        EySpec(i) = Synthetic.at(i).GetZyx() * HxSpec(i);
      }
    SpecCalc.CalcTimeSeries(ExSpec.begin(), ExSpec.end(),
        HTsData.GetData().GetEx().GetData().begin(),
        HTsData.GetData().GetEx().GetData().end());
    SpecCalc.CalcTimeSeries(EySpec.begin(), EySpec.end(),
        HTsData.GetData().GetEy().GetData().begin(),
        HTsData.GetData().GetEy().GetData().end());

    HTsData.WriteAsBirrp(modelfilename+"_ts.asc");

    }

        catch( FatalException& fataException )
            {
                printf( "%s", fataException.what());
            }
            catch ( ... )
            {
                printf( "\nCaught unknown exception\n" );
            }

    system("pause");
    return 0;
  }
/*@}*/
