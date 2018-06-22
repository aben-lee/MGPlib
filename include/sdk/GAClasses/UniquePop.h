#ifndef CUNIQUEPOP_H
#define CUNIQUEPOP_H
#include <boost/unordered_map.hpp>
#include <fstream>
#include "gentypes.h"
#include <iomanip>

using namespace std;

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! This class stores a single unique copy of each population member that is added to it
    /*! In order to avoid duplicate output of inversion results at the end of the genetic algorithm
     * run and have a compact history of all models evaluated during the GA run, we have this class
     * that makes sure that we only have a single copy of each population member. This class also
     * stores the associated fitness values, so we can use it to look up the fitness of a member
     * instead of calculating it if the member has already been evaluated before.
     */
    class UniquePop
      {
    private:
      struct memb_equal
        {
        bool operator()(ttranscribed const& p1, ttranscribed const& p2) const
          {
            return std::equal(p1.begin(), p1.end(), p2.begin());
          }
        };

      struct memb_hash: std::unary_function<ttranscribed, std::size_t>
        {
        std::size_t operator()(ttranscribed const& p) const
          {
            std::size_t seed = 0;
            const size_t length = p.size();
            for (size_t i = 0; i < length; ++i)
              {
                boost::hash_combine(seed, p(i));
              }
            return seed;
          }
        };

      typedef boost::unordered_map<ttranscribed, tfitvec,memb_hash,memb_equal> tmembermap;
      tmembermap MemberHashMap;
    public:
      bool Find(const ttranscribed &popmember, tfitvec &fitness)
      {
        tmembermap::iterator FindPos = MemberHashMap.find(popmember);
        if (FindPos == MemberHashMap.end())
          return false;

        fitness = FindPos->second;
        return true;

      }
      bool Insert(const tfitvec &fitness, const ttranscribed &popmember)
      {
        pair<tmembermap::iterator, bool> insertresult = MemberHashMap.insert(
            std::make_pair(popmember,fitness));
        return insertresult.second;
      }
      void PrintAll(std::ostream &output)
      {
        tmembermap::iterator outit;

        for (outit = MemberHashMap.begin(); outit != MemberHashMap.end(); ++outit)
          {
            output << setprecision(10);
            copy(outit->first.begin(), outit->first.end(), ostream_iterator<
                double> (output, " "));
            output << "    ";
            copy(outit->second.begin(), outit->second.end(),
                ostream_iterator<double> (output, " "));
            output << endl;
          }
      }
      UniquePop();
      virtual ~UniquePop();
      };
  /* @} */
  }
#endif // CUNIQUEPOP_H
