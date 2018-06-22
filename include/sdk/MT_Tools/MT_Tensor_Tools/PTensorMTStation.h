#ifndef PTENSORMTSTATION_H_
#define PTENSORMTSTATION_H_
#include "PTensorMTData.h"
#include <vector>
#include <string>
#include "types.h"
#include "MTStation.h"
#include <fstream>
#include <iomanip>
#include "FatalException.h"

using namespace std;

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    class PTensorMTStation
      {
    private:
      std::vector<PTensorMTData> Tensor;
    public:
      const PTensorMTData &at(const unsigned int i) const
        {
          return Tensor.at(i);
        }
      PTensorMTData &at(const unsigned int i)
        {
          return Tensor.at(i);
        }
      std::vector<PTensorMTData> &GetTensor()
        {
          return Tensor;
        }
      const std::vector<PTensorMTData> &GetTensor() const
        {
          return Tensor;
        }
      const trealdata GetFrequencies() const
      {
        trealdata temp(Tensor.size());
        transform(Tensor.begin(), Tensor.end(), temp.begin(), mem_fun_ref(
            &PTensorMTData::GetFrequency));
        return temp;
      }

      void GetData(const std::string &filename)
      {
        ifstream infile(filename.c_str());
        Tensor.clear();
        double period, phi11, phi12, phi21, phi22, dphi11, dphi12, dphi21,
            dphi22;
        while (infile.good())
          {
            infile >> period >> phi11 >> dphi11 >> phi12 >> dphi12 >> phi21
                >> dphi21 >> phi22 >> dphi22;
            if (infile.good())
              {
                Tensor.push_back(PTensorMTData(1. / period, phi11, phi12,
                    phi21, phi22, dphi11, dphi12, dphi21, dphi22));
              }
          }
        if (Tensor.size() < 1)
          throw FatalException("Ptensor file does not exist or is empty !");
      }

      void WriteData(const std::string &filename)
      {
        ofstream outfile((filename + ".ptensor").c_str());
        const unsigned int nfreq = Tensor.size();
        for (unsigned int i = 0; i < nfreq; ++i)
          {
            outfile << 1. / Tensor.at(i).GetFrequency() << " ";
            outfile << Tensor.at(i).GetPhi11() << " "
                << Tensor.at(i).GetdPhi11() << " ";
            outfile << Tensor.at(i).GetPhi12() << " "
                << Tensor.at(i).GetdPhi12() << " ";
            outfile << Tensor.at(i).GetPhi21() << " "
                << Tensor.at(i).GetdPhi21() << " ";
            outfile << Tensor.at(i).GetPhi22() << " "
                << Tensor.at(i).GetdPhi22() << endl;
          }
      }
      //! copies the phase tensor elements calculated from the impedance in MTData, but without errors
      PTensorMTStation &operator=(const MTStation &MTData)
      {
        Tensor.clear(); // clear old data
        const unsigned int nfrequencies = MTData.GetMTData().size();
        Tensor.reserve(nfrequencies);
        for (unsigned int i = 0; i < nfrequencies; ++i)
          {
            Tensor.push_back(PTensorMTData(MTData.at(i).GetFrequency(),
                MTData.at(i).GetPhi11(), MTData.at(i).GetPhi12(),
                MTData.at(i).GetPhi21(), MTData.at(i).GetPhi22(), 0.0, 0.0,
                0.0, 0.0));
          }
        return *this;
      }

      PTensorMTStation();
      virtual ~PTensorMTStation();
      };
  /* @} */
  }
#endif /*PTENSORMTSTATION_H_*/
