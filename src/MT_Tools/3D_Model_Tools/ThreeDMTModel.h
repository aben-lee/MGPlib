#ifndef _C3DMODEL_H_
#define _C3DMODEL_H_

#include <boost/multi_array.hpp>
#include <string>

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    //! The class 3DMTModel manages 3D models for magnetotelluric model calculations, at this point this is only for file management and plotting purposes
    /*! This class provides basic storage, read/write and plotting capabilities for
     * three dimensional MT models in Mackie's native or WinGLink format. There
     * is no corresponding forward code in this library at this point.
     */
    class ThreeDMTModel
      {
    public:
      typedef boost::multi_array<int, 3> t3DModelData;
      typedef std::vector<double> t3DModelDim;
      typedef std::vector<double> t3DModelRes;
    private:
      int LookupIndex(const double resistivity);
      double LookupResistivity(const int index);
    protected:
      t3DModelData Model;
      t3DModelRes Resistivities;
      t3DModelDim xsize;
      t3DModelDim ysize;
      t3DModelDim zsize;
      int airlayers;
    public:
      //! Get the cell sizes in x-direction (North) in m
      const t3DModelDim &GetXSizes()
        {
          return xsize;
        }
      //! Get the cell sizes in y-direction (East) in m
      const t3DModelDim &GetYSizes()
        {
          return ysize;
        }
      //! Get the cell sizes in z-direction (down) in m
      const t3DModelDim &GetZSizes()
        {
          return zsize;
        }
      //! Return the table of resistivity values that correspond to the index values in GetModel
      const t3DModelRes &GetResistivities()
        {
          return Resistivities;
        }
      //! Return a three dimensional multi-array with the indices of the resistivity values in each model cell, z varies fastest, then y then x
      const t3DModelData &GetModel()
        {
          return Model;
        }
      //! Return the number of air layers in the model
      int GetAirlayers()
        {
          return airlayers;
        }
      //! Set the number of air layers in the model
      void SetAirlayers(const int n)
        {
          airlayers = n;
        }
      //! Read an ascii file in the format written by WinGLink
      void ReadWinGLink(std::string filename);
      //! Read an ascii file in the format use by Mackie's old code
      void ReadMackie(std::string filename);
      //! Write an ascii file in the format written by WinGLink
      void WriteWinGLink(std::string filename);
      //! Write an ascii file in the format use by Mackie's old code
      void WriteMackie(std::string filename);
      //! Write an ascii file in .vtk format for plotting
      void WriteVTK(std::string filename);
      //! Write the model in netcdf format
      void WriteNetCDF(std::string filename);
      ThreeDMTModel();
      virtual ~ThreeDMTModel();
      };
  /* @} */
  }
#endif //_C3DMODEL_H_
