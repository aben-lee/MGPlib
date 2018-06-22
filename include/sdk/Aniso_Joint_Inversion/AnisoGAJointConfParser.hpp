#ifndef INC_AnisoGAJointConfParser_hpp_
#define INC_AnisoGAJointConfParser_hpp_

#include "AnisoGAJointConfParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20100319): "AnisoGAJointConf.g" -> "AnisoGAJointConfParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "AnisoGAJointConfParserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 1 "AnisoGAJointConf.g"
#line 8 "AnisoGAJointConfParser.cpp"

	#include <string>
	#include <vector>
	#include <iostream>
	#include <cstdlib>

#line 19 "AnisoGAJointConfParser.hpp"
class CUSTOM_API AnisoGAJointConfParser : public antlr::LLkParser, public AnisoGAJointConfParserTokenTypes
{
#line 21 "AnisoGAJointConf.g"

private: 
int i; double dtemp; int itemp; std::string stemp; bool btemp;
public: 
bool verbose;
int mtfitexponent;
int popsize;
double inittemp;
double coolingratio;
int generations;
double mutationprob;
double crossoverprob;
int threads;
double starttime;
double endtime;
double tensorerror;
double reserror;
double phaseerror;
std::string gatype;
std::string outputbase;
std::string mode;
std::string mtfit;
std::string mtinputdata;
std::string ptensordata;
int annealinggeneration;
bool elitist;
std::vector< double > thickbase;
std::vector< double > thickstep;
std::vector< int > thicksizes;
std::vector< double > resbase;
std::vector< double > resstep;
std::vector< int > ressizes;
std::vector< double > velbase;
std::vector< double > velstep;
std::vector< int > velsizes;
std::vector< double > aresbase;
std::vector< double > aresstep;
std::vector< int > aressizes;
std::vector< double > avelbase;
std::vector< double > avelstep;
std::vector< int > avelsizes;
std::vector< double > strikebase;
std::vector< double > strikestep;
std::vector< int > strikesizes;
std::vector< double > dstrikebase;
std::vector< double > dstrikestep;
std::vector< int > dstrikesizes;
std::vector< double > weights;
double conddiffweight;
double anisotropyweight;
double strikediffweight;
double veldiffweight;
double anisovelweight;
double deltastrikediffweight;
double avelratio;
#line 23 "AnisoGAJointConfParser.hpp"
public:
	void initializeASTFactory( antlr::ASTFactory& factory );
protected:
        AnisoGAJointConfParser(antlr::TokenBuffer& tokenBuf, int k): antlr::LLkParser(tokenBuf,k)
        {
        }

public:
        AnisoGAJointConfParser(antlr::TokenBuffer& tokenBuf): antlr::LLkParser(tokenBuf,10)
        {
        }

protected:
        AnisoGAJointConfParser(antlr::TokenStream& lexer, int k): antlr::LLkParser(lexer,k)
        {
        }

public:
        AnisoGAJointConfParser(antlr::TokenStream& lexer): antlr::LLkParser(lexer,10)
        {
        }
        AnisoGAJointConfParser(const antlr::ParserSharedInputState& state): antlr::LLkParser(state,10)
        {
        }
	int getNumTokens() const
	{
		return AnisoGAJointConfParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return AnisoGAJointConfParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return AnisoGAJointConfParser::tokenNames;
	}
public: void configentry(){

	try {      // for error handling
			{
				switch (LA(1)) {
				case VERBOSET:
				{
					match(VERBOSET);
					match(EQUAL);
					verbose = boolvalue();
					break;
				}
				case MTFITEXPONENTT:
				{
					match(MTFITEXPONENTT);
					match(EQUAL);
					mtfitexponent = numvalue();
					break;
				}
				case POPSIZET:
				{
					match(POPSIZET);
					match(EQUAL);
					popsize = numvalue();
					break;
				}
				case INITTEMPT:
				{
					match(INITTEMPT);
					match(EQUAL);
					inittemp = numvalue();
					break;
				}
				case COOLINGRATIOT:
				{
					match(COOLINGRATIOT);
					match(EQUAL);
					coolingratio = numvalue();
					break;
				}
				case GENERATIONST:
				{
					match(GENERATIONST);
					match(EQUAL);
					generations = numvalue();
					break;
				}
				case MUTATIONPROBT:
				{
					match(MUTATIONPROBT);
					match(EQUAL);
					mutationprob = numvalue();
					break;
				}
				case CROSSOVERPROBT:
				{
					match(CROSSOVERPROBT);
					match(EQUAL);
					crossoverprob = numvalue();
					break;
				}
				case THREADST:
				{
					match(THREADST);
					match(EQUAL);
					threads = numvalue();
					break;
				}
				case STARTTIMET:
				{
					match(STARTTIMET);
					match(EQUAL);
					starttime = numvalue();
					break;
				}
				case ENDTIMET:
				{
					match(ENDTIMET);
					match(EQUAL);
					endtime = numvalue();
					break;
				}
				case TENSORERRORT:
				{
					match(TENSORERRORT);
					match(EQUAL);
					tensorerror = numvalue();
					break;
				}
				case RESERRORT:
				{
					match(RESERRORT);
					match(EQUAL);
					reserror = numvalue();
					break;
				}
				case PHASEERRORT:
				{
					match(PHASEERRORT);
					match(EQUAL);
					phaseerror = numvalue();
					break;
				}
				case GATYPET:
				{
					match(GATYPET);
					match(EQUAL);
					gatype = stringvalue();
					break;
				}
				case OUTPUTBASET:
				{
					match(OUTPUTBASET);
					match(EQUAL);
					outputbase = stringvalue();
					break;
				}
				case MODET:
				{
					match(MODET);
					match(EQUAL);
					mode = stringvalue();
					break;
				}
				case MTFITT:
				{
					match(MTFITT);
					match(EQUAL);
					mtfit = stringvalue();
					break;
				}
				case MTINPUTDATAT:
				{
					match(MTINPUTDATAT);
					match(EQUAL);
					mtinputdata = stringvalue();
					break;
				}
				case PTENSORDATAT:
				{
					match(PTENSORDATAT);
					match(EQUAL);
					ptensordata = stringvalue();
					break;
				}
				case ANNEALINGGENERATIONT:
				{
					match(ANNEALINGGENERATIONT);
					match(EQUAL);
					annealinggeneration = numvalue();
					break;
				}
				case ELITISTT:
				{
					match(ELITISTT);
					match(EQUAL);
					elitist = boolvalue();
					break;
				}
				case THICKBASET:
				{
					match(THICKBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 101 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 200 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt92 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 102 "AnisoGAJointConf.g"
							if (i < thickbase.size()) { thickbase.at(i) = dtemp; }
							else{ thickbase.push_back(dtemp); }++i;
#line 210 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt92 >= 1) { goto _loop92; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt92++;
				}
			_loop92:;
			}  // ( ... )+
					break;
				}
				case THICKSTEPT:
				{
					match(THICKSTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 103 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 230 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt98 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 104 "AnisoGAJointConf.g"
							if (i < thickstep.size()) { thickstep.at(i) = dtemp; }
							else{ thickstep.push_back(dtemp); }++i;
#line 240 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt98 >= 1) { goto _loop98; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt98++;
				}
			_loop98:;
			}  // ( ... )+
					break;
				}
				case THICKSIZEST:
				{
					match(THICKSIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 105 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 260 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt104 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 106 "AnisoGAJointConf.g"
							if (i < thicksizes.size()) { thicksizes.at(i) = itemp; }
							else{ thicksizes.push_back(itemp); }++i;
#line 270 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt104 >= 1) { goto _loop104; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt104++;
				}
			_loop104:;
			}  // ( ... )+
					break;
				}
				case RESBASET:
				{
					match(RESBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 107 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 290 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt110 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 108 "AnisoGAJointConf.g"
							if (i < resbase.size()) { resbase.at(i) = dtemp; }
							else{ resbase.push_back(dtemp); }++i;
#line 300 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt110 >= 1) { goto _loop110; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt110++;
				}
			_loop110:;
			}  // ( ... )+
					break;
				}
				case RESSTEPT:
				{
					match(RESSTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 109 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 320 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt116 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 110 "AnisoGAJointConf.g"
							if (i < resstep.size()) { resstep.at(i) = dtemp; }
							else{ resstep.push_back(dtemp); }++i;
#line 330 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt116 >= 1) { goto _loop116; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt116++;
				}
			_loop116:;
			}  // ( ... )+
					break;
				}
				case RESSIZEST:
				{
					match(RESSIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 111 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 350 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt122 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 112 "AnisoGAJointConf.g"
							if (i < ressizes.size()) { ressizes.at(i) = itemp; }
							else{ ressizes.push_back(itemp); }++i;
#line 360 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt122 >= 1) { goto _loop122; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt122++;
				}
			_loop122:;
			}  // ( ... )+
					break;
				}
				case VELBASET:
				{
					match(VELBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 113 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 380 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt128 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 114 "AnisoGAJointConf.g"
							if (i < velbase.size()) { velbase.at(i) = dtemp; }
							else{ velbase.push_back(dtemp); }++i;
#line 390 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt128 >= 1) { goto _loop128; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt128++;
				}
			_loop128:;
			}  // ( ... )+
					break;
				}
				case VELSTEPT:
				{
					match(VELSTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 115 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 410 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt134 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 116 "AnisoGAJointConf.g"
							if (i < velstep.size()) { velstep.at(i) = dtemp; }
							else{ velstep.push_back(dtemp); }++i;
#line 420 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt134 >= 1) { goto _loop134; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt134++;
				}
			_loop134:;
			}  // ( ... )+
					break;
				}
				case VELSIZEST:
				{
					match(VELSIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 117 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 440 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt140 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 118 "AnisoGAJointConf.g"
							if (i < velsizes.size()) { velsizes.at(i) = itemp; }
							else{ velsizes.push_back(itemp); }++i;
#line 450 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt140 >= 1) { goto _loop140; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt140++;
				}
			_loop140:;
			}  // ( ... )+
					break;
				}
				case ARESBASET:
				{
					match(ARESBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 119 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 470 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt146 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 120 "AnisoGAJointConf.g"
							if (i < aresbase.size()) { aresbase.at(i) = dtemp; }
							else{ aresbase.push_back(dtemp); }++i;
#line 480 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt146 >= 1) { goto _loop146; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt146++;
				}
			_loop146:;
			}  // ( ... )+
					break;
				}
				case ARESSTEPT:
				{
					match(ARESSTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 121 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 500 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt152 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 122 "AnisoGAJointConf.g"
							if (i < aresstep.size()) { aresstep.at(i) = dtemp; }
							else{ aresstep.push_back(dtemp); }++i;
#line 510 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt152 >= 1) { goto _loop152; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt152++;
				}
			_loop152:;
			}  // ( ... )+
					break;
				}
				case ARESSIZEST:
				{
					match(ARESSIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 123 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 530 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt158 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 124 "AnisoGAJointConf.g"
							if (i < aressizes.size()) { aressizes.at(i) = itemp; }
							else{ aressizes.push_back(itemp); }++i;
#line 540 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt158 >= 1) { goto _loop158; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt158++;
				}
			_loop158:;
			}  // ( ... )+
					break;
				}
				case AVELBASET:
				{
					match(AVELBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 125 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 560 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt164 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 126 "AnisoGAJointConf.g"
							if (i < avelbase.size()) { avelbase.at(i) = dtemp; }
							else{ avelbase.push_back(dtemp); }++i;
#line 570 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt164 >= 1) { goto _loop164; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt164++;
				}
			_loop164:;
			}  // ( ... )+
					break;
				}
				case AVELSTEPT:
				{
					match(AVELSTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 127 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 590 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt170 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 128 "AnisoGAJointConf.g"
							if (i < avelstep.size()) { avelstep.at(i) = dtemp; }
							else{ avelstep.push_back(dtemp); }++i;
#line 600 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt170 >= 1) { goto _loop170; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt170++;
				}
			_loop170:;
			}  // ( ... )+
					break;
				}
				case AVELSIZEST:
				{
					match(AVELSIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 129 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 620 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt176 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 130 "AnisoGAJointConf.g"
							if (i < avelsizes.size()) { avelsizes.at(i) = itemp; }
							else{ avelsizes.push_back(itemp); }++i;
#line 630 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt176 >= 1) { goto _loop176; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt176++;
				}
			_loop176:;
			}  // ( ... )+
					break;
				}
				case STRIKEBASET:
				{
					match(STRIKEBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 131 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 650 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt182 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 132 "AnisoGAJointConf.g"
							if (i < strikebase.size()) { strikebase.at(i) = dtemp; }
							else{ strikebase.push_back(dtemp); }++i;
#line 660 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt182 >= 1) { goto _loop182; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt182++;
				}
			_loop182:;
			}  // ( ... )+
					break;
				}
				case STRIKESTEPT:
				{
					match(STRIKESTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 133 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 680 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt188 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 134 "AnisoGAJointConf.g"
							if (i < strikestep.size()) { strikestep.at(i) = dtemp; }
							else{ strikestep.push_back(dtemp); }++i;
#line 690 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt188 >= 1) { goto _loop188; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt188++;
				}
			_loop188:;
			}  // ( ... )+
					break;
				}
				case STRIKESIZEST:
				{
					match(STRIKESIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 135 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 710 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt194 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 136 "AnisoGAJointConf.g"
							if (i < strikesizes.size()) { strikesizes.at(i) = itemp; }
							else{ strikesizes.push_back(itemp); }++i;
#line 720 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt194 >= 1) { goto _loop194; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt194++;
				}
			_loop194:;
			}  // ( ... )+
					break;
				}
				case DSTRIKEBASET:
				{
					match(DSTRIKEBASET);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 137 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 740 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt200 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 138 "AnisoGAJointConf.g"
							if (i < dstrikebase.size()) { dstrikebase.at(i) = dtemp; }
							else{ dstrikebase.push_back(dtemp); }++i;
#line 750 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt200 >= 1) { goto _loop200; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt200++;
				}
			_loop200:;
			}  // ( ... )+
					break;
				}
				case DSTRIKESTEPT:
				{
					match(DSTRIKESTEPT);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 139 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 770 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt206 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 140 "AnisoGAJointConf.g"
							if (i < dstrikestep.size()) { dstrikestep.at(i) = dtemp; }
							else{ dstrikestep.push_back(dtemp); }++i;
#line 780 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt206 >= 1) { goto _loop206; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt206++;
				}
			_loop206:;
			}  // ( ... )+
					break;
				}
				case DSTRIKESIZEST:
				{
					match(DSTRIKESIZEST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 141 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 800 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt212 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						itemp = numvalue();
						if (inputState->guessing == 0) {
#line 142 "AnisoGAJointConf.g"
							if (i < dstrikesizes.size()) { dstrikesizes.at(i) = itemp; }
							else{ dstrikesizes.push_back(itemp); }++i;
#line 810 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt212 >= 1) { goto _loop212; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt212++;
				}
			_loop212:;
			}  // ( ... )+
					break;
				}
				case WEIGHTST:
				{
					match(WEIGHTST);
					match(EQUAL);
					if (inputState->guessing == 0) {
#line 143 "AnisoGAJointConf.g"
						i = 0; dtemp = 0; stemp = ""; btemp = false;
#line 830 "AnisoGAJointConfParser.cpp"
					}
			{ // ( ... )+
				int _cnt218 = 0;
				for (;;) {
					if ((LA(1) == NUMBER)) {
						dtemp = numvalue();
						if (inputState->guessing == 0) {
#line 144 "AnisoGAJointConf.g"
							if (i < weights.size()) { weights.at(i) = dtemp; }
							else{ weights.push_back(dtemp); }++i;
#line 840 "AnisoGAJointConfParser.cpp"
						}
					}
					else {
						if (_cnt218 >= 1) { goto _loop218; }
						else { throw antlr::NoViableAltException(LT(1), getFilename()); }
					}

					_cnt218++;
				}
			_loop218:;
			}  // ( ... )+
					break;
				}
				case CONDDIFFWEIGHTT:
				{
					match(CONDDIFFWEIGHTT);
					match(EQUAL);
					conddiffweight = numvalue();
					break;
				}
				case ANISOTROPYWEIGHTT:
				{
					match(ANISOTROPYWEIGHTT);
					match(EQUAL);
					anisotropyweight = numvalue();
					break;
				}
				case STRIKEDIFFWEIGHTT:
				{
					match(STRIKEDIFFWEIGHTT);
					match(EQUAL);
					strikediffweight = numvalue();
					break;
				}
				case VELDIFFWEIGHTT:
				{
					match(VELDIFFWEIGHTT);
					match(EQUAL);
					veldiffweight = numvalue();
					break;
				}
				case ANISOVELWEIGHTT:
				{
					match(ANISOVELWEIGHTT);
					match(EQUAL);
					anisovelweight = numvalue();
					break;
				}
				case DELTASTRIKEDIFFWEIGHTT:
				{
					match(DELTASTRIKEDIFFWEIGHTT);
					match(EQUAL);
					deltastrikediffweight = numvalue();
					break;
				}
				case AVELRATIOT:
				{
					match(AVELRATIOT);
					match(EQUAL);
					avelratio = numvalue();
					break;
				}
				default:
				{
					throw antlr::NoViableAltException(LT(1), getFilename());
				}
				}
			}
	}
	catch (antlr::RecognitionException& ex) {
		if (inputState->guessing == 0) {
			reportError(ex);
			recover(ex, _tokenSet_0);
		}
		else {
			throw;
		}
	}
}
	public: bool  boolvalue(){
#line 170 "AnisoGAJointConf.g"
		bool r;
#line 922 "AnisoGAJointConfParser.cpp"

		try {      // for error handling
				{
					switch (LA(1)) {
					case TRUE:
					{
						match(TRUE);
						if (inputState->guessing == 0) {
#line 171 "AnisoGAJointConf.g"
							r = true;
#line 933 "AnisoGAJointConfParser.cpp"
						}
						break;
					}
					case FALSE:
					{
						match(FALSE);
						if (inputState->guessing == 0) {
#line 171 "AnisoGAJointConf.g"
							r = false;
#line 943 "AnisoGAJointConfParser.cpp"
						}
						break;
					}
					default:
					{
						throw antlr::NoViableAltException(LT(1), getFilename());
					}
					}
				}
		}
		catch (antlr::RecognitionException& ex) {
			if (inputState->guessing == 0) {
				reportError(ex);
				recover(ex, _tokenSet_0);
			}
			else {
				throw;
			}
		}
		return r;
	}
