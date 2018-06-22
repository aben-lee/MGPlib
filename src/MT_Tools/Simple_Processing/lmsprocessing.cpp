#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "CLMSCanceller.h"
#include "CTimeSeriesData.h"
#include "CStackedSpectrum.h"
#include "CMTStation.h"
#include "CMttData.h"

using namespace std;
using namespace gplib;

int main()
  {
    CLMSCanceller Canceller;
    CTimeSeriesData TsData;
    StackedSpectrum WeightSpectrum;
    CMTStation MTData;
    CMttData MttData;
    //CMTStation Output;
    MTData.MTData = &MttData;
    const int filterlength = 111;
    //const double mu = 1e-17;
    const double mu = -1;
    const int ntimeseries = 2;
    const int shift = 0; // filterlength/2;
    //const double freqstep = 150/filterlength;
    double freqstep;
    int i, j;
    string tsfilename;
    ifstream noisefile, tsfile;
    ofstream outfile, weightfile, epsfile;
    double temp;
    vector<double> noise, epsilon, output, ts;

    cout << "Time Series Filename: ";
    cin >> tsfilename;
    TsData.GetData(tsfilename);
    freqstep = TsData.Data->samplerate / filterlength;
    Canceller.filterlength = filterlength;
    Canceller.mu.assign(ntimeseries, -1);
    //Canceller.input = &TsData.Data->Ex.data;
    Canceller.FilterOutput = &(TsData.Data->Ex.data);
    Canceller.Input.push_back(&TsData.Data->Hx.data);
    Canceller.Input.push_back(&TsData.Data->Hy.data);
    Canceller.Epsilon = &epsilon;
    Canceller.Desired = &output;
    Canceller.FilterData(shift);

    cout << "Mu: ";
    for (i = 0; i < ntimeseries; ++i)
      cout << Canceller.mu.at(i) << " ";
    cout << endl;
    epsfile.open((tsfilename + ".eps").c_str());
    outfile.open((tsfilename + ".clean").c_str());
    for (i = 0; i < output.size(); ++i)
      {
        outfile << output.at(i) << endl;
        epsfile << Canceller.Epsilon->at(i) << endl;
      }
    outfile.close();
    epsfile.close();

    WeightSpectrum.TimeSeries.assign(filterlength, 0);
    copy(Canceller.Weights.begin() + filterlength, Canceller.Weights.end(),
        WeightSpectrum.TimeSeries.begin());
    WeightSpectrum.CalcSpectrum(filterlength);

    weightfile.open((tsfilename + ".weights").c_str());
    for (i = 0; i < WeightSpectrum.Spectrum.size(); ++i)
      weightfile << i << " " << abs(WeightSpectrum.Spectrum.at(i)) << " "
          << arg(WeightSpectrum.Spectrum.at(i)) << endl;
    weightfile.close();

    MTData.MTData->AssignAll(filterlength / 2);
    cout << "Assigning Tensor values. " << endl << flush;
    copy(WeightSpectrum.Spectrum.begin(), WeightSpectrum.Spectrum.begin()
        + filterlength / 2, MTData.MTData->DataXY.Z.begin());
    for (int i = 0; i < filterlength / 2; ++i)
      MTData.MTData->frequency.at(i) = i * freqstep;
    MTData.MTData->frequency.at(0) = 0.00000001;
    cout << "Writing Data. " << endl << flush;
    MTData.WriteAsMtt(tsfilename);
  }
