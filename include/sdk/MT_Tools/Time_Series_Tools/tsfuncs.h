#include <math.h>

namespace gplib
  {
    /** \addtogroup mttools MT data analysis, processing and inversion */
    /* @{ */

    inline bool IsSpikeAbsolute(const double prediff, const double postdiff,
        const double currvalue, const double Threshold)
      {
        if ((prediff * postdiff < 0) && (currvalue > Threshold))
          return (true);
        else
          return (false);
      }

    inline bool IsSpikePreRel(const double prediff, const double postdiff,
        const double currvalue, const double Threshold)
      {
        if ((prediff * postdiff < 0) && (std::abs(prediff) > Threshold))
          return (true);
        else
          return (false);
      }

    inline bool IsSpikePostRel(const double prediff, const double postdiff,
        const double currvalue, const double Threshold)
      {
        if ((prediff * postdiff < 0) && (std::abs(postdiff) > Threshold))
          return (true);
        else
          return (false);
      }

    inline bool IsSpikeAnyRel(const double prediff, const double postdiff,
        const double currvalue, const double Threshold)
      {
        if ((prediff * postdiff < 0) && ((std::abs(postdiff) > Threshold) || (fabs(
            prediff) > Threshold)))
          return (true);
        else
          return (false);
      }

    inline bool IsSpikeBothRel(const double prediff, const double postdiff,
        const double currvalue, const double Threshold)
      {
        if ((prediff * postdiff < 0) && ((std::abs(postdiff) > Threshold) && (fabs(
            prediff) > Threshold)))
          return (true);
        else
          return (false);

      }
  /* @} */
  }
