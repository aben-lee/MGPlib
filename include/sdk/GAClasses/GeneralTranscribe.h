
#ifndef CGENERALTRANSCRIBE_H
#define CGENERALTRANSCRIBE_H
#include "gentypes.h"

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! General Transcribe base class for genetic algorithm parameter transcription
    /*! General Transcribe: Base class for transcribing a gene string to numbers that can be handled by the Objective functions.
     * Does not care about which parameter used by which function, but only returns a vector of doubles.
     * This base class only defines the interface, but has no own functionality
     * This version: $Id: GeneralTranscribe.h 1816 2009-09-07 11:28:35Z mmoorkamp $
     */
    class GeneralTranscribe
      {
    public:
      /*! The abstract function GetValues takes a population member as input and returns a
       * vector of doubles, that are used as parameters for the objective functions*/
      virtual ttranscribed GetValues(const tpopmember &member)=0;
      virtual int GetNparams() = 0;
      GeneralTranscribe();
      /*! The copy constructor is empty and will be removed in the future*/
      GeneralTranscribe(const GeneralTranscribe &Old);
      virtual ~GeneralTranscribe();
      };
  /* @} */
  }
#endif // CGENERALTRANSCRIBE_H
