#ifndef ARRAYSAMPLEGENERATOR_H_
#define ARRAYSAMPLEGENERATOR_H_
#include "VecMat.h"

namespace gplib
  {

    /** \addtogroup statistics Statistical methods */
    /* @{ */
    //! Sequentially returns the elements of an array
    class ArraySampleGenerator
      {
    private:
      int index;
      gplib::rvec samples;
    public:
      double operator()()
        {
          index = (index + 1) % samples.size();
          return samples(index);
        }
      ArraySampleGenerator(const gplib::rvec &s) :
        index(-1), samples(s)
        {
        }
      ;
      virtual ~ArraySampleGenerator()
        {
        }
      ;
      };
  /* @} */
  }
#endif /*ARRAYSAMPLEGENERATOR_H_*/
