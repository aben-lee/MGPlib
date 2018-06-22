#ifndef ANISOSURFACEWAVEMODEL_H_
#define ANISOSURFACEWAVEMODEL_H_

#include "types.h"
#include <string>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <boost/bind.hpp>
#include <string>
#include <boost/filesystem.hpp>
#include "FatalException.h"
#include <iostream>

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! A class to store information about anisotropic surface wave models
    /*! This class stores 1D anisotropic seismic models. At the moment
     * we use these models to calculate surface waves with AnisoSurfaceWaveSynthetic,
     * but in general it can be used for other seismic methods as well.
     */

    class AnisoSurfaceWaveModel
      {
    private:
      //! The thickness of each layer in km
      trealdata thicknesses;
      //! The P-wave velocity of each layer in km/s
      trealdata vp;
      //! The S-wave velocity of each layer in km/s
      trealdata vs;
      //! The apparent S-wave velocity of each layer in km/s
      trealdata vsapp;
      //three anisotropy coefficients
      trealdata Temp; // Temporary coefficient (-/+B)
      trealdata Temp2; // another temporary coefficient
      trealdata B;
      trealdata C;
      trealdata E;
      trealdata anisoS;
      //and two anisotropy angles
      trealdata theta;
      trealdata phi;
      trealdata angle1;
      //! The density of each layer in g/cm^3
      trealdata densities;
    public:
      //! Get read-only access to the vector of layer thicknesses in km
      const trealdata &GetThicknesses() const
        {
          return thicknesses;
        }
      //! Get read-only access to the vector of P-wave velocities in km/s
      const trealdata &GetVp() const
        {
          return vp;
        }
      //! Get read-only access to the vector of S-wave velocities in km/s
      const trealdata &GetVs() const
        {
          return vs;
        }
      //! Get read-only access to the vector of apparent S-wave velocities in km/s
      const trealdata &GetVsapp() const
        {
          return vsapp;
        }
      //! Get read-only access to the vector of S-wave velocities in km/s
      const trealdata &GetAngle1() const
        {
          return angle1;
        }
      //! Get read-only access to the vector of anisotropy coefficients for each layer
      const trealdata &GetB() const
        {
          return B;
        }
      //! Get read-only access to the vector of anisotropy coefficients for each layer
      const trealdata &GetTemp() const
        {
           return Temp;
        }
      const trealdata &GetTemp2() const
        {
           return Temp2;
        }
      //! Get read-only access to the vector of anisotropy coefficients for each layer
      const trealdata &GetC() const
        {
          return C;
        }
      //! Get read-only access to the vector of anisotropy coefficients for each layer
      const trealdata &GetE() const
        {
          return E;
        }
      //! Get read-only access to the vector of anisotropy coefficients for each layer
      const trealdata &GetAnisoS() const
        {
          return anisoS;
        }
      //! Get read-only access to the vector of anisotropy angles theta for each layer
      const trealdata &GetTheta() const
        {
          return theta;
        }
      //! Get read-only access to the vector of anisotropy angles phi for each layer
      const trealdata &GetPhi() const
        {
          return phi;
        }
      //! Get read-only access to the vector densities for each layer
      const trealdata &GetDensities() const
        {
          return densities;
        }
      //! Set the vector of layer thicknesses in km
      trealdata &SetThicknesses()
        {
          return thicknesses;
        }
      //! Set the vector of P-wave velocities in km/s
      trealdata &SetVp()
        {
          return vp;
        }
      //! Set the vector of S-wave velocities in km/s
      trealdata &SetVs()
        {
          return vs;
        }
      //! Set the vector of S-wave velocities in km/s
      trealdata &SetVsapp()
        {
          return vsapp;
        }
      //! Set the vector of S-wave velocities in km/s
      trealdata &SetAngle1()
        {
          return angle1;
        }
      //! Set the vector of anisotropy coefficients B
      trealdata &SetB()
        {
          return B;
        }
      //! Set the vector of temporary coefficient Temp
      trealdata &SetTemp()
        {
          return Temp;
        }
      //! Set the vector of temporary coefficient Temp2
      trealdata &SetTemp2()
        {
          return Temp2;
        }
      //! Set the vector of anisotropy coefficients C
      trealdata &SetC()
        {
          return C;
        }
      //! Set the vector of anisotropy coefficients E
      trealdata &SetE()
        {
          return E;
        }
      //! Set the vector of anisotropy coefficients E
      trealdata &SetAnisoS()
        {
          return anisoS;
        }
      //! Set the vector of anisotropy angles theta
      trealdata &SetTheta()
        {
          return theta;
        }
      //! Set the vector of anisotropy angles phi
      trealdata &SetPhi()
        {
          return phi;
        }
      //! Set the vector of densities
      trealdata &SetDensities()
        {
          return densities;
        }
      //! Read the model information from an ascii file with name filename
      void ReadModel(const std::string &filename)
      {
        std::cout << "Read Model " << std::endl;
      }

      // Function Read Model for MODES
       /*void ReadModel(const std::string &filename)
       {
       std::ifstream infile(filename.c_str());
       size_t nlayers = 0;
       const size_t titlelength = 512;
       char title[titlelength];
       //the first line of the model is the title that we don't care about
       infile.getline(title, titlelength);
       //the second layer is fixed parameters we don't care about
       infile >> 0 >> 50 >> 1;
       //the number of layers in the model does include the bottom fixed model (14 layers) + layers for boundaries
       infile >> nlayers >> 3 >> 5;
       //so the number of inverted layers
       nlayers = (nlayers - 15)/2 + 1;
       //there can be comments at the end of each line
       //so read the rest of the line, if nothing is there, it only reads the newline
       infile.getline(title, titlelength);
       //reserve memory for all the parameters
       // for a uniform in half-space
       thicknesses.assign(nlayers, 0.0);
       vp.assign(nlayers, 0.0);
       vsapp.assign(nlayers, 0.0);
       B.assign(nlayers, 0.0);
       C.assign(nlayers, 0.0);
       E.assign(nlayers, 0.0);
       theta.assign(nlayers, 0.0);
       phi.assign(nlayers, 0.0);
       densities.assign(nlayers, 0.0);
       //we read the fixed bottom part of the model
       infile >> 0 >> 13012.20 >> 11218.76 >> 3613.67 >> 99999 >> 85 >> 6371.00;
       infile >> 101430 >> 13010.00 >> 11217.18 >> 3612.58 >> 99999 >> 85 >> 6269.57;
       infile >> 1217500 >> 12703.70 >> 11002.11 >> 3452.58 >> 99999 >> 85 >> 5153.50;
       infile >> 1217500 >> 12139.10 >> 10288.78 >> 0.00 >> 99999 >> 0.0 >> 5153.50;
       infile >> 3479500 >> 9914.50 >> 7999.83 >> 0.00 >> 99999 >> 0.0 >> 2891.50;
       infile >> 3479500 >> 5772.10 >> 13621.92 >> 7248.53 >> 99999 >> 274.0 >> 2891.50;
       infile >> 3878500 >> 5331.30 >> 13330.80 >> 7112.86 >> 99999 >> 371.8 >> 2492.50;
       infile >> 4373500 >> 5102.70 >> 12771.47 >> 6898.60 >> 99999 >> 414.9 >> 1997.50;
       infile >> 4868500 >> 4856.20 >> 12170.18 >> 6663.31 >> 99999 >> 463.0 >> 1502.50;
       infile >> 5363500 >> 4592.60 >> 11452.03 >> 6370.39 >> 99999 >> 510.2 >> 1007.50;
       infile >> 5711000 >> 4238.70 >> 10775.04 >> 5947.18 >> 99999 >> 549.5 >> 660.00;
       infile >> 5711000 >> 3920.10 >> 10152.58 >> 5569.85 >> 99999 >> 172.9 >> 660.00;
       infile >> 5961000 >> 3931.70 >> 9314.71 >> 5041.52 >> 99999 >> 162.5 >> 410.00;
       infile >> 5961000 >> 3467.98 >> 8435.09 >> 4870.00 >> 99999 >> 140.0 >> 410.00;
       //then we read the boundary between layer n-1 and fixed part of the model
       double currdepth =0.0;
       double currdepth_center = 0.0;
       infile >> currdepth_center >> densities.at(nlayers-1) >> vp.at(nlayers-1) >> vsapp.at(nlayers-1)
       >> 99999 >> 100 >> currdepth;
       thicknesses(nlayers-1) = 410.00 - currdepth;
       //finally we read the inverted part of the model
       int i = nlayers -2;
       while (i >= 0)
       {
       infile >> currdepth_center >> densities.at(i) >> vp.at(i) >> vsapp.at(i) >> 99999
       >> 100 >> currdepth;
       infile >> currdepth_center + thicknesses.at(i) >> densities.at(i) >> vp.at(i) >> vsapp.at(i) >> 99999
       >> 100 >> currdepth - thicknesses.at(i)/1000;
       i--;
       }
       //transform from m to km for thickness and velocities and kg/m^3 to g/cm^3 for density
       vp.at(i) /= 1000.0;
       vsapp.at(i) /= 1000.0;
       densities.at(i) /= 1000.0;
       thicknesses.at(i) /=1000.0;
       }
       */

      //! Write the model to a file with name filename
      void WriteModel(const std::string &filename) const
      {
        const size_t nlayers = thicknesses.size();
        //check that all the layers have all parameters
        assert(nlayers> 0);
        assert(thicknesses.size() == nlayers);
        assert(vp.size() == nlayers);
        assert(vsapp.size() == nlayers);
        assert(densities.size() == nlayers);
        assert(B.size() == nlayers);
        assert(C.size() == nlayers);
        assert(phi.size() == nlayers);
        std::ofstream outfile(filename.c_str());
        //we have to write some title
        outfile << "title" << std::endl;
        //the code needs some parameters (reference freq = 50 Hz)
        outfile << 0 << " " << 50 << " " << 1 << " " << std::endl;
        //the code needs the numbers of layers in the model / number of lay. in inner / outer core
        outfile << (nlayers - 1) * 2 + 1 + 14 << " " << 3 << " " << 5 << " "
            << std::endl;
        //Model fixed from 410 km to the center of the Earth
        outfile << 0 << " " << 13012.20 << " " << 11218.76 << " " << 3613.67
            << " " << 99999 << " " << 85 << " " << 6371.00 << " " << "\n";
        outfile << 101430 << " " << 13010.00 << " " << 11217.18 << " "
            << 3612.58 << " " << 99999 << " " << 85 << " " << 6269.57 << " "
            << "\n";
        outfile << 1217500 << " " << 12703.70 << " " << 11002.11 << " "
            << 3452.58 << " " << 99999 << " " << 85 << " " << 5153.50 << " "
            << "\n";
        outfile << 1217500 << " " << 12139.10 << " " << 10288.78 << " " << 0.00
            << " " << 99999 << " " << 0.0 << " " << 5153.50 << " " << "\n";
        outfile << 3479500 << " " << 9914.50 << " " << 7999.83 << " " << 0.00
            << " " << 99999 << " " << 0.0 << " " << 2891.50 << " " << "\n";
        outfile << 3479500 << " " << 5772.10 << " " << 13621.92 << " "
            << 7248.53 << " " << 99999 << " " << 274.0 << " " << 2891.50 << " "
            << "\n";
        outfile << 3878500 << " " << 5331.30 << " " << 13330.80 << " "
            << 7112.86 << " " << 99999 << " " << 371.8 << " " << 2492.50 << " "
            << "\n";
        outfile << 4373500 << " " << 5102.70 << " " << 12771.47 << " "
            << 6898.60 << " " << 99999 << " " << 414.9 << " " << 1997.50 << " "
            << "\n";
        outfile << 4868500 << " " << 4856.20 << " " << 12170.18 << " "
            << 6663.31 << " " << 99999 << " " << 463.0 << " " << 1502.50 << " "
            << "\n";
        outfile << 5363500 << " " << 4592.60 << " " << 11452.03 << " "
            << 6370.39 << " " << 99999 << " " << 510.2 << " " << 1007.50 << " "
            << "\n";
        outfile << 5711000 << " " << 4238.70 << " " << 10775.04 << " "
            << 5947.18 << " " << 99999 << " " << 549.5 << " " << 660.00 << " "
            << "\n";
        outfile << 5711000 << " " << 3920.10 << " " << 10152.58 << " "
            << 5569.85 << " " << 99999 << " " << 172.9 << " " << 660.00 << " "
            << "\n";
        outfile << 5961000 << " " << 3931.70 << " " << 9314.71 << " "
            << 5041.52 << " " << 99999 << " " << 162.5 << " " << 410.00 << " "
            << "\n";
        // we fix Vs=4.87 km/s at 410 km in Germany
        outfile << 5961000 << " " << 3467.98 << " " << 8435.09 << " "
            << 4870.00 << " " << 99999 << " " << 140.0 << " " << 410.00 << " "
            << "\n";
        // we fix Vs=5.00 km/s at 410 km depth in Slave
        //          outfile << 5961000 << " " << 3540.00 << " " << 9000.00 << " " << 5000.00 << " " << 99999 << " "
        //                  << 140.0 << " " << 410.00 << " " << "\n";

        //we compute currdepth = maximum depth inverted
        double currdepth = 0.0;
        for (size_t j = 0; j < nlayers - 1; j++)
          {
            currdepth += thicknesses.at(j);
          }
        double currdepth_center = (6371 - currdepth) * 1000;
        //the layer n-1 is not inverted for the seismic model: the thickness is fixed to 410 - currdepth
        //and we impose a gradient between Vs(nlayer - 2) and 4.87km/s (fixed at 410 km depth)
        outfile << currdepth_center << " " << (vs.at(nlayers - 2) * 0.554
            + 0.77) * 1000 << " " << vs.at(nlayers - 2) * 1.80 * 1000 << " "
            << vs.at(nlayers - 2) * 1000.0 << " " << 99999 << " " << 100 << " "
            << currdepth << " " << "\n";

        int i = nlayers - 2;
        while (i >= 0)
          {
            outfile << currdepth_center << " " << densities.at(i) * 1000.0
                << " " << vp.at(i) * 1000 << " " << vsapp.at(i) * 1000.0 << " "
                << 99999 << " " << 100 << " " << currdepth << " " << "\n";
            //calculate the distance to the center of the Earth in m
            currdepth -= thicknesses.at(i);
            //calculate the distance to the surface in km
            currdepth_center += thicknesses.at(i) * 1000;
            //write out the different parameters
            outfile << currdepth_center << " " << densities.at(i) * 1000.0
                << " " << vp.at(i) * 1000 << " " << vsapp.at(i) * 1000.0 << " "
                << 99999 << " " << 100 << " " << currdepth << " " << "\n";
            i--;
          }
      }
      //! Write out a script that computes synthetic data for a model with name filename+.dat
      void WriteRunFile(const std::string &filename) const
      {
        std::ofstream runfile(filename.c_str());
        std::ofstream inputfile((filename + ".in").c_str());
        inputfile << "isomodel" << " " << std::endl;
        inputfile << "output" << " " << std::endl;
        inputfile << "phase" << " " << std::endl;
        // periods for Germany and synthetics
        inputfile << 34 << " " << std::endl;
        inputfile << 14.08 << " " << 14.49 << " " << 14.92 << " " << 15.38
            << " " << 15.87 << " " << 16.39 << " " << 16.94 << " " << 17.54
            << " " << 18.18 << " " << 18.86 << " " << 19.60 << " " << 20.40
            << " " << 21.27 << " " << 22.22 << " " << 23.25 << " " << 24.39
            << " " << 25.64 << " " << 27.02 << " " << 29.41 << " " << 31.25
            << " " << 33.33 << " " << 35.71 << " " << 38.46 << " " << 41.66
            << " " << 45.45 << " " << 50. << " " << 55.55 << " " << 62.50
            << " " << 71.42 << " " << 83.33 << " " << 100. << " " << 125.
            << " " << 166.66 << " " << 250. << " " << std::endl;
        // periods for Slave
        /*    inputfile << 31 << " " << std::endl;
         inputfile << 15.15 << " " << 15.62 << " " << 16.12 << " " << 16.67 << " " << 17.24 << " " << 17.86
         << " " << 18.52 << " " << 19.23 << " " << 20.00 << " " << 20.83 << " " << 21.74 << " " << 22.73
         << " " << 23.81 << " " << 25.00 << " " << 26.31 << " " << 27.78 << " " << 29.41 << " " << 31.25
         << " " << 33.33 << " " << 35.71 << " " << 38.46 << " " << 41.67 << " " << 45.45 << " " << 50.00
         << " " << 55.55 << " " << 62.50 << " " << 71.40 << " " << 83.33 << " " << 100. << " " << 125.
         << " " << 166.67 << " " << std::endl;
         */
        boost::filesystem::path Path(filename);
        std::string dirname(filename + "_dir");
        runfile << "#!/bin/bash" << std::endl;
        runfile << "mkdir " << dirname << std::endl;
        runfile << "mv " << filename << ".* " << dirname << std::endl;
        runfile << "cd " << dirname << std::endl;
        runfile << "cp " << Path.leaf() << ".mod isomodel" << std::endl;
        runfile << "cp " << Path.leaf() << ".in input" << std::endl;
        // Run on Wegener
        runfile << "isoraylC_fund < input 2>&1> /dev/null" << std::endl;
        runfile << "cp �MXAe ../" << filename + ".cvel" << std::endl;
        // Run on Stokes
        //    runfile << "../bin/isoraylC_fund < input 2>&1> /dev/null" << std::endl;
        //    runfile << "cp phase ../" << filename + ".cvel" << std::endl;
        if (!runfile.good())
          throw FatalException("Problem writing to file: " + filename);
      }

      //!Write out an ascii file for plotting the model with xmgrace
      void WritePlot(const std::string &filename) const
      {
        std::ofstream outfile(filename.c_str());
        const size_t nlayers = thicknesses.size();
        outfile << 3613.67 / 1000 << " " << 0 << " " << 0 << " " << 6371.00
            << " " << "\n";
        outfile << 3612.58 / 1000 << " " << 0 << " " << 0 << " " << 6269.57
            << " " << "\n";
        outfile << 3452.58 / 1000 << " " << 0 << " " << 0 << " " << 5153.50
            << " " << "\n";
        outfile << 0.00 << " " << 0 << " " << 0 << " " << 5153.50 << " "
            << "\n";
        outfile << 0.00 << " " << 0 << " " << 0 << " " << 2891.50 << " "
            << "\n";
        outfile << 7248.53 / 1000 << " " << 0 << " " << 0 << " " << 2891.50
            << " " << "\n";
        outfile << 7112.86 / 1000 << " " << 0 << " " << 0 << " " << 2492.50
            << " " << "\n";
        outfile << 6898.60 / 1000 << " " << 0 << " " << 0 << " " << 1997.50
            << " " << "\n";
        outfile << 6663.31 / 1000 << " " << 0 << " " << 0 << " " << 1502.50
            << " " << "\n";
        outfile << 6370.39 / 1000 << " " << 0 << " " << 0 << " " << 1007.50
            << " " << "\n";
        outfile << 5947.18 / 1000 << " " << 0 << " " << 0 << " " << 660.00
            << " " << "\n";
        outfile << 5569.85 / 1000 << " " << 0 << " " << 0 << " " << 660.00
            << " " << "\n";
        outfile << 5041.52 / 1000 << " " << 0 << " " << 0 << " " << 410.00
            << " " << "\n";
        outfile << 4870.00 / 1000 << " " << 0 << " " << 0 << " " << 410.00
            << " " << "\n"; // Germany
        //    outfile << 5000.00/1000 << " " << 0 << " " << 0 << " " << 410.00 << " " << "\n";    // Slave
        int j = 0;
        //we compute currdepth = maximum depth inverted
        double currdepth = 0.0;
        for (j = 0; j < nlayers - 1; j++)
          {
            currdepth += thicknesses.at(j);
          }
        double currdepth_center = (6371 - currdepth) * 1000;
        //one boundary for last inverted layer (thickness is not inverted but fixed to 410 - currdepth)
        //we have a gradient between currdepth and 410 km depth
        outfile << vs.at(nlayers - 2) << " " << 0 << " " << 0 << " "
            << currdepth << " " << "\n";
        int i = nlayers - 2;
        while (i >= 0)
          {
            outfile << vs.at(i) << " " << B.at(i) << " " << phi.at(i) << " "
                << currdepth << " " << "\n";
            //calculate the distance to the center of the Earth in m
            currdepth -= thicknesses.at(i);
            //calculate the distance to the surface in km
            currdepth_center += thicknesses.at(i) * 1000;
            //write out the different parameters
            outfile << vs.at(i) << " " << B.at(i) << " " << phi.at(i) << " "
                << currdepth << " " << "\n";
            i--;
          }
      }
      //we use the compiler generated copy constructor and operator
      AnisoSurfaceWaveModel();
      virtual ~AnisoSurfaceWaveModel();
      };
  /* @} */
  }
#endif /*ANISOSURFACEWAVEMODEL_H_*/
