#ifndef COLLAPSEMODEL_H_
#define COLLAPSEMODEL_H_
#include "gentypes.h"
#include "FatalException.h"
#include "NumUtil.h"

namespace gplib
  {
    //! Remove layers with identical parameters from the model and collapse them into a single layer each
    void CollapseModel(ttranscribed &Thickness, ttranscribed &ParmValue)
    {
      std::vector<double> CollThick, CollValue;
      const unsigned int size = Thickness.size();
      if (size != ParmValue.size())
        throw FatalException(
            "Cannot collapse model with differing number of depths and parameter values !");
      unsigned int index = 0; //we need the loop index afterwards
      for (/* index initialized above*/; index < size - 1; ++index)
        {
          //if layer parameters are identical and combined layer thickness is less than 100km
          //the seismic code seems to have problems when the thickness of a single layer exceeds
          //this value
          if ((fcmp(ParmValue(index), ParmValue(index + 1),
              std::numeric_limits<double>::epsilon()) == 0) && ((Thickness(index) + Thickness(index
              + 1)) < 100.0))
            {
              CollValue.push_back(ParmValue(index));
              CollThick.push_back(Thickness(index) + Thickness(index + 1));
              ++index; //skip the next layer
            }
          else //if layers are different
            {
              CollThick.push_back(Thickness(index));
              CollValue.push_back(ParmValue(index));
            }
        }
      if (index == size - 1) // if we didn't collapse the last layer
        {
          CollThick.push_back(Thickness(index));
          CollValue.push_back(ParmValue(index));
        }
      Thickness.resize(CollThick.size());
      ParmValue.resize(CollValue.size());
      copy(CollThick.begin(), CollThick.end(), Thickness.begin());
      copy(CollValue.begin(), CollValue.end(), ParmValue.begin());
    }
  }
#endif /*COLLAPSEMODEL_H_*/
