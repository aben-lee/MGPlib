#include <iostream>
#include <iomanip>
#include <vector>
#include "MTStationList.h"
#include "Util.h"
using namespace std;
using namespace gplib;

void Interpolate(const std::vector<double> &xvalues, const std::vector<double> &yvalues,
    const std::vector<double> &InterpX, std::vector<double> &InterpY)
  {
    const size_t ninter = InterpX.size();
    size_t currindex = 0;
    for (size_t i = 0; i < ninter; ++i)
      {
        while (xvalues[currindex] <= InterpX[i] && currindex <= xvalues.size())
          ++currindex;
        if ( currindex > xvalues.size())
          {
            InterpY.push_back(0.0);
          }
        else
          {
            if (currindex == 0 && InterpX[i] == xvalues[currindex])
              {
                InterpY.push_back(yvalues[currindex]);
              }
            else
              {
                if (currindex == xvalues.size() && InterpX[i] == xvalues[currindex - 1])
                  {
                    InterpY.push_back(yvalues[currindex - 1]);
                  }
                else
                  {
                    double curry = yvalues[currindex - 1]
                        + (yvalues[currindex] - yvalues[currindex - 1])
                            / (xvalues[currindex] - xvalues[currindex - 1])
                            * (InterpX[i] - xvalues[currindex - 1]);
                    InterpY.push_back(curry);
                  }
              }

          }
      }
  }

void InterpolateError(const std::vector<double> &xvalues,
    const std::vector<double> &yvalues, const std::vector<double> &InterpX,
    std::vector<double> &InterpY)
  {
    const size_t ninter = InterpX.size();
    size_t currindex = 0;
    for (size_t i = 0; i < ninter; ++i)
      {
        while (xvalues[currindex] <= InterpX[i] && currindex <= xvalues.size())
          ++currindex;
        if ( currindex > xvalues.size())
          {
            InterpY.push_back(0.0);
          }
        else
          {
            if (currindex == 0 && InterpX[i] == xvalues[currindex])
              {
                InterpY.push_back(yvalues[currindex]);
              }
            else
              {
                if (currindex == xvalues.size() && InterpX[i] == xvalues[currindex - 1])
                  {
                    InterpY.push_back(yvalues[currindex - 1]);
                  }
                else
                  {
                    double curry = std::max(yvalues[currindex - 1], yvalues[currindex]);
                    InterpY.push_back(curry);
                  }
              }

          }
      }
  }

void SetMissing(std::complex<double> &value, double &error)
  {
    value = std::complex<double>(1.0, 1.0);
    error = 10.0;
  }

