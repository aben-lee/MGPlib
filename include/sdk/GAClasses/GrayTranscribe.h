#ifndef GRAYTRANSCRIBE_H_
#define GRAYTRANSCRIBE_H_
#include "BinaryTranscribe.h"
#include <cmath>
#include <boost/numeric/conversion/cast.hpp>

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */
    //! This class implements the Gray code representation of a binary string and the corresponding transcription
    class GrayTranscribe: public BinaryTranscribe
      {
    public:
      virtual ttranscribed GetValues(const tpopmember &member)
        {
          unsigned int currentindex = 0;
          unsigned int currentmaxindex = 0;
          double currentvalue;
          double exponent;

          ttranscribed ReturnValues(genesizes.size());
          //for each model parameter
          for (unsigned int i = 0; i < genesizes.size(); ++i)
            {
              currentvalue = 0;
              //scan the corresponding section of the genetic string
              currentmaxindex = currentindex + genesizes(i);
              for (unsigned int j = currentindex; j < currentmaxindex; ++j)
                {
                  exponent = 0.0;
                  for (unsigned int k = j; k < currentmaxindex; ++k)
                    {
                      exponent += member(k);
                    }
                  currentvalue += -1.0 * member(j) * std::pow(-1.0, exponent) * (std::pow(
                      2.0, boost::numeric_cast<int>(j - currentindex + 1)) - 1.0); //calculate the numeric value from the bits
                }
              currentvalue *= stepsizes(i);
              currentvalue += basevalues(i);
              currentindex += genesizes(i);
              ReturnValues(i) = currentvalue; //store in the right component
            }
          return (ReturnValues);
        }//!< Re-Implements the  function from BinaryTranscribe
      GrayTranscribe(const ttranscribed &base, const ttranscribed &step,
          const tsizev &gene):
          BinaryTranscribe(base, step, gene)
          {
          }

      virtual ~GrayTranscribe();
      };
  /* @} */
  }
#endif /*GRAYTRANSCRIBE_H_*/