public: double  numvalue(){
#line 166 "AnisoGAJointConf.g"
	double r;
#line 968 "AnisoGAJointConfParser.cpp"
	antlr::RefToken  currvalue = antlr::nullToken;

	try {      // for error handling
		currvalue = LT(1);
		match(NUMBER);
		if (inputState->guessing == 0) {
#line 167 "AnisoGAJointConf.g"
			r = atof(currvalue->getText().c_str());
#line 977 "AnisoGAJointConfParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if (inputState->guessing == 0) {
			reportError(ex);
			recover(ex, _tokenSet_1);
		}
		else {
			throw;
		}
	}
	return r;
}
public: std::string  stringvalue()}{
#line 174 "AnisoGAJointConf.g"
	std::string r;
#line 994 "AnisoGAJointConfParser.cpp"
	antlr::RefToken  currvalue = antlr::nullToken;

	try {      // for error handling
		currvalue = LT(1);
		match(STRING);
		if (inputState->guessing == 0) {
#line 175 "AnisoGAJointConf.g"
			r = currvalue->getText();
#line 1003 "AnisoGAJointConfParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if (inputState->guessing == 0) {
			reportError(ex);
			recover(ex, _tokenSet_0);
		}
		else {
			throw;
		}
	}
	return r;
}
	public: void configfile(){
#line 153 "AnisoGAJointConf.g"

		verbose = false;
		mtfitexponent = 2;
		conddiffweight = 1;
		anisotropyweight = 1;
		strikediffweight = 1;
		veldiffweight = 1;
		anisovelweight = 1;
		deltastrikediffweight = 1;

#line 1029 "AnisoGAJointConfParser.cpp"

		try {      // for error handling
				{ // ( ... )+
					int _cnt250 = 0;
					for (;;) {
						if ((_tokenSet_2.member(LA(1)))) {
							configentry();
							{
								if ((LA(1) == COMMENT) && (_tokenSet_0.member(LA(2))) && (LA(3) == antlr::Token::EOF_TYPE || LA(3) == EQUAL || LA(3) == COMMENT) && (_tokenSet_3.member(LA(4))) && (_tokenSet_1.member(LA(5))) && (_tokenSet_4.member(LA(6))) && (_tokenSet_5.member(LA(7))) && (_tokenSet_5.member(LA(8))) && (_tokenSet_5.member(LA(9))) && (_tokenSet_5.member(LA(10)))) {
									match(COMMENT);
								}
								else if ((_tokenSet_0.member(LA(1))) && (LA(2) == antlr::Token::EOF_TYPE || LA(2) == EQUAL || LA(2) == COMMENT) && (_tokenSet_3.member(LA(3))) && (_tokenSet_1.member(LA(4))) && (_tokenSet_4.member(LA(5))) && (_tokenSet_5.member(LA(6))) && (_tokenSet_5.member(LA(7))) && (_tokenSet_5.member(LA(8))) && (_tokenSet_5.member(LA(9))) && (_tokenSet_5.member(LA(10)))) {
								}
								else {
									throw antlr::NoViableAltException(LT(1), getFilename());
								}

							}
						}
						else {
							if (_cnt250 >= 1) { goto _loop250; }
							else { throw antlr::NoViableAltException(LT(1), getFilename()); }
						}

						_cnt250++;
					}
				_loop250:;
				}  // ( ... )+
		{ // ( ... )*
			for (;;) {
				if ((LA(1) == COMMENT)) {
					match(COMMENT);
				}
				else {
					goto _loop252;
				}

			}
		_loop252:;
		} // ( ... )*
			match(antlr::Token::EOF_TYPE);
		}
		catch (antlr::RecognitionException& ex) {
			if (inputState->guessing == 0) {
				reportError(ex);
				recover(ex, _tokenSet_6);
			}
			else {
				throw;
			}
		}
	}
