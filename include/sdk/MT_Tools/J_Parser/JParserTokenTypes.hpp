#ifndef INC_JParserTokenTypes_hpp_
#define INC_JParserTokenTypes_hpp_

/* $ANTLR 2.7.7 (20130428): "JParser.g" -> "JParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API JParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		NEWLINE = 4,
		COMMENT = 5,
		AZIMUTH = 6,
		LATITUDE = 7,
		LONGITUDE = 8,
		ELEVATION = 9,
		STATION = 10,
		MISDAT = 11,
		EQUAL = 12,
		ZXX = 13,
		ZXY = 14,
		ZYX = 15,
		ZYY = 16,
		RXX = 17,
		RXY = 18,
		RYX = 19,
		RYY = 20,
		TZX = 21,
		TZY = 22,
		SI = 23,
		FIELD = 24,
		UNITS = 25,
		UNDEF = 26,
		ENTRY = 27,
		PLUS = 28,
		MINUS = 29,
		WS = 30,
		DIGIT = 31,
		CHAR = 32,
		OTHER = 33,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_JParserTokenTypes_hpp_*/
