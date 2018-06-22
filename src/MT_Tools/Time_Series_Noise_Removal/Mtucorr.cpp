#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ShortCorr.h"
#include "convert.h"
#include "WFunc.h"
#include "TimeSeriesData.h"
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: mtucorr.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

//! Calculate the correlation between the filed component and a spike and write the correlation to a file 
void CalcCorrAndWrite(ttsdata &Data, ttsdata &Short, ttsdata &Corr, string name)
  {
    ofstream outfile(name.c_str());
    ShortCorr(Data.begin(), Data.end(), Short.begin(), Short.end(),
        Corr.begin());
    copy(Corr.begin(), Corr.end(), ostream_iterator<double> (outfile, "\n"));
  }

//! Find the next spike by examining the first difference
void FindNextSpike(ttsdata::iterator &currstart, ttsdata &Data, ttsdata &Spike,
    const int trailpoints, const int decaypoints, const double diffthreshold)
  {
    ttsdata diffdata;
    diffdata.reserve(Data.size());
    adjacent_difference(Data.begin(), Data.end(), back_inserter(diffdata));
    ttsdata::iterator currdiff = diffdata.begin() + distance(Data.begin(),
        currstart) + trailpoints;
    ttsdata::iterator currdata = currstart + trailpoints;
    bool spikefound = false;
    Spike.assign(trailpoints + decaypoints, 0.0);
    while (!spikefound && (currdata + decaypoints < Data.end()))
      {
        if (*currdiff > diffthreshold)
          {
            copy(currdata - trailpoints, currdata + decaypoints, Spike.begin());
            spikefound = true;
            currstart = currdata;
          }
        ++currdiff;
        ++currdata;
      }
  }

//! Remove spikes with the given form from the time-series 
double RemoveSpike(ttsdata &Data, ttsdata &Spike, const double corrthreshold,
    const int minspikeavg, string outname, const size_t iteration)
  {
    ttsdata Corr(Data.size(), 0.0);
    SubMean(Spike.begin(), Spike.end());
    CalcCorrAndWrite(Data, Spike, Corr, outname + stringify(iteration)
        + ".corr");

    ttsdata::iterator datait = Data.begin();
    ttsdata::iterator corrit = Corr.begin();
    const int shortsize = Spike.size();
    double spikecount = 0;
    ttsdata avgspike(Spike.size(), 0.0);
    while (datait + shortsize < Data.end()) //first iteration, create average
      {
        if (*corrit > corrthreshold)
          {
            ttsdata currsegment(datait, datait + shortsize);
            SubMean(currsegment.begin(), currsegment.end());
            transform(currsegment.begin(), currsegment.end(), avgspike.begin(),
                avgspike.begin(), plus<double> ());
            spikecount += 1.0;
          }
        ++datait;
        ++corrit;
      }
    cout << "   No. of spikes before average: " << spikecount << " ";
    if (spikecount < minspikeavg)
      {
        cout << " below threshold of: " << minspikeavg << " not used." << endl;
        return 0.0;
      }
    else
      {
        cout << endl;
        double maxamp = *max_element(avgspike.begin(), avgspike.end());
        transform(avgspike.begin(), avgspike.end(), avgspike.begin(),
            boost::bind(multiplies<double> (), _1, 1. / maxamp)); //normalize maximum
        ofstream avgfile((static_cast<std::string> ("spike") + stringify(
            iteration) + static_cast<std::string> (".avg")).c_str());
        copy(avgspike.begin(), avgspike.end(), ostream_iterator<double> (
            avgfile, "\n"));

        spikecount = 0.0;

        CalcCorrAndWrite(Data, avgspike, Corr, outname + stringify(iteration)
            + ".avg.corr");
        datait = Data.begin();
        corrit = Corr.begin();
        while (datait + shortsize < Data.end()) //second iteration, remove average
          {
            if (*corrit > corrthreshold)
              {
                ttsdata currsegment(datait, datait + shortsize);
                SubMean(currsegment.begin(), currsegment.end());
                double segmaxamp = *max_element(currsegment.begin(),
                    currsegment.end());
                ttsdata avgadjust(avgspike.begin(), avgspike.end());
                transform(avgadjust.begin(), avgadjust.end(),
                    avgadjust.begin(), boost::bind(multiplies<double> (), _1,
                        segmaxamp));
                transform(datait, datait + shortsize, avgadjust.begin(),
                    datait, minus<double> ());
                spikecount += 1.0;
              }
            ++datait;
            ++corrit;
          }
        cout << "   No. of spikes after average: " << spikecount << endl;
      }
    return spikecount;
  }

