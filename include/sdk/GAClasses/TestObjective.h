#ifndef CTESTOBJECTIVE_H
#define CTESTOBJECTIVE_H

#include "GeneralObjective.h"
#include <cmath>

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    class TestObjective: public GeneralObjective
      {
    public:
      virtual TestObjective *clone() const
        {
          return new TestObjective(*this);
        }
      virtual double PostParallel(const ttranscribed &member)
        {
          double returnvalue = 10. * std::pow(member(0) - std::pow(member(1), 2), 2) + std::pow(
              1. - member(1), 2);
          return (returnvalue);
        }
      TestObjective();

      virtual ~TestObjective();
      };
  /* @} */
  }
#endif // CTESTOBJECTIVE_H
