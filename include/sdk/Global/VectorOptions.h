//============================================================================
// Name        : VectorOptions.h
// Author      : Apr 1, 2011
// Version     : 
// Copyright   : 2011, mmoorkamp
//============================================================================


#ifndef VECTOROPTIONS_H_
#define VECTOROPTIONS_H_

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include "convert.h"


namespace boost
  {

    namespace program_options
      {

        template<class NumType>
        struct DummyVec
          {
          std::vector<NumType> VecVal;
          };

        /*! We define a custom validate function for boost::program_options
         * so that we can read vector valued quantities from configuration
         * file in a way that is compatible with our previous routines, i.e.
         *
         * option = value1 value2 .... valueN
         *
         */
        template<class NumType>
        void validate(boost::any& v, const std::vector<std::string>& values,
            DummyVec<NumType>* target_type, int)
          {
            // Make sure no previous assignment to 'a' was made.
            validators::check_first_occurrence(v);
            const std::string& s = validators::get_single_string(values);

            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> sep(" ");
            tokenizer tok(s, sep);
            NumType CurrVal;
            DummyVec<NumType> TempVec;
            for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
              {
                gplib::convert(*it, CurrVal);
                TempVec.VecVal.push_back(CurrVal);
              }

            v = boost::any(TempVec);

          }
      }
  }


#endif /* VECTOROPTIONS_H_ */
