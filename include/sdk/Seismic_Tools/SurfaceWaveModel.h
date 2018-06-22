#ifndef SURFACEWAVEMODEL_H_
#define SURFACEWAVEMODEL_H_
#include "types.h"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <iostream>
using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    //! A class to store 1D model for calculation of synthetic surface wave data
    /*! This is the base class for general 1D surface wave models.
     *
     */
    class SurfaceWaveModel
      {
    private:
      trealdata pvvelocities;
      trealdata phvelocities;
      trealdata svvelocities;
      trealdata shvelocities;
      trealdata densities;
      trealdata thicknesses;
      trealdata eta;
      trealdata qmu;
      trealdata qkappa;
      double refperiod;
      int anisotropic;
      std::string name;
      int carddeckmodel;
      int ninnercore;
      int noutercore;
      void WriteLayer(std::ostream &stream, const unsigned int index,
          const trealdata &depth) const
      {
        stream << setw(10) << setprecision(6) << (6371 - depth.at(index))
            * 1000;
        stream << setw(10) << setprecision(6) << densities.at(index) * 1000
            << " " << pvvelocities.at(index) * 1000 << " ";
        stream << svvelocities.at(index) * 1000 << " " << qkappa.at(index)
            << " " << qmu.at(index) << " ";
        stream << phvelocities.at(index) * 1000 << " "
            << shvelocities.at(index) * 1000 << " " << eta.at(index) << " ";
        stream << depth.at(index); // have to write depth here
        stream << endl;
      }
    protected:
      void CheckConsistency() const
      {
        assert(pvvelocities.size() == phvelocities.size());
        assert(pvvelocities.size() == svvelocities.size());
        assert(pvvelocities.size() == shvelocities.size());
        assert(pvvelocities.size() == densities.size());
        assert(pvvelocities.size() == thicknesses.size());
        assert(pvvelocities.size() == eta.size());
        assert(pvvelocities.size() == qmu.size());
        assert(pvvelocities.size() == qkappa.size());
      }

    public:
      const trealdata &GetPvVelocities() const
        {
          return pvvelocities;
        }
      const trealdata &GetPhVelocities() const
        {
          return phvelocities;
        }
      const trealdata &GetSvVelocities() const
        {
          return svvelocities;
        }
      const trealdata &GetShVelocities() const
        {
          return shvelocities;
        }
      const trealdata &GetDensities() const
        {
          return densities;
        }
      const trealdata &GetThicknesses() const
        {
          return thicknesses;
        }
      const trealdata &GetEta() const
        {
          return eta;
        }
      const trealdata &GetQmu() const
        {
          return qmu;
        }
      const trealdata &GetQkappa() const
        {
          return qkappa;
        }
      std::string GetName() const
        {
          return name;
        }
      trealdata &SetPvVelocities()
        {
          return pvvelocities;
        }
      trealdata &SetPhVelocities()
        {
          return phvelocities;
        }
      trealdata &SetSvVelocities()
        {
          return svvelocities;
        }
      trealdata &SetShVelocities()
        {
          return shvelocities;
        }
      trealdata &SetDensities()
        {
          return densities;
        }
      trealdata &SetThicknesses()
        {
          return thicknesses;
        }
      trealdata &SetEta()
        {
          return eta;
        }
      trealdata &SetQmu()
        {
          return qmu;
        }
      trealdata &SetQkappa()
        {
          return qkappa;
        }
      double GetMaxDepth(const double depth)
      {
        assert(depth >= 0.0);
        if (depth < 10.0)
          return 1.0;
        if (depth < 20.0)
          return 2.0;
        if (depth < 100)
          return 5;
        if (depth < 400)
          return 10;
        return 100;
      }
      //! Splits a layer into several layers with a maximum thickness of maxthick, but otherwise identical properties
      int SplitLayer(const int index, const double maxthick)
      {
        assert(maxthick > 0.0);
        assert(index < thicknesses.size());
        double currthick = thicknesses.at(index);
        unsigned int ninsert = boost::numeric_cast<unsigned int>(floor(
            currthick / maxthick));
        if (ninsert > 0)
          {
            double diffthick = currthick - ninsert * maxthick;
            if (diffthick > 0.0) // we need diffthick extra layers and one with the difference

              {
                thicknesses.at(index) = diffthick;
              }
            else //they fit exactly

              {
                ninsert -= 1;
                thicknesses.at(index) = maxthick;
              }
            thicknesses.insert(thicknesses.begin() + index, ninsert, maxthick);
            pvvelocities.insert(pvvelocities.begin() + index, ninsert,
                pvvelocities.at(index));
            phvelocities.insert(phvelocities.begin() + index, ninsert,
                phvelocities.at(index));
            svvelocities.insert(svvelocities.begin() + index, ninsert,
                svvelocities.at(index));
            shvelocities.insert(shvelocities.begin() + index, ninsert,
                shvelocities.at(index));
            densities.insert(densities.begin() + index, ninsert, densities.at(
                index));
            eta.insert(eta.begin() + index, ninsert, eta.at(index));
            qmu.insert(qmu.begin() + index, ninsert, qmu.at(index));
            qkappa.insert(qkappa.begin() + index, ninsert, qkappa.at(index));

          }
        if (index + ninsert + 1 < thicknesses.size())
          {
            AddDiscontinuity(index + ninsert + 1);
            return index + ninsert + 1;
          }
        return index + ninsert;
      }
      //! Insert a layer with 0 thickness to create a discontinuity for the forward code
      void AddDiscontinuity(const int index)
      {
        const unsigned int ninsert = 1;
        assert(index-1 < thicknesses.size());
        assert(index > 0);

        thicknesses.insert(thicknesses.begin() + index, ninsert, 0.0);
        pvvelocities.insert(pvvelocities.begin() + index, ninsert,
            pvvelocities.at(index));
        phvelocities.insert(phvelocities.begin() + index, ninsert,
            phvelocities.at(index));
        svvelocities.insert(svvelocities.begin() + index, ninsert,
            svvelocities.at(index));
        shvelocities.insert(shvelocities.begin() + index, ninsert,
            shvelocities.at(index));
        densities.insert(densities.begin() + index, ninsert,
            densities.at(index));
        eta.insert(eta.begin() + index, ninsert, eta.at(index));
        qmu.insert(qmu.begin() + index, ninsert, qmu.at(index));
        qkappa.insert(qkappa.begin() + index, ninsert, qkappa.at(index));
      }

      //! Merge this model with another background model, the depth range below this model will be filled with the values from the background model
      void MergeModel(const SurfaceWaveModel &Background)
      {
        CheckConsistency();
        Background.CheckConsistency();
        trealdata thisdepth(thicknesses.size(), 0.0), backgrounddepth(
            Background.thicknesses.size());
        partial_sum(thicknesses.begin(), thicknesses.end(), thisdepth.begin());
        partial_sum(Background.thicknesses.begin(),
            Background.thicknesses.end(), backgrounddepth.begin());
        //find the index of the layer in the backgroundmodel that lies below the last layer of this model
        const unsigned int layerindex = distance(backgrounddepth.begin(),
            upper_bound(backgrounddepth.begin(), backgrounddepth.end(),
                thisdepth.back()));
        //cout << layerindex << " " << thisdepth.back() << " " << backgrounddepth.at(layerindex) << endl;
        assert(layerindex < Background.thicknesses.size());
        trealdata localthick(Background.thicknesses.begin() + layerindex,
            Background.thicknesses.end()); // we want to keep Background as it is
        localthick.front() = backgrounddepth.at(layerindex) - thisdepth.back(); //adjust thickness of bottom layer
        //copy(thicknesses.begin(),thicknesses.end(),ostream_iterator<double>(cout," "));
        //cout << endl;
        copy(localthick.begin(), localthick.end(), back_inserter(thicknesses));
        copy(Background.pvvelocities.begin() + layerindex,
            Background.pvvelocities.end(), back_inserter(pvvelocities));
        copy(Background.phvelocities.begin() + layerindex,
            Background.phvelocities.end(), back_inserter(phvelocities));
        copy(Background.svvelocities.begin() + layerindex,
            Background.svvelocities.end(), back_inserter(svvelocities));
        copy(Background.shvelocities.begin() + layerindex,
            Background.shvelocities.end(), back_inserter(shvelocities));
        copy(Background.densities.begin() + layerindex,
            Background.densities.end(), back_inserter(densities));
        copy(Background.eta.begin() + layerindex, Background.eta.end(),
            back_inserter(eta));
        copy(Background.qmu.begin() + layerindex, Background.qmu.end(),
            back_inserter(qmu));
        copy(Background.qkappa.begin() + layerindex, Background.qkappa.end(),
            back_inserter(qkappa));
        ninnercore = Background.ninnercore;
        noutercore = Background.noutercore;
      }
      //! Read a model from a file
      virtual void ReadModel(const std::string &filename) = 0;
      //! Write the model to a file
      virtual void WriteModel(const std::string &filename) const = 0;
      //! Write out a script that when executed performs a forward calculation for this model
      virtual void WriteRunFile(const std::string &filename, const std::vector<
          double> periods) const = 0;
      //! Write out an ascii file for plotting with xmgrace or similar programs
      void WritePlot(const std::string &filename) const
      {
        CheckConsistency();
        ofstream outfile(filename.c_str());
        double cumthick = 0;
        const unsigned int size = thicknesses.size();
        for (unsigned int i = 0; i < size; ++i)
          {
            outfile << cumthick << "  " << svvelocities.at(i) << endl;
            cumthick += thicknesses.at(i);
            outfile << cumthick << " " << svvelocities.at(i) << endl;
          }
        outfile << cumthick * 2.0 << " " << svvelocities.at(size - 1) << endl;
      }
      SurfaceWaveModel& operator=(const SurfaceWaveModel& source)
      {
        if (this == &source)
          return *this;
        source.CheckConsistency();
        pvvelocities.clear();
        phvelocities.clear();
        svvelocities.clear();
        shvelocities.clear();
        densities.clear();
        thicknesses.clear();
        eta.clear();
        qmu.clear();
        qkappa.clear();
        copy(source.pvvelocities.begin(), source.pvvelocities.end(),
            back_inserter(pvvelocities));
        copy(source.phvelocities.begin(), source.phvelocities.end(),
            back_inserter(phvelocities));
        copy(source.svvelocities.begin(), source.svvelocities.end(),
            back_inserter(svvelocities));
        copy(source.shvelocities.begin(), source.shvelocities.end(),
            back_inserter(shvelocities));
        copy(source.densities.begin(), source.densities.end(), back_inserter(
            densities));
        copy(source.thicknesses.begin(), source.thicknesses.end(),
            back_inserter(thicknesses));
        copy(source.eta.begin(), source.eta.end(), back_inserter(eta));
        copy(source.qmu.begin(), source.qmu.end(), back_inserter(qmu));
        copy(source.qkappa.begin(), source.qkappa.end(), back_inserter(qkappa));

        refperiod = source.refperiod;
        anisotropic = source.anisotropic;
        name = source.name;
        carddeckmodel = source.carddeckmodel;
        ninnercore = source.ninnercore;
        noutercore = source.noutercore;
        return *this;
      }

      SurfaceWaveModel(const SurfaceWaveModel &Old):
          pvvelocities(Old.pvvelocities), phvelocities(Old.phvelocities),
              svvelocities(Old.svvelocities), shvelocities(Old.shvelocities),
              densities(Old.densities), thicknesses(Old.thicknesses), eta(Old.eta),
              qmu(Old.qmu), qkappa(Old.qkappa), refperiod(Old.refperiod),
              anisotropic(Old.anisotropic), name(Old.name), carddeckmodel(
                  Old.carddeckmodel), ninnercore(Old.ninnercore), noutercore(
                  Old.noutercore)
          {

          }

      SurfaceWaveModel():
          refperiod(50), anisotropic(1), name("surf"), carddeckmodel(1),
              ninnercore(0), noutercore(0)
          {
          }
      virtual ~SurfaceWaveModel();
      };
  /* @} */
  }
#endif /*SURFACEWAVEMODEL_H_*/
