#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <numeric>
#include "TimeSeriesData.h"
#include "StackedSpectrum.h"
#include "WFunc.h"
#include <boost/bind.hpp>
#include <rapidjson/document.h>

using namespace std;
using namespace gplib;
using namespace rapidjson;

/*
{
	 "infilename" : "D:\\Qt\\MGPLib\\bin\\1255",
	 "outfilename" : "D:\\Qt\\MGPLib\\bin\\1255",
	 "search" : "a"
}
*/

string version = "$Id: DelayFilter.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

void SubShiftedComponent(vector<double> &Original, vector<double> &Shifted,
    const int shiftsteps)
  {
    transform(Original.begin(), Original.end() - shiftsteps, Shifted.begin()
        + shiftsteps, Original.begin(), minus<double> ());
    const double factor = 1. / sqrt(2.);
    transform(Original.begin(), Original.end(), Original.begin(), boost::bind(
        multiplies<double> (), _1, factor));
  }

void FindSpikeDistances(const vector<double> &ts)
  {
    const int blocklength = 2400;
    const int nsegments = ts.size() / blocklength;
    const double threshold = 1e4;
    double spikedist = 0;
    int spikecount = 0;
    vector<double>::const_iterator currstart(ts.begin()), currend(ts.begin()
        + blocklength);
    vector<double> differences(blocklength, 0.0);
    for (int i = 0; i < nsegments; ++i)
      {
        adjacent_difference(currstart, currend, differences.begin());
        vector<double>::iterator firstspike = find_if(differences.begin(),
            differences.end(), boost::bind(greater<double> (), boost::bind(
                (double(*)(double)) &abs, _1), threshold)); //find first with absolute difference greater threshold
        vector<double>::iterator nextspike = firstspike;
        while (nextspike != differences.end())
          {
            nextspike = find_if(firstspike + 1, differences.end(), boost::bind(
                greater<double> (), boost::bind((double(*)(double)) &abs, _1),
                threshold)); //find first with absolute difference greater threshold
            if (nextspike != currend)
              {
                spikedist += distance(firstspike, nextspike);
                ++spikecount;
              }
            firstspike = nextspike;
          }
        currstart += blocklength;
        currend += blocklength;
      }
    cout << "Spike count: " << spikecount << " Avg. Dist: " << spikedist
        / spikecount << endl;
  }

int main(int argc, char *argv[])
  {
    TimeSeriesData OriginalData, ShiftedData;

    string infilename, outfilename, search;
    int seglength = 2400;
    double freqstep;
    int startindex, endindex, maxindex = 0;
    const double searchstart = 0.2;
    const double searchend = 1.0;
    double absmax = 0;
    int shiftsteps;

	try
    {
        if(argc != 2)
        {
			cout << "This is dfilter: Apply a delay filter to MT time series file"
				<< endl << endl;
			cout << "At this point no command line parameters, only interactive."
				<< endl << endl;
			cout << "This is Version: " << version << endl << endl;

			cout << "Input Filename: ";
			cin >> infilename;
			OriginalData.GetData(infilename);
			cout << "Output Filename: ";
			cin >> outfilename;
			cout << " Enter 'a' for automatic, or number of points to shift: ";
			cin >> search;
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
                assert(opt.IsObject());   // Document is a JSON value represents the root of DOM. Root can be either an object or array.

                assert(opt.HasMember("infilename"));
                assert(opt["infilename"].IsString());
                infilename = opt["infilename"].GetString();
				
				assert(opt.HasMember("outfilename"));
                assert(opt["outfilename"].IsString());
                outfilename = opt["outfilename"].GetString();

				assert(opt.HasMember("search"));
                assert(opt["search"].IsString());
                search = opt["search"].GetString();
            }
            free(buffer);      // 释放json内存			
		}
		freqstep = OriginalData.GetData().GetSamplerate() * 1. / seglength;
		if (search == "a")
		  {
			vector<complex<double> > ExSpectrum(seglength / 2 + 1);

			cout << "Performing search" << endl;
			FindSpikeDistances(OriginalData.GetData().GetEx().GetData());
			StackedSpectrum(OriginalData.GetData().GetEx().GetData().begin(),
				OriginalData.GetData().GetEx().GetData().end(), ExSpectrum.begin(),
				seglength, Hanning());

			startindex = round(searchstart / freqstep);
			endindex = round(searchend / freqstep);
			for (int i = startindex; i < endindex; ++i)
			  {
				if (abs(ExSpectrum.at(i)) > absmax)
				  {
					maxindex = i;
					absmax = abs(ExSpectrum.at(i));
				  }
			  }
			shiftsteps = round(OriginalData.GetData().GetSamplerate() / (maxindex
				* freqstep)) - 1;
			cout << "Spike frequency: " << maxindex * freqstep << " Height: "
				<< absmax << endl;
		  }
		else
		  {
			istringstream convStream(search);
			convStream >> shiftsteps;
			maxindex = OriginalData.GetData().GetSamplerate() / (shiftsteps
				* freqstep);
		  }

		cout << "Shifted by: " << shiftsteps << " exact: "
			<< OriginalData.GetData().GetSamplerate() / (maxindex * freqstep)
			<< endl;
		ShiftedData = OriginalData;

		SubShiftedComponent(OriginalData.GetData().GetEx().GetData(),
			ShiftedData.GetData().GetEx().GetData(), shiftsteps);
		SubShiftedComponent(OriginalData.GetData().GetEy().GetData(),
			ShiftedData.GetData().GetEy().GetData(), shiftsteps);
		SubShiftedComponent(OriginalData.GetData().GetHx().GetData(),
			ShiftedData.GetData().GetHx().GetData(), shiftsteps);
		SubShiftedComponent(OriginalData.GetData().GetHy().GetData(),
			ShiftedData.GetData().GetHy().GetData(), shiftsteps);
		SubShiftedComponent(OriginalData.GetData().GetHz().GetData(),
			ShiftedData.GetData().GetHz().GetData(), shiftsteps);

		OriginalData.WriteAsMtu(outfilename);
		return 0;		
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
