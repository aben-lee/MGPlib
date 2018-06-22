/*!
 * \file
 * This is the cagniard algorithm to calculate synthetic 1D forward responses for MT.
 *  It reads in model files in the following simple format:
 * <TABLE>
 * <TR> <TD> No. of layers </TD> </TR>
 * <TR> <TD> Thickness in km </TD>  <TD> Resistivity in \f$\Omega m\f$  </TD></TR>
 * </TABLE>
 *
 * The user has to specify the output filename without the ending. ".mtt" will be appended
 * automatically to indicate that this file is in Goettingen .mtt format.
 *
 * There are two different modes: In standard mode (mode 0)
 * the frequencies at which the responses are
 * calculated are based on some realistic frequencies used in deep MT surveys (300Hz - 10.000s).
 * In mode 1 the user can specify a window length and sampling rate and the output frequencies are
 * based on the fft of a windows with those parameters. This is only useful for some special
 * processing applications and might be removed in the future.
 */

#include <iostream>
#include <string>
#include "Util.h"
#include "C1DMTSynthData.h"
#include <iterator>

using namespace std;
using namespace gplib;

int main(int argc, char *argv[])
  {
    string version =
        "$Id: cag++.cpp 20 2005-11-11 12:57:01 +0100 (Fr, 11 Nov 2005) max $";
    cout << endl << endl;
    cout << "Program " << version << endl;
    cout << "Calculates 1D MT Responses from input models " << endl;
    cout
        << "Based on Cagniard algorithm, with stability enhancements taken from A. Avdeeva "
        << endl;

    C1DMTSynthData Synthetic; // create Object for Calculation of Synthetics


    double samplerate, freqstep;
    int samplelength;
    const double eps = 1e-5;
    string modelfilename, mttfilename;
    int mode = 0;
    try
      {
        if (argc == 2)
          {
            modelfilename = argv[1];
            mttfilename = modelfilename;
            mode = 0;
          }
        else
          {
            modelfilename = AskFilename("Model filename: ");

            cout << "Output Format is .mtt ! Do not append ending. " << endl;
            mttfilename = AskFilename("Output filename: ");

            cout
                << "Use Mode = 0 for standard calculation with fixed frequencies (long period) "
                << endl;
            cout
                << "Use Mode = 1 if you want frequencies to be calculated from sample rate and window length."
                << endl;
            cout
                << "Use Mode = 2 if you want to specify the frequency range and sampling."
                << endl;
            cout << "Mode: ";
            cin >> mode;
          }
        Synthetic.ReadModel(modelfilename); // read in model
        switch (mode)
          {
        case 1: //if we want frequencies for a certain window length and sampling rate
          {
            cout << "Sampling rate in Hz: "; //ask
            cin >> samplerate;
            cout << "Length for continuous sample (number of samples): ";
            cin >> samplelength;
            freqstep = samplerate / samplelength;
            trealdata frequency;
            frequency.push_back(eps); //zero frequency means not valid so we use a small value for the static
            for (int i = 1; i < samplelength / 2; ++i) // add frequencies
              {
                frequency.push_back(freqstep * i);
              }
            Synthetic.SetFrequencies(frequency);//copy them to forward calculation object
            break;
          }
        case 2:
          {
            double minfreq = 0.0;
            cout << "Minimum frequency in Hz: ";
            cin >> minfreq;
            double maxfreq = 0.0;
            cout << "Maximum frequency in Hz: ";
            cin >> maxfreq;
            double sampling = 0.0;
            cout << "Frequencies per decade: ";
            cin >> sampling;
            if (maxfreq < minfreq)
              {
                std::cerr << "Maximum frequency less than minimum freuqency !"
                    << std::endl;
                return 100;
              }
            if (sampling <= 0.0)
              {
                std::cerr << "Sampling step is not positive !" << std::endl;
                return 200;
              }
            minfreq = log10(minfreq);
            maxfreq = log10(maxfreq);
            double step = 1.0 / sampling;
            trealdata frequency;
            for (double currfreq = minfreq; currfreq < maxfreq; currfreq
                += step)
              {
                frequency.push_back(std::pow(10.0, currfreq));
              }
            Synthetic.SetFrequencies(frequency);//copy them to forward calculation object
            break;
          }
          }

        Synthetic.CalcSynthetic(); // Calculate Model
        Synthetic.WriteAsMtt(mttfilename); // Write out Mtt file
      } catch (FatalException &e)
      {
        cerr << e.what() << endl;
        return -1;
      }
  }
