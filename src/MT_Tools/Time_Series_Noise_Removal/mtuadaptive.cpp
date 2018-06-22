#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>
#include "LMSCanceller.h"
#include "RLSCanceller.h"
#include "AMRLSCanceller.h"
#include "TimeSeriesData.h"
#include "ApplyFilter.h"
//#include "netcdfcpp.h"
#include "NeuralNetwork.h"
#include <rapidjson/document.h>

using namespace std;
using namespace gplib;
using namespace rapidjson;

/*
{
	 "index" : 1 ;
	 "tsfilename" : "",
	 "noisefilename" : "", 
	 " ntimeseries" : ,
	 "filterchoice" : -1
}
*/

string version = "$Id: mtuadaptive.cpp 1838 2010-03-04 16:19:34Z mmoorkamp $";

void GetNNSetup(const size_t filterlength, const size_t hiddenlayers, const size_t ntimeseries,
    NeuralNetwork::ttypeArray &NNLayers, double &NNmaxinit)
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

//void WriteNetCDF(const string name, const boost::numeric::ublas::matrix<double,
//    boost::numeric::ublas::column_major> &Matrix)
//  {
//    NcFile mtrescdf(name.c_str(), NcFile::Replace);
//    NcDim* xd = mtrescdf.add_dim("x", Matrix.size1());
//    NcDim* yd = mtrescdf.add_dim("y", Matrix.size2());
//    NcVar* x = mtrescdf.add_var("x", ncFloat, xd);
//    NcVar* y = mtrescdf.add_var("y", ncFloat, yd);
//    NcVar* z = mtrescdf.add_var("z", ncFloat, xd, yd);
//    float *xvals = new float[xd->size()];
//    float *yvals = new float[yd->size()];
//    float *zvals = new float[xd->size() * yd->size()];
//    for (size_t i = 0; i < Matrix.size1(); ++i)
//      {
//        xvals[i] = i;
//        for (size_t j = 0; j < Matrix.size2(); ++j)
//          {
//            yvals[j] = j;
//            zvals[(Matrix.size1() - 1 - i) * Matrix.size2() + j] = Matrix(i, j);
//          }
//      }
//    x->put(xvals, xd->size());
//    y->put(yvals, yd->size());
//    z->put(zvals, z->edges());
//  }

namespace po = boost::program_options;

