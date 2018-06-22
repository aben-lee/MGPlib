#ifndef FILEABORT_H_
#define FILEABORT_H_
#include "boost/filesystem/convenience.hpp"

namespace gplib
  {
    /** \addtogroup genfunc General functions from various areas */
    /* @{ */

    //! Checks whether the file abort exists in the current directory to signal the program that we want to stop
    inline bool WantAbort()
      {
        return boost::filesystem::exists("abort");
      }

    //! Remove the abort file in the current directory
    inline void RemoveAbort()
      {
        boost::filesystem::remove("abort");
      }
  /* @} */
  }
#endif /*FILEABORT_H_*/
