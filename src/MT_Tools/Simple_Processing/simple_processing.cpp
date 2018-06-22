#include <iostream>
#include <iterator>
#include <fstream>
#include <boost/program_options.hpp>
#include "TsSpectrum.h"
#include "TimeSeriesData.h"
#include "statutils.h"
#include "MTStation.h"
#include "types.h"
#include "WFunc.h"
#include "TimeFrequency.h"
#include "VecMat.h"
#include "MtuFilter.h"
#include "Util.h"

using namespace std;
using namespace gplib;
namespace po = boost::program_options;


/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file simple_processing.cpp
 * Very simple MT processing code based on least squares estimation as described by Sims 1971.
 * So far no error calculation.
 */

string version =
    "$Id: simple_processing.cpp 1853 2010-05-28 10:37:12Z mmoorkamp $";
int main(int argc, char *argv[])
  {
    cout
        << "This is simpleproc: Simple most estimation of MT transfer function, spectral stacking"
        << endl << endl;
    cout << " Usage   simpleproc  inputfilename";
    cout
        << " Output will have the same name as MTU Input with '.mtt' appended "
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    TimeSeriesData MtuData;
    MTStation Output;
    string infilename, basefilename;
    unsigned int seglength = 2400;
    bool mtufilter = false;
    double rate = 1.0;
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("seglength", po::value<
        unsigned int>(&seglength)->default_value(2400),
        "The length of an individual segment for spectral calculations")(
        "rate", po::value(&rate)->default_value(1.0),
        "Set the sampling rate in Hz")("mtufilter",
        po::value<bool>(&mtufilter)->default_value(false),
        "Read in filter information for mtu data")("input-file", po::value<
        string>(&infilename), "input file");

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(
        po::command_line_parser(argc, argv). options(desc).positional(p).run(),
        vm);
    po::notify(vm);

    if (vm.count("help"))
      {
        cout << desc << "\n";
        return 1;
      }
    MtuData.GetData(infilename.c_str());
    size_t dotpos = infilename.find('.', 0);
    if (dotpos != string::npos)
      basefilename = infilename.erase(dotpos);
    string exfiltername = basefilename + "_1.cts";
    string eyfiltername = basefilename + "_2.cts";
    string hxfiltername = basefilename + "_3.cts";
    string hyfiltername = basefilename + "_4.cts";


    const unsigned int nfreqs = seglength / 2 + 1;
    tcompdata ExHxCorr(nfreqs, 0);
    tcompdata ExHyCorr(nfreqs, 0);
    tcompdata EyHxCorr(nfreqs, 0);
    tcompdata EyHyCorr(nfreqs, 0);
    tcompdata HxHxCorr(nfreqs, 0);
    tcompdata HxHyCorr(nfreqs, 0);
    tcompdata HyHyCorr(nfreqs, 0);
    tcompdata Hdet(nfreqs, 0);
    tcompdata Zxx(nfreqs, 0);
    tcompdata Zxy(nfreqs, 0);
    tcompdata Zyx(nfreqs, 0);
    tcompdata Zyy(nfreqs, 0);



    double freqstep = MtuData.GetData().GetSamplerate() / (seglength);
    MtuFilter ExFilter(seglength, freqstep), EyFilter(seglength, freqstep),
        HxFilter(seglength, freqstep), HyFilter(seglength, freqstep);
    if (mtufilter)
      {
        ExFilter.GetData(exfiltername);
        EyFilter.GetData(eyfiltername);
        HxFilter.GetData(hxfiltername);
        HyFilter.GetData(hyfiltername);
      }
    gplib::cmat ExTimeFrequency, EyTimeFrequency, HxTimeFrequency,
        HyTimeFrequency;

    ExTimeFrequency = TimeFrequency(
        MtuData.GetData().GetEx().GetData().begin(),
        MtuData.GetData().GetEx().GetData().end(), seglength, Hanning());
    EyTimeFrequency = TimeFrequency(
        MtuData.GetData().GetEy().GetData().begin(),
        MtuData.GetData().GetEy().GetData().end(), seglength, Hanning());
    HxTimeFrequency = TimeFrequency(
        MtuData.GetData().GetHx().GetData().begin(),
        MtuData.GetData().GetHx().GetData().end(), seglength, Hanning());
    HyTimeFrequency = TimeFrequency(
        MtuData.GetData().GetHy().GetData().begin(),
        MtuData.GetData().GetHy().GetData().end(), seglength, Hanning());

    const unsigned int nsegs = ExTimeFrequency.size1();
    ofstream logfile((infilename + ".log").c_str());
    for (size_t i = 0; i < Zxx.size(); ++i)
      {
        for (size_t j = 0; j < nsegs; ++j)
          {
            if (mtufilter)
              {
                ExTimeFrequency(j, i) /= ExFilter.GetFilterCoeff().at(i);
                EyTimeFrequency(j, i) /= EyFilter.GetFilterCoeff().at(i);
                HxTimeFrequency(j, i) /= HxFilter.GetFilterCoeff().at(i);
                HyTimeFrequency(j, i) /= HyFilter.GetFilterCoeff().at(i);
              }
            ExHxCorr.at(i) += (ExTimeFrequency(j, i) * conj(HxTimeFrequency(j,
                i)));
            ExHyCorr.at(i) += (ExTimeFrequency(j, i) * conj(HyTimeFrequency(j,
                i)));
            EyHxCorr.at(i) += (EyTimeFrequency(j, i) * conj(HxTimeFrequency(j,
                i)));
            EyHyCorr.at(i) += (EyTimeFrequency(j, i) * conj(HyTimeFrequency(j,
                i)));
            HxHyCorr.at(i) += (HxTimeFrequency(j, i) * conj(HyTimeFrequency(j,
                i)));
            HxHxCorr.at(i) += (HxTimeFrequency(j, i) * conj(HxTimeFrequency(j,
                i)));
            HyHyCorr.at(i) += (HyTimeFrequency(j, i) * conj(HyTimeFrequency(j,
                i)));

          }

        Hdet.at(i) = (HxHxCorr.at(i) * HyHyCorr.at(i) - HxHyCorr.at(i) * conj(
            HxHyCorr.at(i)));
        logfile << "Hdet: " << Hdet.at(i) << endl;
        Zxx.at(i) = ((ExHxCorr.at(i) * HyHyCorr.at(i) - ExHyCorr.at(i) * conj(
            HxHyCorr.at(i))) / Hdet.at(i));
        Zxy.at(i) = ((ExHyCorr.at(i) * HxHxCorr.at(i) - ExHxCorr.at(i)
            * HxHyCorr.at(i)) / Hdet.at(i));
        Zyx.at(i) = ((EyHxCorr.at(i) * HyHyCorr.at(i) - EyHyCorr.at(i) * conj(
            HxHyCorr.at(i))) / Hdet.at(i));
        Zyy.at(i) = ((EyHyCorr.at(i) * HxHxCorr.at(i) - EyHxCorr.at(i)
            * HxHyCorr.at(i)) / Hdet.at(i));
      }
    Output.AssignAll(Zxx.size());
    for (size_t i = 0; i < Zxx.size(); ++i)
      {
        MTTensor
            CurrZ(Zxx.at(i), Zxy.at(i), Zyx.at(i), Zyy.at(i), i * freqstep);
        Output.SetMTData().at(i) = CurrZ;
      }
    vector<double> transferfunc(Zxx.size() * 2 - 1, 0.0);
    TsSpectrum().CalcTimeSeries(Zxy.begin(), Zxy.end(), transferfunc.begin(),
        transferfunc.end());
    ofstream tffile((infilename + ".tf").c_str());
    copy(transferfunc.begin(), transferfunc.end(), ostream_iterator<double> (
        tffile, "\n"));

    Output.WriteAsMtt(infilename.c_str());
  }
/*@}*/
