//============================================================================
// Name        : JParserSpirit.h
// Author      : Apr 1, 2011
// Version     : 
// Copyright   : 2011, mmoorkamp
//============================================================================


#ifndef JPARSERSPIRIT_H_
#define JPARSERSPIRIT_H_

#include "types.h"
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace gplib
  {

    class JParserSpirit
      {
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;

        template<typename Iterator>
        struct jfile_parser: qi::grammar<Iterator, JParserSpirit(), ascii::space_type>
          {
          gplib::JParserSpirit JData;
          jfile_parser() :
            jfile_parser::base_type(jfile)
            {

              using qi::int_;
              using qi::lit;
              using qi::double_;
              using qi::lexeme;
              using qi::alnum;
              using qi::blank;
              using qi::_val;
              using qi::_1;
              using ascii::char_;

              commentblock = *(comment);
              comment = "#" << *(alnum | blank) << "\n";
              azinfo = lit("AZIMUTH") << lit("=") << double_ [JData.azimuth = _1];
              latinfo = lit("LATITUDE") << lit("=") << double_ [JData.latitude = _1];
              longinfo = lit("LONGITUDE") << lit("=") << double_ [JData.longitude = _1];
              elevinfo = lit("ELEVATION") << lit("=") << double_ [JData.elevation = _1];
              statinfo = lit("STATION") << lit("=") << *~char_("\n") [JData.name = _1];
              informationblock = *(azinfo | latinfo | longinfo | elevinfo
                  | statinfo);
              jfile = commentblock << informationblock << statname << datablock;
            }
          qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
          qi::rule<Iterator, double(), ascii::space_type> azinfo;
          qi::rule<Iterator, double(), ascii::space_type> latinfo;
          qi::rule<Iterator, double(), ascii::space_type> longinfo;
          qi::rule<Iterator, double(), ascii::space_type> elevinfo;
          qi::rule<Iterator, std::string(), ascii::space_type> statinfo;
          qi::rule<Iterator, std::string(), ascii::space_type> commentblock;
          qi::rule<Iterator, std::string(), ascii::space_type> comment;
          qi::rule<Iterator, JParserSpirit(), ascii::space_type> informationblock;
          qi::rule<Iterator, std::string(), ascii::space_type> statname;
          qi::rule<Iterator, JParserSpirit(), ascii::space_type> datablock;
          qi::rule<Iterator, JParserSpirit(), ascii::space_type> jfile;

          };
    public:
      gplib::trealdata frequency;
      gplib::trealdata Rx;
      gplib::trealdata Ry;
      gplib::trealdata Rz;
      gplib::tcompdata DataXX;
      gplib::tcompdata DataXY;
      gplib::tcompdata DataYX;
      gplib::tcompdata DataYY;
      gplib::tcompdata DataZX;
      gplib::tcompdata DataZY;
      gplib::trealdata dDataXX;
      gplib::trealdata dDataXY;
      gplib::trealdata dDataYX;
      gplib::trealdata dDataYY;
      gplib::trealdata dDataZX;
      gplib::trealdata dDataZY;
      double latitude;
      double longitude;
      double elevation;
      double azimuth;
      std::string name;
      bool tassigned;
      bool zassigned;
      bool rassigned;
      void ParseFile(std::string &Filename)
      {

      }

      JParserSpirit(){

      }

      virtual ~JParserSpirit();
      };

  }

#endif /* JPARSERSPIRIT_H_ */
