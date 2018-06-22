#ifndef CSTANDARDTRANSCRIBE_H
#define CSTANDARDTRANSCRIBE_H
#include "GeneralTranscribe.h"
#include <cmath>
#include "FatalException.h"
#include <boost/numeric/conversion/cast.hpp>

namespace gplib
  {
    /** \addtogroup gainv Genetic algorithm optimization */
    /* @{ */

    //! BinaryTranscibe implements transcription for standard binary populations
    /*! It works for simple binary string populations with the "canonic" decoding of the bit string
     * For each parameter a basevalue, stepsize and genesize has to be specified
     * upon construction. These three vectors have to have identical size.
     */
    class BinaryTranscribe: public GeneralTranscribe
      {
    protected:
      //! The minimum value for each parameter
      const ttranscribed basevalues;
      //! The stepsize associated to a bit change for each parameter
      const ttranscribed stepsizes;
      //! The number of bits for each parameter
      const tsizev genesizes;
    public:
      //! Implements the abstract function from GeneralTranscribe
      virtual ttranscribed GetValues(const tpopmember &member)
      {
        unsigned int currentindex = 0;
        double currentvalue;

        ttranscribed ReturnValues(genesizes.size());
        //for each model parameter
        for (unsigned int i = 0; i < genesizes.size(); ++i)
          {
            currentvalue = 0;
            //scan the corresponding section of the genetic string
            for (unsigned int j = currentindex; j < currentindex + genesizes(i); ++j)
              {
                //calculate the numeric value from the bits
                //some compilers have trouble using pow with some combinations of numeric types
                //so we explicitly use double and int which should work everywhere
                currentvalue += member(j) * std::pow(2.0, boost::numeric_cast<int>(j - currentindex));
              }
            //currentvalue now holds the raw integer value that is encoded in the bit string
            //so we multiply by the step size and add the basevalue to get the parameter value
            currentvalue *= stepsizes(i);
            currentvalue += basevalues(i);
            currentindex += genesizes(i);
            ReturnValues(i) = currentvalue; //store in the right component
          }
        return ReturnValues;
      }

      //! Without basevalues, stepsizes and genesizes BinaryTranscribe does not work, so we enforce their use by including them in the constructor
      BinaryTranscribe(const ttranscribed &base, const ttranscribed &step,
          const tsizev &gene) :
          basevalues(base), stepsizes(step), genesizes(gene)
          {
            //check that all three vectors have the same size
            if ((basevalues.size() != stepsizes.size()) || (basevalues.size()
                != genesizes.size()))
              throw FatalException(
                  "Basevalues, Stepsizes and Genesizes do not have equal length !");
            //they all have the same size, so we only check whether one is empty
            if (basevalues.empty())
              throw FatalException("Specified an empty base value vector for binary transcribe !");

          }
      //! Returns the number of parameters that are encoded in the binary string
      virtual int GetNparams()
        {
          return basevalues.size();
        }
      ;
      //! We declare a copy constructor that copies the private variables;
      BinaryTranscribe(const BinaryTranscribe &Old) :
          basevalues(Old.basevalues), stepsizes(Old.stepsizes), genesizes(
              Old.genesizes)
          {
            // The body is empty
          }
      BinaryTranscribe(const GeneralTranscribe &Old);
      virtual ~BinaryTranscribe();
      };
  /* @} */
  }
#endif // CSTANDARDTRANSCRIBE_H
