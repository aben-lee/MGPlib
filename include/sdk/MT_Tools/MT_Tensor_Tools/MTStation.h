#ifndef CMTSTATION_H
#define CMTSTATION_H

#include "MTTensor.h"
#include "MagneticTF.h"
#include "types.h"
#include <string>
#include <map>
#include <boost/function.hpp>
#include "miscfunc.h"

   #define HAVEANTLR 1

#ifdef HAVEANTLR
#include "EDILexer.hpp"
#include "EDIParser.hpp"
#include "JLexer.hpp"
#include "JParser.hpp"
#endif
//similarly we only activate reading netcdf files
//if netcdf is installed
#ifdef HAVENETCDF
#include "ReadWriteImpedances.h"
#endif
#include <iomanip>
#include <iterator>
#include <string>
#include "convert.h"
#include "FatalException.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/tokenizer.hpp>
#include <functional>
#include <fstream>
#include <cassert>
#include <map>
#include "Util.h"

using namespace std;



namespace gplib
  {


void TrimFilename(std::string &name)
  {
    size_t slashpos = name.find('/', 0);
    if (slashpos != std::string::npos)
      name = name.substr(slashpos + 1);
    size_t dotpos = name.find('.', 0);
    if (dotpos != std::string::npos)
      name.erase(dotpos);
  }
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! The class MTStation is used to store the transfer functions and related information for a MT-site
    class MTStation
      {

    public:
      enum tmtdataformat
        {
        unknown, mtt, j, edi, pek, nc, zmm, mtf
        };

      const std::map<std::string, MTStation::tmtdataformat> MTFileTypes =  {
            { ".mtt", MTStation::tmtdataformat::mtt},
            { ".j", MTStation::tmtdataformat::j},
            { ".dat", MTStation::tmtdataformat::j},
            { ".nc", MTStation::tmtdataformat::nc},
            { ".zmm", MTStation::tmtdataformat::zmm},
            { ".mtf", MTStation::tmtdataformat::mtf},
            { ".edi", MTStation::tmtdataformat::edi},
            { ".pek", MTStation::tmtdataformat::pek}
        };

    private:
      //! Station Latitude
      double latitude;
      //! Station Lonigude
      double longitude;
      //! Station elevation
      double elevation;
      //! Name, does not have to be filename for j and edi data
      std::string name;
      //! Azimuth from magnetic north if station was rotated
      double azimuth;
      // The MTTensor data for each frequency
      std::vector<MTTensor> MTData;
      // The Local induction vectors for each frequency
      std::vector<MagneticTF> TFData;
      void DoRotate(const int i, const double angle)
      {
        dcomp newxx, newxy, newyx, newyy;
        newxx = MTData.at(i).Zxx * std::pow(cos(angle), 2)
            + (MTData.at(i).Zxy + MTData.at(i).Zyx) * sin(angle) * cos(angle)
            + MTData.at(i).Zyy * std::pow(sin(angle), 2);
        newxy = MTData.at(i).Zxy * std::pow(cos(angle), 2)
            - (MTData.at(i).Zxx - MTData.at(i).Zyy) * sin(angle) * cos(angle)
            - MTData.at(i).Zyx * std::pow(sin(angle), 2);
        newyx = MTData.at(i).Zyx * std::pow(cos(angle), 2)
            - (MTData.at(i).Zxx - MTData.at(i).Zyy) * sin(angle) * cos(angle)
            - MTData.at(i).Zxy * std::pow(sin(angle), 2);
        newyy = MTData.at(i).Zyy * std::pow(cos(angle), 2)
            - (MTData.at(i).Zxy + MTData.at(i).Zyx) * sin(angle) * cos(angle)
            + MTData.at(i).Zxx * std::pow(sin(angle), 2);
        MTData.at(i).Zxx = newxx;
        MTData.at(i).Zxy = newxy;
        MTData.at(i).Zyx = newyx;
        MTData.at(i).Zyy = newyy;
        MTData.at(i).rotangle += angle;
      }
      //! Perform some initial Setup
      void InitialSetup()
      {
        latitude = 0;
        longitude = 0;
        elevation = 0;
        azimuth = 0;
      }
      //! the format the data was stored in the original file
      tmtdataformat dataformat;
      //! Write data to file in goettingen .mtt format

      void inline MttLine(std::ofstream &outfile, double value)
        {
          outfile << setw(15) << setfill(' ') << setprecision(8) << setiosflags(ios::fixed)
              << value << " ";
        }

      void WriteMtt(const std::string filename)
      {
        ofstream outfile;

        outfile.open(filename.c_str());
        std::map<double, int> FreqOrder;
        for (size_t i = 0; i < MTData.size(); ++i)
          {
            FreqOrder.insert(std::make_pair(MTData.at(i).frequency, i));
          }
        // index(frequency, mttindex);
        assert(MTData.size() == TFData.size());
        for (auto currfreq : FreqOrder) //write mtt-file
          {
            int i = currfreq.second;
            if (MTData.at(i).frequency > 0)
              {
                //we write out the frequency in scientific notation
                //to avoid loss of precision for low frequencies
                outfile << setw(15) << setfill(' ') << setprecision(8)
                    << setiosflags(ios::scientific) << MTData.at(i).frequency;
                outfile << "  " << resetiosflags(ios::scientific) << setprecision(5)
                    << MTData.at(i).Nu << "\n";
                //some of the older programs are very picky about
                //how numbers are written, so we write the tensor
                //elements in fixed format
                MttLine(outfile, MTData.at(i).Zxx.real());
                MttLine(outfile, MTData.at(i).Zxx.imag());
                MttLine(outfile, MTData.at(i).Zxy.real());
                MttLine(outfile, MTData.at(i).Zxy.imag());
                MttLine(outfile, MTData.at(i).Zyx.real());
                MttLine(outfile, MTData.at(i).Zyx.imag());
                MttLine(outfile, MTData.at(i).Zyy.real());
                MttLine(outfile, MTData.at(i).Zyy.imag());
                outfile << "\n";
                MttLine(outfile, MTData.at(i).dZxx);
                MttLine(outfile, MTData.at(i).dZxy);
                MttLine(outfile, MTData.at(i).dZyx);
                MttLine(outfile, MTData.at(i).dZyy);
                MttLine(outfile, TFData.at(i).Tx.real());
                MttLine(outfile, TFData.at(i).Tx.imag());
                MttLine(outfile, TFData.at(i).Ty.real());
                MttLine(outfile, TFData.at(i).Ty.imag());
                outfile << "\n";
                MttLine(outfile, TFData.at(i).dTx);
                MttLine(outfile, TFData.at(i).dTy);
                MttLine(outfile, MTData.at(i).Rx);
                MttLine(outfile, MTData.at(i).Ry);
                MttLine(outfile, TFData.at(i).Rz);
                outfile << "\n" << resetiosflags(ios::fixed);
                //write out mtt file entries
              }

          }
        outfile.close();
      }
      //! Read data from edi file (not all features supported)
      void ReadEdi(const std::string filename);
      //! Read data from j file
      void ReadJ(const std::string filename);
      //! Read data from goettingen .mtt file
      void ReadMtt(const std::string filename)
      {
        ifstream infile;
        double currentreal, currentimag;
        int nentries = 0;
        infile.open(filename.c_str());
        while (infile.good())
          {
            infile >> currentreal;
            ++nentries;
          }
        infile.close();
        if (((nentries - 1) % 23) != 0)
          throw FatalException("Number of records does not match expected: " + filename);
        const int nrecords = (nentries - 1) / 23;
        Assign(nrecords);
        infile.open(filename.c_str());
        int currentrecord = 0;
        if (infile)
          {
            while (infile.good()) // read in inputfile
              {
                infile >> currentreal;
                if (infile.good())
                  {
                    MTData.at(currentrecord).frequency = currentreal;
                    TFData.at(currentrecord).frequency = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).Nu = currentreal;
                    infile >> currentreal >> currentimag;
                    MTData.at(currentrecord).Zxx = (currentreal + I * currentimag);
                    infile >> currentreal >> currentimag;
                    MTData.at(currentrecord).Zxy = (currentreal + I * currentimag);
                    infile >> currentreal >> currentimag;
                    MTData.at(currentrecord).Zyx = (currentreal + I * currentimag);
                    infile >> currentreal >> currentimag;
                    MTData.at(currentrecord).Zyy = (currentreal + I * currentimag);
                    infile >> currentreal;
                    MTData.at(currentrecord).dZxx = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).dZxy = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).dZyx = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).dZyy = currentreal;
                    infile >> currentreal >> currentimag;
                    TFData.at(currentrecord).Tx = currentreal + I * currentimag;
                    infile >> currentreal >> currentimag;
                    TFData.at(currentrecord).Ty = currentreal + I * currentimag;
                    infile >> currentreal;
                    TFData.at(currentrecord).dTx = currentreal;
                    infile >> currentreal;
                    TFData.at(currentrecord).dTy = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).Rx = currentreal;
                    infile >> currentreal;
                    MTData.at(currentrecord).Ry = currentreal;
                    infile >> currentreal;
                    TFData.at(currentrecord).Rz = currentreal;
                    ++currentrecord;
                  }
              }
            infile.close();
            name = filename;
            TrimFilename(name);
          }
        else
          {
            throw FatalException("File not found: " + filename);
          }
        Update();
      }

      //! Read output of Pek's 1D anisotropy code
      void ReadPek1D(const std::string filename)
      {
        ifstream infile(filename.c_str());
        if (infile)
          {
            const double convfactor = 1. / (1000. * mu);
            double period, rxx, imxx, rxy, imxy, ryx, imyx, ryy, imyy;
            while (infile.good())
              {
                infile >> period >> rxx >> imxx >> rxy >> imxy >> ryx >> imyx >> ryy
                    >> imyy;

                if (infile.good())
                  {
                    MTTensor CurrentImp;
                    CurrentImp.frequency = 1. / period;
                    CurrentImp.Zxx = (rxx + I * imxx) * convfactor;
                    CurrentImp.Zxy = (rxy + I * imxy) * convfactor;
                    CurrentImp.Zyx = (ryx + I * imyx) * convfactor;
                    CurrentImp.Zyy = (ryy + I * imyy) * convfactor;
                    MTData.push_back(CurrentImp);
                    TFData.push_back(MagneticTF());
                  }
              }
            name = filename;
            TrimFilename(name);
          }
        else
          {
            throw FatalException("File not found: " + filename);
          }
      }