int main(int argc, char *argv[])
  {
    cout
        << "This is mtuadaptive: Apply an adaptive filter (LMS or RLS) to cancel noise in MT time series"
        << endl << endl;
    cout
        << " The program will ask for reference and input filename, further settings are read from 'mtuadaptive.conf' "
        << endl;
    cout
        << " Output will be 2 Phoenix format files with ending '.clean' and '.eps' where the chosen channel is overwritten"
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    int filterlength = 0, shift = 0, hiddenlayers;
    double mu, lambda, alpha, delta;

    po::options_description desc("General options");
    desc.add_options()("help", "produce help message")("filterlength",
        po::value<int>(&filterlength)->default_value(10),
        "The length of the adaptive filter")("shift",
        po::value<int>(&shift)->default_value(0),
        "The shift in samples between the time series")("mu",
        po::value<double>(&mu)->default_value(1.0),
        "Stepsize for LMS adaptive filter")("lambda",
        po::value<double>(&lambda)->default_value(1.0), "")("alpha", po::value<
        double>(&alpha)->default_value(1.0), "")("delta", po::value<double>(
        &delta)->default_value(1.0), "")("hiddenlayers",
            po::value<int>(&hiddenlayers)->default_value(1),
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

    int index;
    string tsfilename, noisefilename;

    int ntimeseries;
    AdaptiveFilter *Filter;
    int filterchoice = -1;
	
	try
    {
        if(argc != 2)
        {
			cout << "Which type of adaptive filter do you want ?" << endl;
			cout << " 1: LMS" << endl;
			cout << " 2: RLS" << endl;
			cout << " 3: AMRLS" << endl;
			cout << " 4: NN" << endl;
			cin >> filterchoice;

			cout << "Reference Data: ";
			cin >> noisefilename;
			
			cout << "Component Index (Hx,Hy,Ex,Ey): ";
			cin >> index;
			cout << "Input Time Series Filename: ";
			cin >> tsfilename;
		    cout << "Number of input channels: ";
			cin >> ntimeseries;	
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

                assert(opt.HasMember("filterchoice"));
                assert(opt["filterchoice"].IsInt());
                filterchoice = opt["filterchoice"].GetInt();
				
				assert(opt.HasMember("index"));
                assert(opt["index"].IsInt());
                index = opt["index"].GetInt();
				
				assert(opt.HasMember("ntimeseries"));
                assert(opt["ntimeseries"].IsInt());
                ntimeseries = opt["ntimeseries"].GetInt();
				
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

    TimeSeriesComponent *RefComp;
    switch (index)
      {
    case 1:
      RefComp = &ReferenceData.GetData().GetHx();
      break;
    case 2:
      RefComp = &ReferenceData.GetData().GetHy();
      break;
    case 3:
      RefComp = &ReferenceData.GetData().GetEx();
      break;
    case 4:
      RefComp = &ReferenceData.GetData().GetEy();
      break;
    default:
      cerr << "Component index not valid !";
      return 100;
      break;
      }

    NeuralNetwork::ttypeArray NNLayers;
    double NNmaxinit;
    switch (filterchoice)
      {
    case 1:
      Filter = new LMSCanceller(filterlength, mu);
      break;
    case 2:
      Filter = new RLSCanceller(filterlength,
          delta, lambda);
      break;
    case 3:
      Filter = new AMRLSCanceller(filterlength,
          delta, lambda, alpha);
      break;
    case 4:
      GetNNSetup(filterlength, hiddenlayers, ntimeseries, NNLayers, NNmaxinit);
      Filter = new NeuralNetwork(filterlength, 1,
          mu, NNLayers, NNmaxinit);
      break;
    default:
      cerr << "Invalid number input, don't know what to do and will exit ! ";
      return 100;
      break;
      }

    ApplyFilter Canceller(*Filter, true);
    Canceller.AddReferenceChannel(*RefComp);
    for (int i = 0; i < ntimeseries; ++i)
      {
        // cout << "Component Index (Hx,Hy,Ex,Ey): ";
        // cin >> index;
        switch (index)
          {
        case 1:
          Canceller.AddInputChannel(InputData.GetData().GetHx());
          break;
        case 2:
          Canceller.AddInputChannel(InputData.GetData().GetHy());
          break;
        case 3:
          Canceller.AddInputChannel(InputData.GetData().GetEx());
          break;
        case 4:
          Canceller.AddInputChannel(InputData.GetData().GetEy());
          break;
        default:
          cerr << "Component index not valid !";
          return 100;
          break;
          }
      }

		Canceller.SetWeightSaveIntervall(1000);
		Canceller.SetShift(shift);
		Canceller.ShowProgress(true);
		cout << " First iteration: " << endl << endl;

		Canceller.FilterData();

		cout << endl << endl << " Second iteration: " << endl << endl;

		Canceller.FilterData();

		copy(Canceller.GetOutChannels().front()->GetData().begin(),
			Canceller.GetOutChannels().front()->GetData().end(),
			RefComp->GetData().begin());
		ReferenceData.WriteBack(noisefilename + ".clean");
		ofstream cleanfile((noisefilename + ".clean").c_str());
		copy(Canceller.GetOutChannels().front()->GetData().begin(),
			Canceller.GetOutChannels().front()->GetData().end(), ostream_iterator<
				double> (cleanfile, "\n"));
		copy(Canceller.GetEpsValues().front().begin(),
			Canceller.GetEpsValues().front().end(), RefComp->GetData().begin());

		ReferenceData.WriteBack(noisefilename + ".eps");
		ofstream epsfile((noisefilename + ".eps").c_str());
		copy(Canceller.GetEpsValues().front().begin(),
			Canceller.GetEpsValues().front().end(), ostream_iterator<double> (
				epsfile, "\n"));

		WriteNetCDF(noisefilename + ".weights.nc", Canceller.GetWeightHistory());
		delete Filter;		
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
