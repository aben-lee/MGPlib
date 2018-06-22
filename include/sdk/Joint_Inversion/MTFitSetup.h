#ifndef MTFITSETUP_H_
#define MTFITSETUP_H_
#include "C1DMTObjective.h"
#include "Adaptors.h"
namespace gplib
  {
    template<typename tConfObject>
    void SetupMTFitParameters(const tConfObject &Configuration,
        C1DMTObjective &Objective)
      {
        if (Configuration.mode == "xy")
          {
            if (Configuration.mtfit == "phase")
              Objective.AppendFitParameters(&MTTensor::GetPhixy,
                  &MTTensor::GetdPhixy, Configuration.phaseerror);
            if (Configuration.mtfit == "appres")
              Objective.AppendFitParameters(&MTTensor::GetRhoxy,
                  &MTTensor::GetdRhoxy, Configuration.reserror);
            if (Configuration.mtfit == "resphase")
              {
                Objective.AppendFitParameters(&MTTensor::GetRhoxy,
                    &MTTensor::GetdRhoxy, Configuration.reserror);
                Objective.AppendFitParameters(&MTTensor::GetPhixy,
                    &MTTensor::GetdPhixy, Configuration.phaseerror);
              }
          }
        else
          {
            if (Configuration.mtfit == "phase")
              Objective.AppendFitParameters(&MTTensor::GetPhiyx,
                  &MTTensor::GetdPhiyx, Configuration.phaseerror);
            if (Configuration.mtfit == "appres")
              Objective.AppendFitParameters(&MTTensor::GetRhoyx,
                  &MTTensor::GetdRhoyx, Configuration.reserror);
            if (Configuration.mtfit == "resphase")
              {
                Objective.AppendFitParameters(&MTTensor::GetRhoyx,
                    &MTTensor::GetdRhoyx, Configuration.reserror);
                Objective.AppendFitParameters(&MTTensor::GetPhiyx,
                    &MTTensor::GetdPhiyx, Configuration.phaseerror);
              }
          }
        if (Configuration.mtfit == "berd")
          {
            Objective.AppendFitParameters(boost::bind(gplib::real(),
                boost::bind(&MTTensor::GetBerd, _1)), &MTTensor::GetdBerd,
                Configuration.tensorerror);
            Objective.AppendFitParameters(boost::bind(gplib::imag(),
                boost::bind(&MTTensor::GetBerd, _1)), &MTTensor::GetdBerd,
                Configuration.tensorerror);
          }
        if (Configuration.mtfit == "det")
          {
            Objective.AppendFitParameters(boost::bind(gplib::real(),
                boost::bind(&MTTensor::GetDet, _1)), &MTTensor::GetdDet,
                Configuration.tensorerror);
            Objective.AppendFitParameters(boost::bind(gplib::imag(),
                boost::bind(&MTTensor::GetDet, _1)), &MTTensor::GetdDet,
                Configuration.tensorerror);
          }
        if (Configuration.mtfit == "all")
          {
            Objective.AppendFitParameters(&MTTensor::GetRhoxx,
                &MTTensor::GetdRhoxx, Configuration.reserror);
            Objective.AppendFitParameters(&MTTensor::GetPhixx,
                &MTTensor::GetdPhixx, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetRhoxy,
                &MTTensor::GetdRhoxy, Configuration.reserror);
            Objective.AppendFitParameters(&MTTensor::GetPhixy,
                &MTTensor::GetdPhixy, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetRhoyx,
                &MTTensor::GetdRhoyx, Configuration.reserror);
            Objective.AppendFitParameters(&MTTensor::GetPhiyx,
                &MTTensor::GetdPhiyx, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetRhoyy,
                &MTTensor::GetdRhoyy, Configuration.reserror);
            Objective.AppendFitParameters(&MTTensor::GetPhiyy,
                &MTTensor::GetdPhiyy, Configuration.phaseerror);
          }
        if (Configuration.mtfit == "allphase")
          {
            Objective.AppendFitParameters(&MTTensor::GetPhixx,
                &MTTensor::GetdPhixx, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhixy,
                &MTTensor::GetdPhixy, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhiyx,
                &MTTensor::GetdPhiyx, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhiyy,
                &MTTensor::GetdPhiyy, Configuration.phaseerror);
          }
        if (Configuration.mtfit == "offdphase")
          {
            Objective.AppendFitParameters(&MTTensor::GetPhixy,
                &MTTensor::GetdPhixy, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhiyx,
                &MTTensor::GetdPhiyx, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetAlpha,
                &MTTensor::GetdZero, Configuration.phaseerror);
          }
        if (Configuration.mtfit == "ptensor")
          {
            Objective.AppendFitParameters(&MTTensor::GetPhi11,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhi12,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhi21,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhi22,
                &MTTensor::GetdZero, Configuration.phaseerror);
          }
        if (Configuration.mtfit == "ptellip")
          {
            Objective.AppendFitParameters(&MTTensor::GetPhiMax,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetPhiMin,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetAlpha_phi,
                &MTTensor::GetdZero, Configuration.phaseerror);
            Objective.AppendFitParameters(&MTTensor::GetBeta_phi,
                &MTTensor::GetdZero, Configuration.phaseerror);
          }
      }
  }
#endif /*MTFITSETUP_H_*/