#ifdef HAVEANTLR
    void MTStation::ReadJ(const std::string filename)
      {

        using namespace antlr;
        ifstream infile(filename.c_str());

        if (infile)
          {
            try
              {
                JLexer lexer(infile);
                JParser parser(lexer);
                parser.jfile();
                latitude = parser.latitude;
                longitude = parser.longitude;
                elevation = parser.elevation;
                azimuth = parser.azimuth;
                name = parser.name;
                TrimFilename(name);
                Assign(parser.frequency.size());

                //frequency = parser.frequency;
                if (parser.zassigned == false && parser.rassigned == false)
                  {
                    cerr << "No MT data in file !" << endl;
                  }
                else
                  {
                    for (unsigned int i = 0; i < parser.frequency.size(); ++i)
                      {
                        MTData.at(i).frequency = parser.frequency.at(i);
                        MTData.at(i).rotangle = parser.azimuth;
                        MTData.at(i).Zxx = parser.DataXX.at(i);
                        MTData.at(i).Zxy = parser.DataXY.at(i);
                        MTData.at(i).Zyx = parser.DataYX.at(i);
                        MTData.at(i).Zyy = parser.DataYY.at(i);
                        MTData.at(i).dZxx = parser.dDataXX.at(i);
                        MTData.at(i).dZxy = parser.dDataXY.at(i);
                        MTData.at(i).dZyx = parser.dDataYX.at(i);
                        MTData.at(i).dZyy = parser.dDataYY.at(i);
                        MTData.at(i).Rx = parser.Rx.at(i);
                        MTData.at(i).Ry = parser.Ry.at(i);
                      }
                  }
                if (parser.tassigned)
                  {
                    for (unsigned int i = 0; i < parser.DataZY.size(); ++i)
                      {
                        TFData.at(i).frequency = parser.frequency.at(i);
                        TFData.at(i).Tx = parser.DataZX.at(i);
                        TFData.at(i).Ty = parser.DataZY.at(i);
                        TFData.at(i).dTx = parser.dDataZX.at(i);
                        TFData.at(i).dTy = parser.dDataZY.at(i);
                        TFData.at(i).Rz = parser.Rz.at(i);
                      }
                  }
              }
            catch (ANTLRException& e)
              {
                cerr << "Parse exception: " << e.toString() << endl;
              }
            Update();
          }
        else
          {
            throw FatalException("File not found: " + filename);
          }

      }
