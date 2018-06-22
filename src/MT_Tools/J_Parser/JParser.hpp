#ifndef INC_JParser_hpp_
#define INC_JParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20110618): "JParser.g" -> "JParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "JParserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 1 "JParser.g"

	#include <iostream>	
	#include <iomanip>
	#include <string>
	#include <cstdlib>
	#include "types.h"

#line 20 "JParser.hpp"
class CUSTOM_API JParser : public antlr::LLkParser, public JParserTokenTypes
{
#line 21 "JParser.g"

private:
	bool zsection;
	bool rsection;
	bool tsection;
	bool isstring;
	int currindex;
	gplib::pcompdata CurrentData;
	gplib::prealdata CurrentError;
	gplib::prealdata CurrentCoh;
	double convfactor;
	double *currdouble;
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
#line 24 "JParser.hpp"
public:
	void initializeASTFactory( antlr::ASTFactory& factory );
protected:
	JParser(antlr::TokenBuffer& tokenBuf, int k);
public:
	JParser(antlr::TokenBuffer& tokenBuf);
protected:
	JParser(antlr::TokenStream& lexer, int k);
public:
	JParser(antlr::TokenStream& lexer);
	JParser(const antlr::ParserSharedInputState& state);
	int getNumTokens() const
	{
		return JParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return JParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return JParser::tokenNames;
	}
	public: void jfile();
	public: void commentblock();
	public: void informationblock();
	public: std::string  stringvalue();
	public: void datablock();
	public: double  datavalue();
	public: void datasection();
	public: void zdata();
	public: void rdata();
	public: void tdata();
public:
	antlr::RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	antlr::RefAST returnAST;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 33;
#else
	enum {
		NUM_TOKENS = 33
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const antlr::BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const antlr::BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const antlr::BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const antlr::BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const antlr::BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const antlr::BitSet _tokenSet_5;
	static const unsigned long _tokenSet_6_data_[];
	static const antlr::BitSet _tokenSet_6;
	static const unsigned long _tokenSet_7_data_[];
	static const antlr::BitSet _tokenSet_7;
	static const unsigned long _tokenSet_8_data_[];
	static const antlr::BitSet _tokenSet_8;
	static const unsigned long _tokenSet_9_data_[];
	static const antlr::BitSet _tokenSet_9;
	static const unsigned long _tokenSet_10_data_[];
	static const antlr::BitSet _tokenSet_10;
	static const unsigned long _tokenSet_11_data_[];
	static const antlr::BitSet _tokenSet_11;
	static const unsigned long _tokenSet_12_data_[];
	static const antlr::BitSet _tokenSet_12;
	static const unsigned long _tokenSet_13_data_[];
	static const antlr::BitSet _tokenSet_13;
	static const unsigned long _tokenSet_14_data_[];
	static const antlr::BitSet _tokenSet_14;
	static const unsigned long _tokenSet_15_data_[];
	static const antlr::BitSet _tokenSet_15;
	static const unsigned long _tokenSet_16_data_[];
	static const antlr::BitSet _tokenSet_16;
};

#endif /*INC_JParser_hpp_*/
