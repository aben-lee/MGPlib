#ifndef INC_EDIParserTokenTypes_hpp_
#define INC_EDIParserTokenTypes_hpp_

/* $ANTLR 2.7.7 (20130428): "EdiParser2.g" -> "EDIParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API EDIParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		LITERAL_NFREQ = 4,
		LITERAL_LATITUDE = 5,
		LITERAL_LONGITUDE = 6,
		LITERAL_AZIMUTH = 7,
		LITERAL_ELEVATION = 8,
		LITERAL_REFLONG = 9,
		LITERAL_REFLAT = 10,
		STRING = 11,
		EQUAL = 12,
		DATE = 13,
		NUMBER = 14,
		HEAD = 15,
		// ">INFO" = 16
		SPECIAL = 17,
		// ">EMEAS" = 18
		// ">HMEAS" = 19
		LITERAL_DEFINEMEAS = 20,
		LITERAL_SPECTRASET = 21,
		// "//" = 22
		INT = 23,
		LITERAL_SPECTRA = 24,
		// ";" = 25
		LITERAL_MTSECT = 26,
		// ">ZXXR" = 27
		// ">ZXXI" = 28
		// ">ZXYR" = 29
		// ">ZXYI" = 30
		// ">ZYXR" = 31
		// ">ZYXI" = 32
		// ">ZYYR" = 33
		// ">ZYYI" = 34
		// ">TXR.EXP" = 35
		// ">TXI.EXP" = 36
		// ">TYR.EXP" = 37
		// ">TYI.EXP" = 38
		SLASH = 39,
		// ">FREQ" = 40
		// ">ZXXR.VAR" = 41
		// ">ZXXI.VAR" = 42
		// ">ZXX.VAR" = 43
		// ">ZXYR.VAR" = 44
		// ">ZXYI.VAR" = 45
		// ">ZXY.VAR" = 46
		// ">ZYXR.VAR" = 47
		// ">ZYXI.VAR" = 48
		// ">ZYX.VAR" = 49
		// ">ZYYR.VAR" = 50
		// ">ZYYI.VAR" = 51
		// ">ZYY.VAR" = 52
		// ">TXVAR.EXP" = 53
		// ">TYVAR.EXP" = 54
		// ">ZROT" = 55
		KEYWORD = 56,
		COMMENT = 57,
		// ">END" = 58
		COLON = 59,
		WS = 60,
		EXKL = 61,
		DIGIT = 62,
		LETTER = 63,
		OTHER = 64,
		NONUMBER = 65,
		LEGAL_CHAR = 66,
		SIGN = 67,
		REAL = 68,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_EDIParserTokenTypes_hpp_*/
