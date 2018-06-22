#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>
#include "ApplyFilter.h"
#include "Adaptors.h"
//#include "NetCDFTools.h"
#include "NeuralNetwork.h"
#include "TimeSeriesData.h"
#include <rapidjson/document.h>

using namespace std;
using namespace gplib;
using namespace rapidjson;

/*
{
	 "tsfilename" : "D:\\Qt\\MGPLib\\bin\\1255",
	 "noisefilename" : "D:\\Qt\\MGPLib\\bin\\1255",
}
*/

string version = "$Id: mtunn.cpp 1838 2010-03-04 16:19:34Z mmoorkamp $";

void Restore(const TimeSeriesComponent &Input, TimeSeriesComponent &Output,
    const double factor)
  {
    transform(Input.GetData().begin(), Input.GetData().end(),
        Output.GetData().begin(),
        boost::bind(multiplies<double> (), _1, factor));
  }

double Normalize(TimeSeriesComponent &Component)
  {
    double themax = *max_element(Component.GetData().begin(),
        Component.GetData().end(), gplib::absLess<double, double>());
    double factor = 1. / themax;
    transform(Component.GetData().begin(), Component.GetData().end(),
        Component.GetData().begin(), boost::bind(multiplies<double> (), _1,
            factor));
    return themax;
  }

void GetNNSetup(const size_t filterlength, const size_t hiddenlayers,
    const size_t ntimeseries, NeuralNetwork::ttypeArray &NNLayers,
    double &NNmaxinit)
  {
    NeuralNetwork::ttypeVector typeVector(filterlength,
        SigmoidalNeuron::bipolar); // we want filterlength number of bipolar neurons per hidden layer
    for (size_t i = 0; i < hiddenlayers; ++i) //intialize the type array for the hidden layers
      {
        NNLayers.push_back(typeVector); // all layers are the same, so we copy the same vector there
      }
    typeVector.assign(1, SigmoidalNeuron::identity);
    NNLayers.push_back(typeVector); // and then we add it to the type Array
  }

namespace po = boost::program_options;

