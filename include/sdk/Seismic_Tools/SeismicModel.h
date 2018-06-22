#ifndef CSEISMICMODEL_H
#define CSEISMICMODEL_H

#include "types.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <cassert>

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! The class SeismicModel is the base class for some of the model format for seismic codes
    /*!
     * We store the basic seismic parameters here and implement some of the common functionailty.
     *
     */
    class SeismicModel
      {
    public:
      //! Do we want to calculate the arrival of a direct S-Wave or a P-wave
      enum tArrivalType
        {
        DirectS, DirectP
        };
    private:
      trealdata SVelErrors;
      trealdata ThickErrors;
      bool
      FuzzComp(const double elem1, const double elem2, const double tolerance)
      {
        return (std::abs(elem1 - elem2) < tolerance);
      }
      trealdata PVelocity;
      trealdata SVelocity;
      trealdata Density;
      trealdata Thickness;
      trealdata Qp;
      trealdata Qs;
      double SourceDepth;
      double dt;
      unsigned int npts;
    public:
      //! Get the number of points for synthetic seismogram calculation
      unsigned int GetNpts() const
        {
          return npts;
        }
      //! Set the number of points for synthetic seismogram calculation
      void SetNpts(const unsigned int s)
        {
          npts = s;
        }
      //! Get the depth to the seismic source that generates the wavefield
      double GetSourceDepth() const
        {
          return SourceDepth;
        }
      //! Set the depth to the seismic source
      void SetSourceDepth(const double s)
        {
          SourceDepth = s;
        }
      //! Get the time between two samples in s, this is for synthetic forward calculations
      double GetDt() const
        {
          return dt;
        }
      //! Set the time between two samples in s, this is for synthetic forward calculations
      void SetDt(const double s)
        {
          dt = s;
        }
      //! Read-only access to the vector of P-velocities in km/s in each layer
      const trealdata &GetPVelocity() const
        {
          return PVelocity;
        }
      //! Read-write access to the vector of P-velocities in km/s in each layer
      trealdata &SetPVelocity()
        {
          return PVelocity;
        }
      //! Read-only access to the vector of S-velocities in km/s in each layer
      const trealdata &GetSVelocity() const
        {
          return SVelocity;
        }
      //! Read-write access to the vector of S-velocities in km/s in each layer
      trealdata &SetSVelocity()
        {
          return SVelocity;
        }
      //! Read-only access to the vector of densities in g/cm^3 in each layer
      const trealdata &GetDensity() const
        {
          return Density;
        }
      //! Read-write access to the vector of densities in g/cm^3 in each layer
      trealdata &SetDensity()
        {
          return Density;
        }
      //! Read-only access to the vector of thicknesses in km in each layer
      const trealdata &GetThickness() const
        {
          return Thickness;
        }
      //! Read-write access to the vector of thicknesses in km in each layer
      trealdata &SetThickness()
        {
          return Thickness;
        }
      //! Read-only access to the vector of P quality factors for each layer
      const trealdata &GetQp() const
        {
          return Qp;
        }
      //! Read-write access to the vector of P quality factors for each layer
      trealdata &SetQp()
        {
          return Qp;
        }
      //! Read-only access to the vector of S quality factors for each layer
      const trealdata &GetQs() const
        {
          return Qs;
        }
      //! Read-write access to the vector of S quality factors for each layer
      trealdata &SetQs()
        {
          return Qs;
        }
      //! Set error bars on S-velocities for plotting
      void SetSVelErrors(const trealdata &sve)
        {
          SVelErrors = sve;
        }
      //! Set error bars on Thicknesses for plotting
      void SetThickErrors(const trealdata &te)
        {
          ThickErrors = te;
        }
      //! Returns the index of the layer that correponds to depth in km
      int FindLayer(const double depth)
      {
        //make sure the depth is positive
        assert(depth > 0.0);
        double currentbottom = 0;
        size_t i = 0;
        //we have to check that the bottom of the current layer
        //is deeper then what we are looking for
        //and that we don't look past the last index
        while (depth > currentbottom && i < Thickness.size())
          {
            currentbottom += Thickness.at(i);
            ++i;
          }
        //if we reach the end it means we are in the lower most
        //halfspace and return the index of the last layer
        return min(i, Thickness.size() - 1);
      }

      //! Given a slowness in s/km and a wave type calculate the distance that matches this slowness
      double MatchSlowness(const double slowness, const tArrivalType mode)
      {
        double x = 0;
        double currdepth = 0;
        trealdata *velocity;
        const int sourcelayer = FindLayer(SourceDepth) - 1;

        if (mode == DirectS)
          velocity = &SVelocity;
        else
          velocity = &PVelocity;
        for (int i = 0; i < sourcelayer; ++i)
          {
            x += Thickness.at(i) * tan(asin(slowness * velocity->at(i)));
            currdepth += Thickness.at(i);
          }
        x += (SourceDepth - currdepth) * tan(asin(slowness * velocity->at(
            sourcelayer)));
        return x;
      }
      double CalcArrival(const tArrivalType mode, const double recdist)
      {
        const double tolerance = 0.001;
        double angle = PI / 4.;
        double distance = 0;
        trealdata *velocity;
        double p = 0;
        double currdepth = 0;
        int preclevel = 3;

        if (mode == DirectS)
          velocity = &SVelocity;
        else
          velocity = &PVelocity;
        while (!FuzzComp(recdist, distance, tolerance))
          {
            currdepth = 0;
            p = sin(angle) / velocity->at(0);
            distance = MatchSlowness(p, mode);
            if (distance > recdist)
              angle -= PI * pow(0.5, preclevel);
            else
              angle += PI * pow(0.5, preclevel);
            preclevel++;
          }
        return CalcTravelTime(mode, SourceDepth, 0.0, p);
      }
      double CalcTravelTime(const tArrivalType mode, const double sdepth,
          const double rdepth, const double p)
      {
        int sourceindex = FindLayer(sdepth);
        int recindex = FindLayer(rdepth);
        const double hdistance = MatchSlowness(p, mode);
        double currdepth = accumulate(Thickness.begin(), Thickness.begin()
            + recindex, 0.0);
        trealdata *velocity;
        if (mode == DirectS)
          velocity = &SVelocity;
        else
          velocity = &PVelocity;
        double t = p * hdistance;
        double eta = sqrt(1 / pow(velocity->at(recindex), 2) - p * p);
        t += (currdepth - rdepth) * eta;
        for (int i = recindex; i < sourceindex; ++i)
          {
            currdepth += Thickness.at(i);
            eta = sqrt(1 / pow(velocity->at(i), 2) - p * p);
            t += eta * Thickness.at(i);
          }
        eta = sqrt(1 / pow(velocity->at(sourceindex), 2) - p * p);
        t += (sdepth - currdepth) * eta;
        return t;
      }
      //! Read the model in its native format from a file
      virtual void ReadModel(const std::string filename)=0;
      //! Write the model in its native format to a file
      virtual void WriteModel(const std::string filename)=0;
      //! Write out a script that performs a forward calculation for the current model
      virtual void WriteRunFile(const std::string &filename)=0;
      //! Write out an ascii file for plotting with xmgrace etc.
      void WritePlot(const std::string &filename)
      {
        ofstream outfile((filename + ".plot").c_str());
        double cumthick = 0;
        const unsigned int size = Thickness.size();
        for (unsigned int i = 0; i < size; ++i)
          {
            outfile << cumthick << "  " << SVelocity.at(i) << "  "
                << PVelocity.at(i) << "  " << Density.at(i) << endl;
            cumthick += Thickness.at(i);
            outfile << cumthick << " " << SVelocity.at(i) << "  "
                << PVelocity.at(i) << "  " << Density.at(i) << endl;
          }
        outfile << cumthick * 2.0 << " " << SVelocity.at(size - 1) << "  "
            << PVelocity.at(size - 1) << "  " << Density.at(size - 1) << endl;
      }
      //! Write out an ascii file with error bars for plotting with xmgrace etc.
      void PlotVelWithErrors(const std::string &filename)
      {
        bool haveErrors = false;
        if (!SVelErrors.empty() && !ThickErrors.empty())
          haveErrors = true;
        ofstream outfile(filename.c_str());
        double cumthick = 0;
        const unsigned int size = Thickness.size();
        for (unsigned int i = 0; i < size; ++i)
          {
            outfile << cumthick << "  " << SVelocity.at(i);
            if (haveErrors)
              outfile << " " << ThickErrors.at(i) << " " << SVelErrors.at(i);
            outfile << endl;
            cumthick += Thickness.at(i);
            outfile << cumthick << " " << SVelocity.at(i);
            if (haveErrors)
              outfile << " " << ThickErrors.at(i) << " " << SVelErrors.at(i);
            outfile << endl;
          }
      }
      //! Init provides a convenient way to allocate memory in all structures for a given number of layers
      void Init(const int nlayers)
      {
        //with this function we can easily allocate
        //elements for the different vectors
        PVelocity.assign(nlayers, 0);
        SVelocity.assign(nlayers, 0);
        Density.assign(nlayers, 0);
        Thickness.assign(nlayers, 0);
        Qp.assign(nlayers, 0);
        Qs.assign(nlayers, 0);
      }
      SeismicModel(const int nlayers = 0):
          SourceDepth(0.0), dt(0.0), npts(0)
          {
            Init(nlayers);
          }

      SeismicModel(const SeismicModel& source)
      {
        //when we use the copy constructor the vectors
        //of the new object are empty so we can use a back_inserter
        copy(source.PVelocity.begin(), source.PVelocity.end(), back_inserter(
            this->PVelocity));
        copy(source.SVelocity.begin(), source.SVelocity.end(), back_inserter(
            this->SVelocity));
        copy(source.Density.begin(), source.Density.end(), back_inserter(
            this->Density));
        copy(source.Thickness.begin(), source.Thickness.end(), back_inserter(
            this->Thickness));
        copy(source.Qp.begin(), source.Qp.end(), back_inserter(this->Qp));
        copy(source.Qs.begin(), source.Qs.end(), back_inserter(this->Qs));
        SourceDepth = source.SourceDepth;
        dt = source.dt;
        npts = source.npts;
      }
      SeismicModel& operator=(const SeismicModel& source)
      {
        if (this == &source)
          return *this;
        const int nelements = source.PVelocity.size();
        //for the regular copy operator we have to delete old data
        //so we allocate new space and copy the elements
        PVelocity.assign(nelements, 0);
        SVelocity.assign(nelements, 0);
        Density.assign(nelements, 0);
        Thickness.assign(nelements, 0);
        Qp.assign(nelements, 0);
        Qs.assign(nelements, 0);

        copy(source.PVelocity.begin(), source.PVelocity.end(),
            PVelocity.begin());
        copy(source.SVelocity.begin(), source.SVelocity.end(),
            SVelocity.begin());
        copy(source.Density.begin(), source.Density.end(), Density.begin());
        copy(source.Thickness.begin(), source.Thickness.end(),
            Thickness.begin());
        copy(source.Qp.begin(), source.Qp.end(), Qp.begin());
        copy(source.Qs.begin(), source.Qs.end(), Qs.begin());
        SourceDepth = source.SourceDepth;
        dt = source.dt;
        npts = source.npts;
        return *this;
      }
      virtual ~SeismicModel();
      };
  /* @} */
  }
#endif // CSEISMICMODEL_H
