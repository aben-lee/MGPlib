#ifndef MTRECOBJECTIVE_H_
#define MTRECOBJECTIVE_H_
#include "Iso1DMTObjective.h"
#include "C1DRecObjective.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <iostream>
#include "Adaptors.h"
namespace gplib
  {
    class MTRecObjective: public GeneralObjective
      {
    private:
      double recweight;
      C1DRecObjective RecObjective;
      Iso1DMTObjective MTObjective;
    public:
      void SetRecWeight(const double w)
        {
          recweight = w;
        }
      C1DRecObjective &GetRecObjective()
        {
          return RecObjective;
        }
      Iso1DMTObjective &GetMTObjective()
        {
          return MTObjective;
        }
      virtual MTRecObjective *clone() const
        {
          return new MTRecObjective(*this);
        }
      virtual double PostParallel(const ttranscribed &member)
      {
        const int nlayers = member.size() / 3;
        ttranscribed mtmember(nlayers * 2), recmember(nlayers * 2);
        mtmember = ublas::project(member, ublas::range(0, nlayers * 2));
        recmember = ublas::project(member, ublas::range(nlayers, nlayers * 3));
        double mtperf = MTObjective.CalcPerformance(mtmember);
        double recperf = RecObjective.CalcPerformance(recmember);
        const int ndata = MTObjective.GetSynthData().size()
            + RecObjective.GetSynthData().size();
        SetMisfit().resize(ndata); //make sure Misfit in base class can hold enough elements
        SetSynthData().resize(ndata); // and same for data
        project(SetSynthData(), ublas::range(0,
            MTObjective.GetSynthData().size())) = MTObjective.GetSynthData();
        project(SetSynthData(), ublas::range(MTObjective.GetSynthData().size(),
            MTObjective.GetSynthData().size()
                + RecObjective.GetSynthData().size()))
            = RecObjective.GetSynthData();
        project(SetMisfit(), ublas::range(0, MTObjective.GetMisfit().size()))
            = MTObjective.GetMisfit();
        project(SetMisfit(), ublas::range(MTObjective.GetMisfit().size(),
            MTObjective.GetMisfit().size() + RecObjective.GetMisfit().size()))
            = RecObjective.GetMisfit();
        SetRMS(mtperf + recweight * recperf);

        return mtperf + recweight * recperf;
      }
      MTRecObjective(const CMTStation &LocalMTData,
          SeismicDataComp &TheRecData, const int myshift, const double myomega,
          const double mysigma, const double myc, const double myslowness) :
          recweight(1), RecObjective(TheRecData, myshift, myomega, mysigma, myc,
              myslowness), MTObjective(LocalMTData)
          {

          }

      virtual ~MTRecObjective();
      };
  }
#endif /*MTRECOBJECTIVE_H_*/

