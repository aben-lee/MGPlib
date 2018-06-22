#ifndef GENTYPE_H
#define GENTYPE_H
#include <vector>
#include "VecMat.h"
#include <boost/function.hpp>
#include <map>

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    /*! /file Here we define some common types that are used throughout the genetic algorithm classes
     */
    namespace ublas = boost::numeric::ublas;

    typedef ublas::vector<double> tprobabilityv;
    typedef ublas::vector<double> tmisfit;
    typedef ublas::vector<double> tdata;
    typedef ublas::vector<double> tcrowddistv;
    typedef ublas::vector<double> ttranscribed;
    typedef ublas::vector<bool> tpopmember;
    typedef ublas::vector<double> tfitvec;
    typedef gplib::rmat tfitmat;
    typedef gplib::rmat tpopulation;
    typedef std::vector<int> tindexv;
    typedef ublas::vector<int> tsizev;
    typedef std::multimap<double, int> tIndexMap;
    typedef boost::function<const tprobabilityv &()> tProbabilityFunction;
    typedef boost::function<const tcrowddistv &()> tDistanceFunction;
  /* @} */
  }
#endif