#endif

      //! Read output of Egbert's code, so far only supports files that contain only impedances and no tipper
      void ReadZmm(const std::string filename)
      {
        std::ifstream zmmfile(filename.c_str());
        latitude = 0.0;
        longitude = 0.0;
        elevation = 0.0;
        azimuth = 0.0;
        name = filename;
        double dummy, rotangle;
        std::string line = FindToken(zmmfile, "orientations");
        zmmfile >> dummy >> rotangle;
        try
          {
            while (zmmfile.good())
              {
                MTTensor CurrentImp;
                double period = 0.0;
                std::string periodline = FindToken(zmmfile, "period");
                if (zmmfile.good())
                  {
                    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

                    boost::char_separator<char> sep(" ");
                    tokenizer tok(periodline, sep);
                    tokenizer::iterator beg = tok.begin();
                    advance(beg, 2);
                    std::cout << *beg << std::endl;
                    convert(*beg, period);
                  }
                FindToken(zmmfile, "Transfer");
                if (zmmfile.good())
                  {
                    double zxx_re, zxx_im, zxy_re, zxy_im, zyx_re, zyx_im, zyy_re, zyy_im;
                    zmmfile >> zxx_re >> zxx_im >> zxy_re >> zxy_im >> zyx_re >> zyx_im
                        >> zyy_re >> zyy_im;
                    CurrentImp.frequency = 1.0 / period;
                    CurrentImp.Zxx = (zxx_re + I * zxx_im);
                    CurrentImp.Zxy = (zxy_re + I * zxy_im);
                    CurrentImp.Zyx = (zyx_re + I * zyx_im);
                    CurrentImp.Zyy = (zyy_re + I * zyy_im);

                  }
                double s11_re, s11_im, s21_re, s21_im, s22_re, s22_im;
                FindToken(zmmfile, "Inverse Coherent Signal Power Matrix");
                if (zmmfile.good())
                  {
                    zmmfile >> s11_re >> s11_im >> s21_re >> s21_im >> s22_re >> s22_im;
                  }
                FindToken(zmmfile, "Residual");
                double cov11_re, cov11_im, cov21_re, cov21_im, cov22_re, cov22_im;
                if (zmmfile.good())
                  {
                    zmmfile >> cov11_re >> cov11_im >> cov21_re >> cov21_im >> cov22_re
                        >> cov22_im;
                  }
                CurrentImp.dZxx = sqrt(
                    std::abs(
                        complex<double>(cov11_re, cov11_im)
                            * complex<double>(s11_re, s11_im)));
                CurrentImp.dZxy = sqrt(
                    std::abs(
                        complex<double>(cov11_re, cov11_im)
                            * complex<double>(s22_re, s22_im)));
                CurrentImp.dZyx = sqrt(
                    std::abs(
                        complex<double>(cov22_re, cov22_im)
                            * complex<double>(s11_re, s11_im)));
                CurrentImp.dZyy = sqrt(
                    std::abs(
                        complex<double>(cov22_re, cov22_im)
                            * complex<double>(s22_re, s22_im)));
                CurrentImp.rotangle = rotangle;
                MTData.push_back(CurrentImp);
                TFData.push_back(MagneticTF());
              }
          } catch (...)
          {

          }
      }
      //! Read mtf format for impedances by M. Smirnov
      void ReadMtf(const std::string filename)
      {
        std::ifstream mtffile(filename.c_str());
        latitude = 0.0;
        longitude = 0.0;
        elevation = 0.0;
        azimuth = 0.0;
        name = filename;
        std::string latline = FindToken(mtffile, ">LATITUDE");
        if (mtffile.good())
          {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> sep(":");
            tokenizer tok(latline, sep);
            tokenizer::iterator beg = tok.begin();
            advance(beg, 1);
            convert(*beg, latitude);
          }
        std::string lonline = FindToken(mtffile, ">LONGITUDE");
        if (mtffile.good())
          {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> sep(":");
            tokenizer tok(lonline, sep);
            tokenizer::iterator beg = tok.begin();
            advance(beg, 1);
            convert(*beg, longitude);
          }
        std::string line = FindToken(mtffile, "//SECTION=IMP");
        double rotangle, period;
        double zxx_re, zxx_im, zxy_re, zxy_im, zyx_re, zyx_im, zyy_re, zyy_im;
        double dzxx, dzxy, dzyx, dzyy;

        while (mtffile.good())
          {
            MTTensor CurrentImp;
            mtffile >> period >> rotangle >> zxx_re >> zxx_im >> dzxx >> zxy_re >> zxy_im
                >> dzxy >> zyx_re >> zyx_im >> dzyx >> zyy_re >> zyy_im >> dzyy;
            if (mtffile.good())
              {

                CurrentImp.frequency = 1.0 / period;
                CurrentImp.Zxx = (zxx_re - I * zxx_im);
                CurrentImp.Zxy = (zxy_re - I * zxy_im);
                CurrentImp.Zyx = (zyx_re - I * zyx_im);
                CurrentImp.Zyy = (zyy_re - I * zyy_im);
                CurrentImp.dZxx = dzxx;
                CurrentImp.dZxy = dzxy;
                CurrentImp.dZyx = dzyx;
                CurrentImp.dZyy = dzyy;
                CurrentImp.rotangle = rotangle;
                MTData.push_back(CurrentImp);
                TFData.push_back(MagneticTF());
              }

          }

      }

