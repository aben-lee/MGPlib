#ifndef CTESTOBJECTIVE2_H
#define CTESTOBJECTIVE2_H

#include "GeneralObjective.h"
#include <cmath>
namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    class TestObjective2: public GeneralObjective
      {
    private:
      bool compatible;
    public:
      virtual TestObjective2 *clone() const
        {
          return new TestObjective2(*this);
        }
      virtual double PostParallel(const ttranscribed &member)
      {
        double returnvalue = 0.0;
        if (compat)
          {
            returnvalue = 10. * std::pow(member(1) - std::pow(member(0), 2), 2) + std::pow(1.
                - member(0), 2);
          }
        else
          {
            returnvalue = 10. * std::pow(member(0) + std::pow(member(1), 2), 2) + std::pow(1.
                + member(1), 2);
          }
        return returnvalue;
      }
      TestObjective2(bool compat = true) :
          compatible(compat)
          {
          }

      virtual ~TestObjective2();
      };
  /* @} */
  }
#endif // CTESTOBJECTIVE_H