int main(int argc, char *argv[])
  {
    cout << "This is mtunn: Perform neural network filtering on MT time-series"
        << endl << endl;
    cout
        << " The program will ask for reference and input filename, further settings are read from 'mtuadaptive.conf' "
        << endl;
    cout
        << " Output will be 1 Phoenix format file with ending '.clean'  where all channels are overwritten"
        << endl;
    cout
        << " Network weights are stored in a file with ending '.weights.nc' and network topology in '.dot"
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    int filterlength = 0, shift = 0, hiddenlayers;
    double mu, alpha;

    po::options_description desc("General options");
    desc.add_options()("help", "produce help message")("filterlength",
        po::value<int>(&filterlength)->default_value(10),
        "The length of the adaptive filter")("shift",
        po::value<int>(&shift)->default_value(0),
        "The shift in samples between the time series")("mu",
        po::value<double>(&mu)->default_value(1.0),
        "Stepsize for LMS adaptive filter")("alpha", po::value<
            double>(&alpha)->default_value(1.0), "")("hiddenlayers", po::value<int>(
        &hiddenlayers)->default_value(1),
        "The number of hiddenlayers for the neural network");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
      {
        std::cout << desc << "\n";
        return 1;
      }

    TimeSeriesData InputData, ReferenceData;
    string tsfilename, noisefilename;

	try
    {
        if( argc != 2 )
        {
			cout << "Reference Data: ";
			cin >> noisefilename;
			cout << "Input Time Series Filename: ";
			cin >> tsfilename;			
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

                assert(opt.HasMember("noisefilename"));
                assert(opt["noisefilename"].IsString());
                noisefilename = opt["noisefilename"].GetString();

                assert(opt.HasMember("tsfilename"));
                assert(opt["tsfilename"].IsString());
                tsfilename = opt["tsfilename"].GetString();
            }
            free(buffer);      // 释放json内存
		}
		ReferenceData.GetData(noisefilename);
		InputData.GetData(tsfilename);

		cout << "Input Start time: " << InputData.GetData().GetTime().front()
			<< endl;
		cout << "Reference Start time: "
			<< ReferenceData.GetData().GetTime().front() << endl;
		if (InputData.GetData().GetTime().front()
			!= ReferenceData.GetData().GetTime().front())
		  {
			cerr << "Time series not synchronized !" << endl;
			return 100;
		  }
		int lengthdiff = ReferenceData.GetData().Size()
			- InputData.GetData().Size();
		if (lengthdiff > 0)
		  {
			cout << "Removing " << lengthdiff
				<< " datapoints from Reference time-series." << endl;
			ReferenceData.GetData().erase(ReferenceData.GetData().Size()
				- lengthdiff, ReferenceData.GetData().Size());
		  }
		if (lengthdiff < 0)
		  {
			cout << "Removing " << lengthdiff
				<< " datapoints from Input time-series." << endl;
			InputData.GetData().erase(InputData.GetData().Size() + lengthdiff,
				InputData.GetData().Size());
		  }
		cout << "Input End time: " << InputData.GetData().GetTime().back() << endl;
		cout << "Reference End time: " << ReferenceData.GetData().GetTime().back()
			<< endl;

		NeuralNetwork::ttypeArray NNLayers;
		double NNmaxinit = 1.0;
		const int ntimeseries = 4;
		GetNNSetup(filterlength, hiddenlayers, ntimeseries, NNLayers, NNmaxinit);
		NeuralNetwork NN(filterlength, ntimeseries, mu, NNLayers, NNmaxinit, true);
		NN.SetAlpha(alpha);

		ApplyFilter Canceller(NN, true);

		double rexmax = Normalize(ReferenceData.GetData().GetEx());
		double reymax = Normalize(ReferenceData.GetData().GetEy());
		double rhxmax = Normalize(ReferenceData.GetData().GetHx());
		double rhymax = Normalize(ReferenceData.GetData().GetHy());

		Canceller.AddReferenceChannel(ReferenceData.GetData().GetHx());
		Canceller.AddReferenceChannel(ReferenceData.GetData().GetHy());
		Canceller.AddReferenceChannel(ReferenceData.GetData().GetEx());
		Canceller.AddReferenceChannel(ReferenceData.GetData().GetEy());

		double ihxmax = Normalize(InputData.GetData().GetHx());
		double ihymax = Normalize(InputData.GetData().GetHy());
		Canceller.AddInputChannel(InputData.GetData().GetHx());
		Canceller.AddInputChannel(InputData.GetData().GetHy());

		Canceller.SetWeightSaveIntervall(1000);
		Canceller.SetShift(shift);
		Canceller.ShowProgress(true);
		ofstream weightfile((noisefilename + "weights").c_str());
		NN.PrintWeights(weightfile);
		cout << " First iteration: " << endl << endl;

		Canceller.FilterData();
		NN.PrintWeights(weightfile);
		cout << endl << endl << " Second iteration: " << endl << endl;

		Canceller.FilterData();
		NN.PrintWeights(weightfile);

		Restore(*Canceller.GetOutChannels().at(0).get(),
			ReferenceData.GetData().GetHx(), rhxmax);
		Restore(*Canceller.GetOutChannels().at(1).get(),
			ReferenceData.GetData().GetHy(), rhymax);
		Restore(*Canceller.GetOutChannels().at(2).get(),
			ReferenceData.GetData().GetEx(), rexmax);
		Restore(*Canceller.GetOutChannels().at(3).get(),
			ReferenceData.GetData().GetEy(), reymax);
		ReferenceData.WriteBack(noisefilename + ".clean");

		//ofstream epsfile((noisefilename+".eps").c_str());
		//copy(Canceller.GetEpsValues().front().begin(),Canceller.GetEpsValues().front().end(),ostream_iterator<double>(epsfile,"\n"));

		//WriteMatrixAsNetCDF(noisefilename+".weights.nc",Canceller.GetWeightHistory());
		//NN.PrintTopology(noisefilename+".dot");		
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
