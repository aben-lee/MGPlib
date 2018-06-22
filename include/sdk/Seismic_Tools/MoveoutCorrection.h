#ifndef MOVEOUTCORRECTION_H_
#define MOVEOUTCORRECTION_H_
#include "SeismicDataComp.h"
#include "ResPkModel.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

using namespace std;

namespace gplib
  {
    /** \addtogroup seistools Seismic data analysis and modeling */
    /* @{ */

    class MoveoutCorrection
      {
    private:
      double refslowness;
      ResPkModel Model;
        //double CalcTraveltime(const double rayparameter, const double depth)
        //  {
        //    Model.SetSourceDepth(depth);
        //    double precdist = Model.MatchSlowness(rayparameter, SeismicModel::DirectP);
        //    Model.SetRecDist().push_back(precdist);
        //    double ptime = Model.CalcArrival(SeismicModel::DirectP, Model.GetRecDist().size()-1);
        //    double srecdist = Model.MatchSlowness(rayparameter, SeismicModel::DirectS);
        //    Model.SetRecDist().back() = srecdist;
        //    double stime = Model.CalcArrival(SeismicModel::DirectS, Model.GetRecDist().size()-1);
        //    double distdiff = precdist - srecdist;
        //    double angle = PI/2. - asin(rayparameter*Model.GetPVelocity().at(Model.FindLayer(Model.GetSourceDepth())));
        //    double extratotaldist = sin(angle) * distdiff;
        //    double extravdist = cos(PI/2.0 - angle) * extratotaldist;
        //    double extratime = Model.CalcTravelTime(SeismicModel::DirectP, extravdist
        //        +depth, depth, rayparameter);
        //    timesfile << depth << "  " << stime << " " << ptime << " "<< extratime
        //        << endl;
        //    return stime + extratime - ptime;
        //  }
      double CalcTraveltime(const double rayparameter, const double depth)
      {
        int sourceindex = Model.FindLayer(depth);
        double deltat = 0.0;
        double currdepth = 0.0;
        const double p2 = rayparameter * rayparameter;
        for (int i = 0; i < sourceindex; ++i)
          {
            currdepth += Model.GetThickness().at(i);
            double u = 1. / Model.GetPVelocity().at(i);
            deltat += Model.GetThickness().at(i) * (sqrt(pow(1.
                / Model.GetSVelocity().at(i), 2) - p2) - sqrt(pow(1.
                / Model.GetPVelocity().at(i), 2) - p2));
          }
        deltat += (depth - currdepth) * (sqrt(pow(1. / Model.GetSVelocity().at(
            sourceindex), 2) - p2) - sqrt(pow(1. / Model.GetPVelocity().at(
            sourceindex), 2) - p2));
        return deltat;
      }

      void InterpolateTo(trealdata &oldx, trealdata &y, trealdata &newx,
          trealdata &newy)
      {
        gsl_interp_accel *gslacc = gsl_interp_accel_alloc();
        gsl_spline *spline = gsl_spline_alloc(gsl_interp_linear, oldx.size());
        cout << "Oldx: " << oldx.size() << endl;
        cout << "Newx: " << newx.size() << endl;
        gsl_spline_init(spline, &oldx[0], &y[0], newx.size());
        newy.clear();
        for (int i = 0; i < newx.size(); ++i)
          {
            newy.push_back(gsl_spline_eval(spline, newx.at(i), gslacc));
          }

        gsl_spline_free(spline);
        gsl_interp_accel_free(gslacc);
      }

    public:
      void DoCorrection(SeismicDataComp &Rec, const double slowness)
      {
        const double maxdepth = 350;
        const int nelements = Rec.GetData().size();
        const double dt = Rec.GetDt();
        std::vector<double> refdeltat, deltat, depths, refdepths, actdepths,
            times, newtimes, amps, newamps;
        copy(Rec.GetData().begin(), Rec.GetData().end(), back_inserter(amps));
        cout << "Ref slow: " << refslowness << " Slow: " << slowness << endl;
        ofstream depthfile("depths");
        ofstream deltatfile("deltat");
        ofstream timesfile("times");
        for (double i = 1.0; i < maxdepth; i += 1.0)
          {
            depths.push_back(i);
            times.push_back(i * dt + Rec.GetB());
            refdeltat.push_back(CalcTraveltime(refslowness, i));
            deltat.push_back(CalcTraveltime(slowness, i));
            deltatfile << deltat.at(i) << " " << depths.at(i) << endl;
            cout << "Deltat: " << deltat.back() << " Ref Deltat: "
                << refdeltat.back() << endl;
          }
        InterpolateTo(deltat, depths, times, actdepths);
        InterpolateTo(depths, refdeltat, actdepths, newtimes);
        InterpolateTo(newtimes, amps, times, newamps);

        //    for (int i = 0; i < actdepths.size(); ++i)
        //      {
        //        depthfile << actdepths.at(i) << " " << amps.at(i) << endl;
        //
        //        timesfile << times.at(i) << " " << actdepths.at(i) << endl;
        //      }
        copy(newamps.begin(), newamps.end(), Rec.GetData().begin());
      }
      MoveoutCorrection(const double refslow, const ResPkModel &TheModel):
          refslowness(refslow), Model(TheModel)
          {
          }
      virtual ~MoveoutCorrection()
        {
        }
      };
  /* @} */
  }
#endif /*MOVEOUTCORRECTION_H_*/