//! The program mtucorr tries to identify spikes in the electric field of MT time-series data and remove them.
int main(int argc, char *argv[])
  {
    TimeSeriesData TsData;

    string masterfilename, shortfilename;

    double corrthreshold = 0.9;
    double diffthreshold = 10000;
    int trailpoints = 5;
    int decaypoints = 20;
    int iterations = 50;
    int minspikeavg = 10;

    try
    {
        if(argc != 2)
        {

    cout
        << " This is mtucorr: Substract spikeform from a mtu time series for cow-fence denoising"
        << endl << endl;
    cout
        << " Usage      mtucorr   You will have to enter the mtufilename and a number of parameters that determine which spike will be removed"
        << endl;
    cout
        << " The output will have the same name as the Master filename with ending appended"
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    cout << "Time Series filename: ";
    cin >> masterfilename;
    TsData.GetData(masterfilename);
    cout << "Minimum differential spike height: ";
    cin >> diffthreshold;
    cout << "Number of trailing points: ";
    cin >> trailpoints;
    cout << "Number of decay points: ";
    cin >> decaypoints;
    cout << "Minimum correlation: ";
    cin >> corrthreshold;
    cout << "Minimum number of samples in average: ";
    cin >> minspikeavg;
    cout << "Number of Iterations: ";
    cin >> iterations;
    }
    else
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

                        assert(opt.HasMember("masterfilename"));
                        assert(opt["masterfilename"].IsString());
                        masterfilename = opt["masterfilename"].GetString();

                        assert(opt.HasMember("shortfilename"));
                        assert(opt["shortfilename"].IsString());
                        shortfilename = opt["shortfilename"].GetString();

                        assert(opt["corrthreshold"].IsDouble());
                        corrthreshold = opt["corrthreshold"].GetDouble();

                        assert(opt["diffthreshold"].IsDouble());
                        diffthreshold = opt["diffthreshold"].GetDouble();

                        assert(opt["trailpoints"].IsInt());
                        trailpoints = opt["trailpoints"].GetInt();

                        assert(opt["decaypoints"].IsInt());
                        decaypoints = opt["decaypoints"].GetInt();

                        assert(opt["iterations"].IsInt());
                        iterations = opt["iterations"].GetInt();

                        assert(opt["minspikeavg"].IsInt());
                        minspikeavg = opt["minspikeavg"].GetInt();
                       }
                    free(buffer);      // 释放json内存
        }

    ttsdata ShortData;

    ttsdata::iterator currexstart = TsData.GetData().GetEx().GetData().begin();
    ttsdata::iterator curreystart = TsData.GetData().GetEy().GetData().begin();
    ttsdata::iterator currhxstart = TsData.GetData().GetHx().GetData().begin();
    ttsdata::iterator currhystart = TsData.GetData().GetHy().GetData().begin();
    double exspikes = 0;
    double eyspikes = 0;
    for (int i = 0; i < iterations; ++i)
      {
        cout << "Iteration: " << i + 1 << endl;
        cout << " Ex Component" << endl;

        FindNextSpike(currexstart, TsData.GetData().GetEx().GetData(),
            ShortData, trailpoints, decaypoints, diffthreshold);
        exspikes += RemoveSpike(TsData.GetData().GetEx().GetData(), ShortData,
            corrthreshold, minspikeavg, masterfilename, i);
        cout << " Ey Component" << endl;
        FindNextSpike(curreystart, TsData.GetData().GetEy().GetData(),
            ShortData, trailpoints, decaypoints, diffthreshold);
        eyspikes += RemoveSpike(TsData.GetData().GetEy().GetData(), ShortData,
            corrthreshold, minspikeavg, masterfilename, i);
      }
    cout << "Total Spikes removed: " << endl;
    cout << " Ex: " << exspikes << endl;
    cout << " Ey: " << eyspikes << endl;
    ofstream cleanfile((masterfilename + ".ex.clean").c_str());
    copy(TsData.GetData().GetEx().GetData().begin(),
        TsData.GetData().GetEx().GetData().end(), ostream_iterator<double> (
            cleanfile, "\n"));
    TsData.WriteAsMtu(masterfilename + ".clean");
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