int main(int argc, char* argv[])
  {
    string version = "$Id: freqinter.cpp 1886 2014-10-29 12:38:46Z mmoorkamp $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << " Read in several files with MT tensor data" << endl;
    cout << " and keep interpolate between frequencies. The files will be written in"
        << endl;
    cout
        << " .mtt format. If the input files were in that format they will be overwritten"
        << endl;
    cout << endl << endl;

    try
      {
        MTStationList MTSites;
        std::string infilename;
        //read the file with the name of stations either directly from the command line
        if (argc > 1)
          {
            infilename = argv[1];
          }
        else
          {
            //or prompt for it.
            infilename = AskFilename("Station Filename: ");
          }

        MTSites.GetData(infilename);
        const size_t nstats = MTSites.GetList().size();
        //create a display of frequencies in the different files
        //first column is the filename, then a column for each frequency
        //in the first data files
        std::cout << "Frequency matrix \n" << std::endl;
        std::cout << std::setw(12) << "Filename ";
        std::vector<double> MasterFreqs(MTSites.at(0).GetFrequencies());
        for (double freq : MasterFreqs)
          {
            std::cout << std::setw(10) << freq << std::endl;
          }
        std::cout << std::endl;

        std::cout << "Frequencies per decade: ";
        int freqperdec;
        std::cin >> freqperdec;

        double minfreq = *std::min_element(MasterFreqs.begin(), MasterFreqs.end());
        double maxfreq = *std::max_element(MasterFreqs.begin(), MasterFreqs.end());
        double decades = log10(maxfreq) - log10(minfreq);
        size_t nfreq = ceil(decades * freqperdec);
        double freqstep = decades / nfreq;
        std::vector<double> OutFreqs(nfreq);
        for (size_t i = 0; i < nfreq; ++i)
          {
            OutFreqs.at(i) = pow10(log10(minfreq) + freqstep * i);
          }

        std::cout << "Output frequencies: ";
        std::copy(OutFreqs.begin(), OutFreqs.end(),
            std::ostream_iterator<double>(std::cout, " "));
        std::cout << "\n";

        MTStationList OutList;
        //the relative tolerance with which we consider two frequencies equal
        const double tolerance = 0.05;
        for (size_t i = 0; i < nstats; ++i)
          {
            //for each site we output its name in the first column
            std::cout << std::setw(10) << MTSites.at(i).GetName();
            MTStation CurrStation(MTSites.at(i));
            CurrStation.SetFrequencies(OutFreqs);
            auto CurrData = MTSites.at(i).GetMTData();
            std::vector<double> ZxxR, ZxxI, ZxyR, ZxyI, ZyxR, ZyxI, ZyyR, ZyyI, dZxx,
                dZxy, dZyx, dZyy;
            size_t nvals = CurrData.size();
            for (size_t j = 0; j < nvals; ++j)
              {
                auto CurrTensor = CurrData.at(j);
                ZxxR.push_back(std::real(CurrTensor.GetZxx()));
                ZxxI.push_back(std::imag(CurrTensor.GetZxx()));
                ZxyR.push_back(std::real(CurrTensor.GetZxy()));
                ZxyI.push_back(std::imag(CurrTensor.GetZxy()));
                ZyxR.push_back(std::real(CurrTensor.GetZyx()));
                ZyxI.push_back(std::imag(CurrTensor.GetZyx()));
                ZyyR.push_back(std::real(CurrTensor.GetZyy()));
                ZyyI.push_back(std::imag(CurrTensor.GetZyy()));
                dZxx.push_back(CurrTensor.GetdZxx());
                dZxy.push_back(CurrTensor.GetdZxy());
                dZyx.push_back(CurrTensor.GetdZyx());
                dZyy.push_back(CurrTensor.GetdZyy());
              }
            std::vector<double> IZxxR, IZxxI, IZxyR, IZxyI, IZyxR, IZyxI, IZyyR, IZyyI,
                IdZxx, IdZxy, IdZyx, IdZyy;
            std::vector<double> SiteFreqs(MTSites.at(i).GetFrequencies());
            Interpolate(SiteFreqs, ZxxR, OutFreqs, IZxxR);
            Interpolate(SiteFreqs, ZxxI, OutFreqs, IZxxI);
            Interpolate(SiteFreqs, ZxyR, OutFreqs, IZxyR);
            Interpolate(SiteFreqs, ZxyI, OutFreqs, IZxyI);
            Interpolate(SiteFreqs, ZyxR, OutFreqs, IZyxR);
            Interpolate(SiteFreqs, ZyxI, OutFreqs, IZyxI);
            Interpolate(SiteFreqs, ZyyR, OutFreqs, IZyyR);
            Interpolate(SiteFreqs, ZyyI, OutFreqs, IZyyI);
            InterpolateError(SiteFreqs, dZxx, OutFreqs, IdZxx);
            InterpolateError(SiteFreqs, dZxy, OutFreqs, IdZxy);
            InterpolateError(SiteFreqs, dZyx, OutFreqs, IdZyx);
            InterpolateError(SiteFreqs, dZyy, OutFreqs, IdZyy);

            MTStation OutSite(nfreq);
            OutSite.SetFrequencies(OutFreqs);
            for (size_t j = 0; j < nfreq; ++j)
              {
                if (IZxxR[j] != 0.0 || IZxxI[j] != 0.0)
                  {
                    OutSite.SetMTData().at(j).SetZxx() = std::complex<double>(IZxxR[j],
                        IZxxI[j]);
                    OutSite.SetMTData().at(j).SetdZxx() = IdZxx[j];
                  }
                else
                  {
                    SetMissing(OutSite.SetMTData().at(j).SetZxx(),
                        OutSite.SetMTData().at(j).SetdZxx());
                  }

                if (IZxyR[j] != 0.0 || IZxyI[j] != 0.0)
                  {
                    OutSite.SetMTData().at(j).SetZxy() = std::complex<double>(IZxyR[j],
                        IZxyI[j]);
                    OutSite.SetMTData().at(j).SetdZxy() = IdZxy[j];
                  }
                else
                  {
                    SetMissing(OutSite.SetMTData().at(j).SetZxy(),
                        OutSite.SetMTData().at(j).SetdZxy());
                  }

                if (IZyxR[j] != 0.0 || IZyxI[j] != 0.0)
                  {
                    OutSite.SetMTData().at(j).SetZyx() = std::complex<double>(IZyxR[j],
                        IZyxI[j]);
                    OutSite.SetMTData().at(j).SetdZyx() = IdZyx[j];
                  }
                else
                  {
                    SetMissing(OutSite.SetMTData().at(j).SetZyx(),
                        OutSite.SetMTData().at(j).SetdZyx());
                  }

                if (IZyyR[j] != 0.0 || IZyyI[j] != 0.0)
                  {
                    OutSite.SetMTData().at(j).SetZyy() = std::complex<double>(IZyyR[j],
                        IZyyI[j]);
                    OutSite.SetMTData().at(j).SetdZyy() = IdZyy[j];
                  }
                else
                  {
                    SetMissing(OutSite.SetMTData().at(j).SetZyy(),
                        OutSite.SetMTData().at(j).SetdZyy());
                  }

              }
            OutList.GetList().push_back(OutSite);
          }

        //now we go through the sites again to mark the ones
        //that are not in the master file
        for (size_t i = 0; i < nstats; ++i)
          {
            OutList.at(i).WriteAsMtt(MTSites.at(i).GetName());
          }
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      }
  }