#ifdef HAVENETCDF
      void ReadNetCDF(const std::string filename)
      {
        std::vector<double> Frequencies,StatXCoord, StatYCoord, StatZCoord;
        gplib::rvec Impedances;
        ReadImpedancesFromNetCDF(filename, Frequencies, StatXCoord, StatYCoord, StatZCoord,Impedances);
        if (StatXCoord.size() != 1)
          {
            throw FatalException("Cannot have data for more than one station in netcdf file !");
          }
        const size_t nfreq = Frequencies.size();
        for (size_t i = 0; i < nfreq; ++i)
          {
            MTTensor CurrentImp;
            CurrentImp.frequency = Frequencies[i];
            CurrentImp.Zxx = (Impedances(i*8) + I * Impedances(i*8 +1));
            CurrentImp.Zxy = (Impedances(i*8 +2) + I * Impedances(i*8 +3));
            CurrentImp.Zyx = (Impedances(i*8 + 4) + I * Impedances(i*8 +5));
            CurrentImp.Zyy = (Impedances(i*8 + 6) + I * Impedances(i*8 +7));
            MTData.push_back(CurrentImp);
            TFData.push_back(MagneticTF());
          }
        name = filename;
        TrimFilename(name);
      }
#endif

#ifdef HAVEANTLR
    void MTStation::ReadEdi(const std::string filename)
      {
        using namespace antlr;
        std::ifstream infile(filename.c_str());
        const double invalid = 1e30;

        if (infile)
          {
            try
              {
                EDILexer lexer(infile);
                EDIParser parser(lexer);
                parser.edi_file();
                latitude = parser.latitude;
                longitude = parser.longitude;
                elevation = parser.elevation;
                azimuth = parser.azimuth;
                name = filename;
                TrimFilename(name);
                unsigned int valfreqs = 0;
                for (unsigned int i = 0; i < parser.frequency.size(); ++i)
                  {
                    if (abs(parser.DataXX.at(i)) > invalid)
                      {
                        parser.frequency.at(i) = 0;
                      }
                    else
                      {
                        valfreqs++;
                      }
                  }
                //frequency.assign(parser.frequency.size(),0);
                //copy(parser.frequency.begin(),parser.frequency.end(),frequency.begin());
                //rotangles.assign(parser.frequency.size(),0);
                if (!parser.rotangles.empty())
                  {
                    azimuth += parser.rotangles.at(0) * 180. / PI;
                  }
                Assign(valfreqs);
                unsigned int mtindex = 0;
                //There might be some invalid entries that we do not want to copy, we therefore
                //go through all parsed entries with the for loop, but have a separate index
                //for our storage class
                for (unsigned int i = 0; i < parser.rotangles.size(); ++i)
                  {
                    if (abs(parser.DataXX.at(i)) < invalid)
                      {
                        MTData.at(mtindex).frequency = parser.frequency.at(i);
                        MTData.at(mtindex).rotangle = parser.rotangles.at(i)
                        * PI / 180.;
                        MTData.at(mtindex).Zxx = parser.DataXX.at(i);
                        MTData.at(mtindex).Zxy = parser.DataXY.at(i);
                        MTData.at(mtindex).Zyx = parser.DataYX.at(i);
                        MTData.at(mtindex).Zyy = parser.DataYY.at(i);
                        MTData.at(mtindex).dZxx = parser.dDataXX.at(i);
                        MTData.at(mtindex).dZxy = parser.dDataXY.at(i);
                        MTData.at(mtindex).dZyx = parser.dDataYX.at(i);
                        MTData.at(mtindex).dZyy = parser.dDataYY.at(i);
                        mtindex++;
                      }
                  }
                mtindex = 0;
                if (parser.DataZY.empty() == false)
                  {
                    for (unsigned int i = 0; i < parser.DataZY.size(); ++i)
                      {
                        if (abs(parser.DataZX.at(i)) < invalid)
                          {
                            TFData.at(mtindex).frequency = parser.frequency.at(
                                i);
                            TFData.at(mtindex).Tx = parser.DataZX.at(i);
                            TFData.at(mtindex).Ty = parser.DataZY.at(i);
                            TFData.at(mtindex).dTx = parser.dDataZX.at(i);
                            TFData.at(mtindex).dTy = parser.dDataZY.at(i);
                            mtindex++;
                          }
                      }
                  }
              }
            catch (ANTLRException& e)
              {
                cerr << "Parse exception: " << e.toString() << endl;
              }
            Update();
          }
        else
          {
            throw FatalException("File not found: " + filename);
          }
      }