public:
	antlr::RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	antlr::RefAST returnAST;
private:
	static const char* tokenNames[]{
		"<0>",
			"EOF",
			"<2>",
			"NULL_TREE_LOOKAHEAD",
			"VERBOSET",
			"EQUAL",
			"MTFITEXPONENTT",
			"NUMBER",
			"POPSIZET",
			"INITTEMPT",
			"COOLINGRATIOT",
			"GENERATIONST",
			"MUTATIONPROBT",
			"CROSSOVERPROBT",
			"THREADST",
			"STARTTIMET",
			"ENDTIMET",
			"TENSORERRORT",
			"RESERRORT",
			"PHASEERRORT",
			"GATYPET",
			"STRING",
			"OUTPUTBASET",
			"MODET",
			"MTFITT",
			"MTINPUTDATAT",
			"PTENSORDATAT",
			"ANNEALINGGENERATIONT",
			"ELITISTT",
			"THICKBASET",
			"THICKSTEPT",
			"THICKSIZEST",
			"RESBASET",
			"RESSTEPT",
			"RESSIZEST",
			"VELBASET",
			"VELSTEPT",
			"VELSIZEST",
			"ARESBASET",
			"ARESSTEPT",
			"ARESSIZEST",
			"AVELBASET",
			"AVELSTEPT",
			"AVELSIZEST",
			"STRIKEBASET",
			"STRIKESTEPT",
			"STRIKESIZEST",
			"DSTRIKEBASET",
			"DSTRIKESTEPT",
			"DSTRIKESIZEST",
			"WEIGHTST",
			"CONDDIFFWEIGHTT",
			"ANISOTROPYWEIGHTT",
			"STRIKEDIFFWEIGHTT",
			"VELDIFFWEIGHTT",
			"ANISOVELWEIGHTT",
			"DELTASTRIKEDIFFWEIGHTT",
			"AVELRATIOT",
			"COMMENT",
			"TRUE",
			"FALSE",
			"WS",
			"NEWLINE",
			"REAL",
			"INT",
			"DIGIT",
			"CHAR",
			"OTHER",
			0
	};
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 68;
#else
	enum {
		NUM_TOKENS = 68
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[]={ 4292869970UL, 134217727UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_0(_tokenSet_0_data_, 4);
	static const unsigned long _tokenSet_1_data_[] = { 4292870098UL, 134217727UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_1(_tokenSet_1_data_, 4);
	static const unsigned long _tokenSet_2_data_[] = { 4292869968UL, 67108863UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_2 = (_tokenSet_2_data_, 4);
	static const unsigned long _tokenSet_3_data_[] = { 2097282UL, 469762048UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_3(_tokenSet_3_data_, 4);
	static const unsigned long _tokenSet_4_data_[]{ 4292870130UL, 134217727UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_4(_tokenSet_4_data_, 4);
	static const unsigned long _tokenSet_5_data_[]={ 4294967282UL, 536870911UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_5(_tokenSet_5_data_, 4);
	static const unsigned long _tokenSet_6_data_[] = { 2UL, 0UL, 0UL, 0UL };
	static const antlr::BitSet _tokenSet_6(_tokenSet_6_data_, 4);

};

#endif /*INC_AnisoGAJointConfParser_hpp_*/
