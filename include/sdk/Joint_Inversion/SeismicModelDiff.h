#ifndef _SEISMICMODELDIFF_H_
#define _SEISMICMODELDIFF_H_
#include "GeneralObjective.h"
#include "ResPkModel.h"
#include "NumUtil.h"
#include <iostream>
#include <numeric>

namespace gplib
  {
    //! SeismicModelDiff calculates the roughness of a joint MT- receiver functions model compared to a seismic model
    class SeismicModelDiff: public GeneralObjective
      {
    private:
      ResPkModel Model;
    public:
      //! Clone the object
      virtual SeismicModelDiff *clone() const
        {
          return new SeismicModelDiff(*this);
        }
      virtual void SafeParallel(const ttranscribed &member)
      {
        const unsigned int length = member.size() / 3; //we have 3 parameters in the model, so size/3 layers
        double roughness = 0.0; // init returnvalue

        vector<double> memberdepth, refdepth;
        partial_sum(member.begin() + length, member.begin() + 2 * length,
            back_inserter(memberdepth));
        partial_sum(Model.GetThickness().begin(), Model.GetThickness().end(),
            back_inserter(refdepth));
        refdepth.back() += 1000.0; // the last layer is a halfspace
        vector<double> layerthick(memberdepth); //vector to contain the depths to interfaces in both models, contruct from inversion model
        copy(refdepth.begin(), refdepth.end(), back_inserter(layerthick)); // and insert reference model interfaces at back
        sort(layerthick.begin(), layerthick.end()); //then put them in right order
        adjacent_difference(layerthick.begin(), layerthick.end(),
            layerthick.begin());
        layerthick.erase(remove(layerthick.begin(), layerthick.end(), 0.0),
            layerthick.end()); //remove layers of 0 thickness
        unsigned int refindex = 0;
        unsigned int memberindex = 0;
        unsigned int thickindex = 0;
        double currthick = 0.0;
        while (refindex < Model.GetThickness().size() && memberindex < length)
          {
            int difference = fcmp(memberdepth.at(memberindex), refdepth.at(
                refindex), std::numeric_limits<double>::epsilon());
            currthick = layerthick.at(thickindex);
            roughness += pow2((member(memberindex + 2 * length)
                - Model.GetSVelocity().at(refindex)) / Model.GetSVelocity().at(
                refindex) * currthick);
            switch (difference)
              {
            case 1: // memberdepth bigger

              ++refindex;
              break;
            case -1:

              ++memberindex;
              break;
            case 0:

              ++refindex;
              ++memberindex;
              break;
              }
            thickindex++;
          }
        SetRMS(roughness);
      }
      virtual double PostParallel(const ttranscribed &member)
      {
        return GetRMS();
      }
      explicit SeismicModelDiff(const ResPkModel &Seis) :
          Model(Seis)
          {
          }
      SeismicModelDiff(const SeismicModelDiff &Old):
          GeneralObjective(Old), Model(Old.Model)
          {
          }

      SeismicModelDiff& operator=(const SeismicModelDiff& source)
      {
        if (this == &source)
          return *this;
        GeneralObjective::operator=(source);
        Model = source.Model;
        return *this;
      }

      virtual ~SeismicModelDiff();
      };
  }
#endif /*_SEISMICMODELDIFF_H_*/