#endif

      // helper function for WriteAsJ
      void WriteJBlock(boost::function<std::complex<double>(const MTTensor*)> Comp,
          boost::function<double(const MTTensor*)> Err, std::ofstream &outfile,
          const double convfactor)
      {
        for (unsigned int i = 0; i < MTData.size(); ++i)
          {
            if (MTData.at(i).frequency != 0)
              {
                outfile << setfill(' ') << setw(15) << resetiosflags(ios::fixed)
                    << 1. / MTData.at(i).frequency << " ";
                outfile << setfill(' ') << setw(15)
                    << convfactor * boost::bind(Comp, &MTData.at(i))().real() << " ";
                outfile << setfill(' ') << setw(15)
                    << convfactor * boost::bind(Comp, &MTData.at(i))().imag() << " ";
                outfile << setfill(' ') << setw(15)
                    << convfactor * boost::bind(Err, &MTData.at(i))() << " ";
                outfile << setfill(' ') << setw(15) << setiosflags(ios::fixed) << 1.000
                    << " " << endl;
              }
          }
      }
    protected:
      //! Update all derived quantities
      void Update()
      {}
      //! Assign() assigns zero to all derived quantities, this makes the calculation
      // more easy
      void Assign(const int nfreq)
      {
        MTData.assign(nfreq, MTTensor());
        TFData.assign(nfreq, MagneticTF());
      }
    public:
      // Assign zero to everything, convenient for synthetic data that is not read in from file
      void AssignAll(const int nfreq)
      {
        Assign(nfreq);
      }
      //! Given a rotation angle in radian this method rotates the impedance tensor
      //! and updates all derived quantities
      void Rotate(const double rotangle)
      {
        for (unsigned int i = 0; i < MTData.size(); ++i)
          {
            DoRotate(i, rotangle);
          }
        Update();
      }
      //! Rotate to zero rotation angle
      void Rotate(void)
      {
        for (unsigned int i = 0; i < MTData.size(); ++i)
          {
            DoRotate(i, -MTData.at(i).rotangle);
          }
        Update();
      }
      //! return the available frequencies in a single vector
      trealdata GetFrequencies() const
      {
        trealdata temp(MTData.size());
        transform(MTData.begin(), MTData.end(), temp.begin(), [](MTTensor val)
          { return val.GetFrequency();});
        return temp;
      }
      //! Set the frequencies of the tensor elements, invalidates the previously stored impedance data, mainly for creating synthetic data
      void SetFrequencies(const trealdata &freqs)
      {
        //assert(MTData.size() == freqs.size());
        const unsigned int nfreqs = freqs.size();
        if (MTData.size() != nfreqs) //this invalidates the data stored there before
          {
            MTData.resize(nfreqs);
            TFData.resize(nfreqs);
          }
        for (unsigned int i = 0; i < nfreqs; ++i)
          MTData.at(i).frequency = freqs.at(i);
        assert(MTData.size() == TFData.size());

      }
      //! access funtion for Latitude
      double GetLatitude() const
        {
          return latitude;
        }
      void SetLatitude(double lat)
        {
          latitude = lat;
        }
      double GetLongitude() const
        {
          return longitude;
        }
      void SetLongitude(double lon)
        {
          longitude = lon;
        }
      double GetElevation() const
        {
          return elevation;
        }
      std::string GetName()
        {
          return name;
        }
      double GetAzimuth() const
        {
          return azimuth;
        }
      ;
      //! direct acces to a tensor at a given index
      const MTTensor &at(const unsigned int i) const
        {
          return MTData.at(i);
        }
      //! Get the full vector of Tensor elements read only
      const std::vector<MTTensor> &GetMTData() const
        {
          return MTData;
        }
      //! Get the full vector of Tensor elements for reading and writing
      std::vector<MTTensor> &SetMTData()
        {
          return MTData;
        }
      //! for parallel runs we need to make a copy of the object and its derived classes
      virtual MTStation *clone() const
        {
          return new MTStation(*this);
        }
      MTStation& operator=(const MTStation& source)
      {
        if (this == &source)
          return *this;

        copy(source.MTData.begin(), source.MTData.end(), back_inserter(this->MTData));
        copy(source.TFData.begin(), source.TFData.end(), back_inserter(this->TFData));

        this->latitude = source.latitude;
        this->longitude = source.longitude;
        this->elevation = source.elevation;
        this->azimuth = source.azimuth;
        this->name = source.name;
        this->dataformat = source.dataformat;
        this->Update();
        return *this;
      }
      MTStation()
      {
        InitialSetup();
      }
      MTStation(const MTStation &old) :
          latitude(old.latitude), longitude(old.longitude), elevation(old.elevation), name(
              old.name), azimuth(old.azimuth), MTData(old.MTData), TFData(old.TFData),

          dataformat(old.dataformat)
        {
          Update();
        }

      MTStation(const int size):
          MTData(size)
        {
          InitialSetup();
          Assign(size);
        }
      MTStation(const std::string filename)
      {
        InitialSetup();
        GetData(filename);
      }
      virtual ~MTStation()
      {

      }
      //! read in data from file, determines format by ending
      virtual void GetData(const std::string filename)
      {
        if (!boost::filesystem::exists(filename))
          throw FatalException("File does not exist : " + filename);
        string ending = boost::filesystem::extension(filename);
        boost::to_lower(ending);
        if (ending == "")
          {
            cerr << "File has no extension ! " << filename << endl;
            dataformat = unknown;
            throw FatalException("File has no extension ! " + filename);
          }
        dataformat = MTFileTypes.at(ending);

        switch (dataformat)
          {
        case mtt:
          ReadMtt(filename);
          break;
        case j:
#ifdef HAVEANTLR
          ReadJ(filename);
#else
          throw FatalException("Did not compile with .j support");
#endif
          break;
        case edi:
#ifdef HAVEANTLR
          ReadEdi(filename);
#else
          throw FatalException("Did not compile with .edi support");
#endif
          break;
        case pek:
          ReadPek1D(filename);
          break;
        case zmm:
          ReadZmm(filename);
          break;
        case mtf:
          ReadMtf(filename);
          break;
        case nc:
#ifdef HAVENETCDF
          ReadNetCDF(filename);
#else
          throw FatalException("Did not compile with .nc support");
#endif
          break;
        default:
          throw FatalException(
              "Unknown File Format for Reading ! This should not happen");
          }
        assert(MTData.size() == TFData.size());
        Rotate(); //rotate data to 0 degree

      }

      virtual void GetData()
        {
        }
      //Write data to file, same as WriteBack
      virtual void WriteData(const std::string filename)
      {
        name = filename;
        WriteBack();
      }
      friend class C1DMTSynthData;
      //! Write data in goettingen .mtt format
      void WriteAsMtt(const std::string filename)
      {
        Update();
        WriteMtt((filename + ".mtt").c_str());
      }
      //! Write data as edi (no functionality yet)
      void WriteAsEdi(const std::string filename)
      {
        throw FatalException("WriteAsEdi not implemented yet !");
      }

      //! Write data to j-file
      void WriteAsJ(const std::string filename)
      {
        ofstream outfile;
        outfile.open((filename + ".j").c_str());
        int actfreqs = 0;
        const double convfactor = 4. * acos(-1.) * 1e-4;

        outfile << "# J-File Produced by CJData.cpp" << endl;
        outfile << ">LATITUDE  = " << latitude << endl;
        outfile << ">LONGITUDE = " << longitude << endl;
        outfile << ">ELEVATION = " << elevation << endl;
        outfile << ">AZIMUTH   = " << azimuth << endl;
        outfile << name << endl;
        for (unsigned int i = 0; i < MTData.size(); ++i)
          if (MTData.at(i).frequency != 0)
            actfreqs++;
        outfile << "ZXX S.I." << endl;
        outfile << actfreqs << endl;
        //WriteJBlock(DataXX,outfile,convfactor);
        WriteJBlock(&MTTensor::GetZxx, &MTTensor::GetdZxx, outfile, convfactor);
        outfile << "ZXY S.I." << endl;
        outfile << actfreqs << endl;
        WriteJBlock(&MTTensor::GetZxy, &MTTensor::GetdZxy, outfile, convfactor);

        outfile << "ZYX S.I." << endl;
        outfile << actfreqs << endl;
        WriteJBlock(&MTTensor::GetZyx, &MTTensor::GetdZyx, outfile, convfactor);

        outfile << "ZYY S.I." << endl;
        outfile << actfreqs << endl;
        WriteJBlock(&MTTensor::GetZyy, &MTTensor::GetdZyy, outfile, convfactor);

        /*	if (norm(DataZY.Z.at(0)) !=0)
         {
         outfile << "TZX " << endl;
         outfile << actfreqs << endl;
         WriteJBlock(DataZX,outfile,1.);
         }

         if (norm(DataZY.Z.at(0)) !=0)
         {
         outfile << "TZY " << endl;
         outfile << actfreqs << endl;
         WriteJBlock(DataZY,outfile,1.);
         }*/
        outfile.close();
      }

      //! Write data back in original format, with filename given by station name
      void WriteBack()
      {
        switch (dataformat)
          {
        case mtt:
          WriteAsMtt(name.c_str());
          break;
        case j:
          WriteAsJ(name.c_str());
          break;
        case edi:
          WriteAsEdi(name.c_str());
          break;
        default:
          throw FatalException(
              "Unknown File Format for Writing ! This should not happen");
          }

      }
      };

/* @} */
}
#endif // CMTSTATION_H
