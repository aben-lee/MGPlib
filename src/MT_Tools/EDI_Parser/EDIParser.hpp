#ifndef INC_EDIParser_hpp_
#define INC_EDIParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20110618): "EdiParser2.g" -> "EDIParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "EDIParserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 1 "EdiParser2.g"

	#include <iostream>	
	#include "types.h"
	#include "convert.h"
	#include <complex>	

#line 19 "EDIParser.hpp"
class CUSTOM_API EDIParser : public antlr::LLkParser, public EDIParserTokenTypes
{
#line 20 "EdiParser2.g"

private:
	bool zsection;
	bool rsection;
	bool isstring;
	int nfreq;
	double convfactor;
	double globalconv;
public:
	gplib::trealdata frequency;
	gplib::trealdata rotangles;
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
#line 23 "EDIParser.hpp"
public:
	void initializeASTFactory( antlr::ASTFactory& factory );
protected:
	EDIParser(antlr::TokenBuffer& tokenBuf, int k);
public:
	EDIParser(antlr::TokenBuffer& tokenBuf);
protected:
	EDIParser(antlr::TokenStream& lexer, int k);
public:
	EDIParser(antlr::TokenStream& lexer);
	EDIParser(const antlr::ParserSharedInputState& state);
	int getNumTokens() const
	{
		return EDIParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return EDIParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return EDIParser::tokenNames;
	}
	public: void option();
	public: double  lat_long();
	public: double  datavalue();
	public: void option_list();
	public: void head_block();
	public: void info_block();
	public: void info_text();
	public: void emeas_block();
	public: void hmeas_block();
	public: void def_meas_section();
	public: void spectrasect_block();
	public: void spectra_block();
	public: void spectra_section();
	public: void mtsect_block();
	public: void mt_complex_data_block();
	public: void mt_real_data_block();
	public: void mt_section();
	public: void end_block();
	public: void edi_file();
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
	static const int NUM_TOKENS = 69;
#else
	enum {
		NUM_TOKENS = 69
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

#endif /*INC_EDIParser_hpp_*/
