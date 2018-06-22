//============================================================================
// Name        : ReadWriteImpedances.h
// Author      : Jul 13, 2009
// Version     : 
// Copyright   : 2009, mmoorkamp
//============================================================================


#ifndef READWRITEIMPEDANCES_H_
#define READWRITEIMPEDANCES_H_

#include "../Global/VecMat.h"
#include <netcdfcpp.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "../Global/Util.h"

namespace gplib
  {
//! The name used for the x-coordinates of the measurements in netcdf files
static const std::string MeasPosXName = "MeasPosX";
//! The name used for the y-coordinates of the measurements in netcdf files
static const std::string MeasPosYName = "MeasPosY";
//! The name used for the z-coordinates of the measurements in netcdf files
static const std::string MeasPosZName = "MeasPosZ";
//! The name used for the index of the measurements in netcdf files
static const std::string StationNumberName = "StationNumber";

//! Read a vector from a netcdf file
template<class VectorType>
void ReadVec(NcFile &NetCDFFile, const std::string &DataName,
    const std::string &DimName, VectorType &Position)
  {
    //create a netcdf dimension for the Station number
    NcDim *Dim = NetCDFFile.get_dim(DimName.c_str());
    //determine the size of that dimension
    const size_t nvalues = Dim->size();

    //allocate memory in the class variable
    Position.resize(nvalues);
    // create netcdf variable with the same name as the dimension
    NcVar *SizeVar = NetCDFFile.get_var(DataName.c_str());
    //read coordinate values from netcdf file
    SizeVar->get(&Position[0], nvalues);
  }

//! Write a vectorial quantity to a netcdf file
template<class VectorType>
void WriteVec(NcFile &NetCDFFile, const std::string &MeasPosName,
    const VectorType &Position, NcDim *Dimension, const std::string unit)
  {
    const size_t nmeas = Position.size();
    NcVar *PosVar = NetCDFFile.add_var(MeasPosName.c_str(), ncDouble,
        Dimension);
    PosVar->add_att("units", unit.c_str());
    PosVar->put(&Position[0], nmeas);
  }

const std::string FreqDimName = "Frequency";
//write one compoment of the impedance tensor to a netcdf file
//this is an internal helper function
void WriteImpedanceComp(NcFile &NetCDFFile, NcDim *StatNumDim,
    NcDim *FreqDim, const gplib::rvec &Impedances,
    const std::string &CompName, const size_t compindex)
  {
    NcVar *CompVar = NetCDFFile.add_var(CompName.c_str(), ncDouble,
        FreqDim, StatNumDim);
    gplib::rvec Component(FreqDim->size() * StatNumDim->size());
    for (size_t i = 0; i < Component.size(); ++i)
      {
        Component(i) = Impedances(i * 8 + compindex);
      }
    CompVar->put(&Component[0], FreqDim->size(), StatNumDim->size());
  }
//read one compoment of the impedance tensor from a netcdf file
//this is an internal helper function
void ReadImpedanceComp(NcFile &NetCDFFile, gplib::rvec &Impedances,
    const std::string &CompName, const size_t compindex)
  {
    NcVar *SizeVar = NetCDFFile.get_var(CompName.c_str());
    const size_t nvalues = Impedances.size() / 8;
    gplib::rvec Temp(nvalues);
    SizeVar->get(&Temp[0], SizeVar->edges()[0], SizeVar->edges()[1]);
    for (size_t i = 0; i < nvalues; ++i)
      {
        Impedances(i * 8 + compindex) = Temp(i);
      }

  }

    /** \addtogroup mtmodelling Forward modelling of magnetotelluric data */
    /* @{ */
    //! Write magnetotelluric impedances to a netcdf file
    /*! We can save MT impedances for several stations in a netcdf file for storage
     * and analysis with external programs.
     * @param filename The name for the netcdf file
     * @param Frequencies The vector of frequencies in Hz for the impedances in the vector Impedances
     * @param StatXCoord The x-coordinates (North) of the measurement stations for the impedances in m
     * @param StatYCoord The y-coordinates (East) of the measurement stations for the impedances in m
     * @param StatZCoord The z-coordinates (Down) of the measurement stations for the impedances in m
     * @param Impedances The impedances as a vector of real numbers. 8 consecutive elements form the impedance matrix for one frequency and site, all impedances for one frequency and all stations form a contiguous block, the frequencies vary slowest.
     */
    void WriteImpedancesToNetCDF(const std::string &filename,
        const std::vector<double> &Frequencies,
        const std::vector<double> &StatXCoord,
        const std::vector<double> &StatYCoord,
        const std::vector<double> &StatZCoord, const gplib::rvec &Impedances)
    {
      const size_t nstats = StatXCoord.size();
      const size_t nfreqs = Frequencies.size();
      assert(nstats == StatYCoord.size());
      assert(nstats == StatYCoord.size());
      assert(Impedances.size() == nstats * nfreqs * 8);
      //create a netcdf file
      NcFile DataFile(filename.c_str(), NcFile::Replace);
      //each station gets an index number that we use as a dimension
      //in the netcdf file
      NcDim *StatNumDim = DataFile.add_dim(StationNumberName.c_str(), nstats);
      std::vector<int> StationNumber;
      std::generate_n(back_inserter(StationNumber), nstats, IntSequence(0));
      NcVar *StatNumVar = DataFile.add_var(StationNumberName.c_str(), ncInt,
          StatNumDim);
      StatNumVar->put(&StationNumber[0], nstats);
      //write out the measurement coordinates
      WriteVec(DataFile, MeasPosXName, StatXCoord, StatNumDim, "m");
      WriteVec(DataFile, MeasPosYName, StatYCoord, StatNumDim, "m");
      WriteVec(DataFile, MeasPosZName, StatZCoord, StatNumDim, "m");
      //write out the frequencies that we store
      NcDim *FreqDim = DataFile.add_dim(FreqDimName.c_str(),
          Frequencies.size());
      NcVar *FreqVar = DataFile.add_var(FreqDimName.c_str(), ncDouble,
          FreqDim);
      FreqVar->put(&Frequencies[0], nfreqs);
      //and now we can write all the impedance components
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zxx_re",
          0);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zxx_im",
          1);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zxy_re",
          2);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zxy_im",
          3);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zyx_re",
          4);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zyx_im",
          5);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zyy_re",
          6);
      WriteImpedanceComp(DataFile, StatNumDim, FreqDim, Impedances, "Zyy_im",
          7);
    }

    //! Read magnetotelluric impedances from a netcdf file
    /*! Read MT impedances for several stations from a netcdf file.
     * @param filename The name for the netcdf file
     * @param Frequencies The vector of frequencies in Hz for the impedances in the vector Impedances
     * @param StatXCoord The x-coordinates (North) of the measurement stations for the impedances in m
     * @param StatYCoord The y-coordinates (East) of the measurement stations for the impedances in m
     * @param StatZCoord The z-coordinates (Down) of the measurement stations for the impedances in m
     * @param Impedances The impedances as a vector of real numbers. 8 consecutive elements form the impedance matrix for one frequency and site, all impedances for one frequency and all stations form a contiguous block, the frequencies vary slowest.
     */
    void ReadImpedancesFromNetCDF(const std::string &filename, std::vector<
        double> &Frequencies, std::vector<double> &StatXCoord, std::vector<
        double> &StatYCoord, std::vector<double> &StatZCoord,
        gplib::rvec &Impedances)
    {
      NcFile DataFile(filename.c_str(), NcFile::ReadOnly);
      ReadVec(DataFile, MeasPosXName, StationNumberName, StatXCoord);
      ReadVec(DataFile, MeasPosYName, StationNumberName, StatYCoord);
      ReadVec(DataFile, MeasPosZName, StationNumberName, StatZCoord);
      ReadVec(DataFile, FreqDimName, FreqDimName, Frequencies);
      Impedances.resize(Frequencies.size() * StatXCoord.size() * 8);
      ReadImpedanceComp(DataFile, Impedances, "Zxx_re", 0);
      ReadImpedanceComp(DataFile, Impedances, "Zxx_im", 1);
      ReadImpedanceComp(DataFile, Impedances, "Zxy_re", 2);
      ReadImpedanceComp(DataFile, Impedances, "Zxy_im", 3);
      ReadImpedanceComp(DataFile, Impedances, "Zyx_re", 4);
      ReadImpedanceComp(DataFile, Impedances, "Zyx_im", 5);
      ReadImpedanceComp(DataFile, Impedances, "Zyy_re", 6);
      ReadImpedanceComp(DataFile, Impedances, "Zyy_im", 7);

    }
  /* @} */
  }

#endif /* READWRITEIMPEDANCES_H_ */
