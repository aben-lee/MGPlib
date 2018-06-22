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

namespace gplib
  {

    class JParserSpirit
      {
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
      void ParseFile(std::string &Filename);
      JParserSpirit();
      virtual ~JParserSpirit();
      };

  }

#endif /* JPARSERSPIRIT_H_ */
