#ifndef MULTIANISOSURFACEWAVEOBJECTIVE_H_
#define MULTIANISOSURFACEWAVEOBJECTIVE_H_

#include "GeneralObjective.h"
#include "AnisoSurfaceWaveObjective.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "convert.h"
#include <boost/bind.hpp>
#include <numeric>
namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */
    //! Minimize the misfit for several surface wave dispersion curves simultaneously
    class MultiAnisoSurfaceWaveObjective: public GeneralObjective
      {
    private:
      std::vector<boost::shared_ptr<AnisoSurfaceWaveObjective> >
          IndividualObjectives;
      std::vector<double> backazimuths;
    public:
      virtual MultiAnisoSurfaceWaveObjective *clone() const
        {
          return new MultiAnisoSurfaceWaveObjective(*this);
        }
      void AddMeasurement(const ParkSurfaceWaveData &Measured,
          const double back, const double avel)
      {
        boost::shared_ptr<AnisoSurfaceWaveObjective> CurrObj(
            new AnisoSurfaceWaveObjective(Measured, back, avel));
        IndividualObjectives.push_back(CurrObj);
        backazimuths.push_back(back);
      }

      //! Some operations cannot be done in parallel, these are done before
      virtual void PreParallel(const ttranscribed &member)
      {
        if (IndividualObjectives.empty())
          throw FatalException(
              "In Multi1DRecObjective: No Objective functions set !");
        const size_t nobjs = IndividualObjectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            IndividualObjectives.at(i)->SetParallelID(GetParallelID()
                + stringify(i));
            IndividualObjectives.at(i)->PreParallel(member);
          }
      }
      //! Some operations cannot be done in parallel, these are done after, returns the misfit value
      virtual double PostParallel(const ttranscribed &member)
      {
        std::vector<double> values;
        transform(IndividualObjectives.begin(), IndividualObjectives.end(),
            back_inserter(values), boost::bind(
                &AnisoSurfaceWaveObjective::PostParallel, _1, member));
        double sumsquares = inner_product(values.begin(), values.end(),
            values.begin(), 0.0);
        return sqrt(sumsquares / values.size());
      }

      //! The core performance calculation, has to be safe to be done in parallel
      virtual void SafeParallel(const ttranscribed &member)
      {
        for_each(IndividualObjectives.begin(), IndividualObjectives.end(),
            boost::bind(&AnisoSurfaceWaveObjective::SafeParallel, _1, member));
      }

      void WriteData(const std::string &filename)
      {
        const size_t nobjs = IndividualObjectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            IndividualObjectives.at(i)->WriteData(filename + stringify(i)); // write one output file for each BAZ
          }
      }

      void WriteModel(const std::string &filename)
      {
        const size_t nobjs = IndividualObjectives.size();
        for (size_t i = 0; i < nobjs; ++i)
          {
            IndividualObjectives.at(i)->WriteModel(filename + stringify(i)); // write one model file for each BAZ
          }
      }
      void WritePlot(const std::string &filename)
      {
        IndividualObjectives.front()->WritePlot(filename); //all models are the same, so we only write the first
      }
      MultiAnisoSurfaceWaveObjective(const MultiAnisoSurfaceWaveObjective &Old)
      {
        const size_t nobjs = Old.IndividualObjectives.size();
        IndividualObjectives.clear();
        backazimuths.clear();
        copy(Old.backazimuths.begin(), Old.backazimuths.end(), back_inserter(
            backazimuths));
        for (size_t i = 0; i < nobjs; ++i)
          {
            boost::shared_ptr<AnisoSurfaceWaveObjective> Obj(
                Old.IndividualObjectives.at(i)->clone());
            IndividualObjectives.push_back(Obj);
          }
      }
      MultiAnisoSurfaceWaveObjective& operator=(
          const MultiAnisoSurfaceWaveObjective& source)
      {
        if (this == &source)
          return *this;
        const size_t nobjs = source.IndividualObjectives.size();
        IndividualObjectives.clear();
        backazimuths.clear();
        copy(source.backazimuths.begin(), source.backazimuths.end(),
            back_inserter(backazimuths));
        for (size_t i = 0; i < nobjs; ++i)
          {
            boost::shared_ptr<AnisoSurfaceWaveObjective> Obj(
                source.IndividualObjectives.at(i)->clone());
            IndividualObjectives.push_back(Obj);
          }
        return *this;
      }
      MultiAnisoSurfaceWaveObjective();
      virtual ~MultiAnisoSurfaceWaveObjective();
      };
  /* @} */
  }
#endif /*MULTIANISOSURFACEWAVEOBJECTIVE_H_*/
