/* $ANTLR 2.7.7 (20110618): "JParser.g" -> "JParser.cpp"$ */
#include "JParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "JParser.g"
#line 8 "JParser.cpp"
JParser::JParser(antlr::TokenBuffer& tokenBuf, int k)
: antlr::LLkParser(tokenBuf,k)
{
}

JParser::JParser(antlr::TokenBuffer& tokenBuf)
: antlr::LLkParser(tokenBuf,10)
{
}

JParser::JParser(antlr::TokenStream& lexer, int k)
: antlr::LLkParser(lexer,k)
{
}

JParser::JParser(antlr::TokenStream& lexer)
: antlr::LLkParser(lexer,10)
{
}

JParser::JParser(const antlr::ParserSharedInputState& state)
: antlr::LLkParser(state,10)
{
}

void JParser::jfile() {
#line 59 "JParser.g"
	
		zassigned = false;
		rassigned = false;
		tassigned = false;
		latitude = 0;
		longitude =0;
		elevation = 0;
		azimuth = 0;
		name = "default";
	
#line 46 "JParser.cpp"
	
	try {      // for error handling
		commentblock();
		informationblock();
		name=stringvalue();
		match(NEWLINE);
		datablock();
		match(antlr::Token::EOF_TYPE);
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

void JParser::commentblock() {
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == COMMENT)) {
				match(COMMENT);
			}
			else {
				goto _loop4;
			}
			
		}
		_loop4:;
		} // ( ... )*
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}

void JParser::informationblock() {
#line 78 "JParser.g"
	double temp;
#line 95 "JParser.cpp"
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if (((LA(1) >= AZIMUTH && LA(1) <= STATION))) {
				{
				switch ( LA(1)) {
				case AZIMUTH:
				{
					match(AZIMUTH);
					if ( inputState->guessing==0 ) {
#line 80 "JParser.g"
						currdouble = &azimuth; isstring = false; std::cout << "Reading Az. ";
#line 109 "JParser.cpp"
					}
					break;
				}
				case LATITUDE:
				{
					match(LATITUDE);
					if ( inputState->guessing==0 ) {
#line 81 "JParser.g"
						currdouble = &latitude; isstring = false;std::cout << "Reading Lat. ";
#line 119 "JParser.cpp"
					}
					break;
				}
				case LONGITUDE:
				{
					match(LONGITUDE);
					if ( inputState->guessing==0 ) {
#line 82 "JParser.g"
						currdouble = &longitude; isstring = false;std::cout << "Reading Long. ";
#line 129 "JParser.cpp"
					}
					break;
				}
				case ELEVATION:
				{
					match(ELEVATION);
					if ( inputState->guessing==0 ) {
#line 83 "JParser.g"
						currdouble = &elevation; isstring = false;std::cout << "Reading El. ";
#line 139 "JParser.cpp"
					}
					break;
				}
				case STATION:
				{
					match(STATION);
					if ( inputState->guessing==0 ) {
#line 84 "JParser.g"
						isstring = true;
#line 149 "JParser.cpp"
					}
					break;
				}
				default:
				{
					throw antlr::NoViableAltException(LT(1), getFilename());
				}
				}
				}
				match(EQUAL);
				{
				if (((LA(1) == ENTRY) && (LA(2) == NEWLINE) && (_tokenSet_1.member(LA(3))) && (LA(4) == NEWLINE || LA(4) == EQUAL) && (_tokenSet_2.member(LA(5))) && (_tokenSet_3.member(LA(6))) && (_tokenSet_4.member(LA(7))) && (_tokenSet_5.member(LA(8))) && (_tokenSet_6.member(LA(9))) && (_tokenSet_7.member(LA(10))))&&(isstring)) {
					name=stringvalue();
					if ( inputState->guessing==0 ) {
#line 85 "JParser.g"
						std::cout << name << std::endl;
#line 166 "JParser.cpp"
					}
				}
				else if ((LA(1) == UNDEF || LA(1) == ENTRY) && (LA(2) == NEWLINE) && (_tokenSet_1.member(LA(3))) && (LA(4) == NEWLINE || LA(4) == EQUAL) && (_tokenSet_2.member(LA(5))) && (_tokenSet_3.member(LA(6))) && (_tokenSet_4.member(LA(7))) && (_tokenSet_5.member(LA(8))) && (_tokenSet_6.member(LA(9))) && (_tokenSet_7.member(LA(10)))) {
					temp=datavalue();
					if ( inputState->guessing==0 ) {
#line 86 "JParser.g"
						*currdouble = temp;std::cout << temp << std::endl;
#line 174 "JParser.cpp"
					}
				}
				else if ((LA(1) == NEWLINE)) {
				}
				else {
					throw antlr::NoViableAltException(LT(1), getFilename());
				}
				
				}
				match(NEWLINE);
			}
			else {
				goto _loop9;
			}
			
		}
		_loop9:;
		} // ( ... )*
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_8);
		} else {
			throw;
		}
	}
}

std::string  JParser::stringvalue() {
#line 190 "JParser.g"
	std::string r;
#line 207 "JParser.cpp"
	antlr::RefToken  currvalue = antlr::nullToken;
	
	try {      // for error handling
		currvalue = LT(1);
		match(ENTRY);
		if ( inputState->guessing==0 ) {
#line 191 "JParser.g"
			r = currvalue->getText();
#line 216 "JParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		} else {
			throw;
		}
	}
	return r;
}

void JParser::datablock() {
	
	try {      // for error handling
		{ // ( ... )+
		int _cnt12=0;
		for (;;) {
			if (((LA(1) >= ZXX && LA(1) <= TZY))) {
				datasection();
			}
			else {
				if ( _cnt12>=1 ) { goto _loop12; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt12++;
		}
		_loop12:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
}

double  JParser::datavalue() {
#line 185 "JParser.g"
	double r;
#line 261 "JParser.cpp"
	antlr::RefToken  currvalue = antlr::nullToken;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case UNDEF:
		{
			match(UNDEF);
			if ( inputState->guessing==0 ) {
#line 186 "JParser.g"
				r = -1000000000;
#line 273 "JParser.cpp"
			}
			break;
		}
		case ENTRY:
		{
			currvalue = LT(1);
			match(ENTRY);
			if ( inputState->guessing==0 ) {
#line 187 "JParser.g"
				r = atof(currvalue->getText().c_str());
#line 284 "JParser.cpp"
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
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_10);
		} else {
			throw;
		}
	}
	return r;
}

void JParser::datasection() {
#line 95 "JParser.g"
	
		CurrentData = NULL;
		zsection = false;
		rsection = false;
		tsection = false;
		currindex =0;
		convfactor = 1/(1000 * gplib::mu);
		int size;
#line 316 "JParser.cpp"
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case ZXX:
		{
			match(ZXX);
			if ( inputState->guessing==0 ) {
#line 104 "JParser.g"
				zsection = true; rsection = false; CurrentData=&DataXX;CurrentError=&dDataXX;CurrentCoh=&Rx;
#line 327 "JParser.cpp"
			}
			break;
		}
		case ZXY:
		{
			match(ZXY);
			if ( inputState->guessing==0 ) {
#line 105 "JParser.g"
				zsection = true; rsection = false;CurrentData=&DataXY;CurrentError=&dDataXY;CurrentCoh=&Rx;
#line 337 "JParser.cpp"
			}
			break;
		}
		case ZYX:
		{
			match(ZYX);
			if ( inputState->guessing==0 ) {
#line 106 "JParser.g"
				zsection = true; rsection = false;CurrentData=&DataYX;CurrentError=&dDataYX;CurrentCoh=&Ry;
#line 347 "JParser.cpp"
			}
			break;
		}
		case ZYY:
		{
			match(ZYY);
			if ( inputState->guessing==0 ) {
#line 107 "JParser.g"
				zsection = true; rsection = false;CurrentData=&DataYY;CurrentError=&dDataYY;CurrentCoh=&Ry;
#line 357 "JParser.cpp"
			}
			break;
		}
		case RXX:
		{
			match(RXX);
			if ( inputState->guessing==0 ) {
#line 108 "JParser.g"
				rsection = true; zsection = false;CurrentData=&DataXX;CurrentError=&dDataXX;
#line 367 "JParser.cpp"
			}
			break;
		}
		case RXY:
		{
			match(RXY);
			if ( inputState->guessing==0 ) {
#line 109 "JParser.g"
				rsection = true; zsection = false;CurrentData=&DataXY;CurrentError=&dDataXY;
#line 377 "JParser.cpp"
			}
			break;
		}
		case RYX:
		{
			match(RYX);
			if ( inputState->guessing==0 ) {
#line 110 "JParser.g"
				rsection = true; zsection = false;CurrentData=&DataYX;CurrentError=&dDataYX;
#line 387 "JParser.cpp"
			}
			break;
		}
		case RYY:
		{
			match(RYY);
			if ( inputState->guessing==0 ) {
#line 111 "JParser.g"
				rsection = true; zsection = false;CurrentData=&DataYY;CurrentError=&dDataYY;
#line 397 "JParser.cpp"
			}
			break;
		}
		case TZX:
		{
			match(TZX);
			if ( inputState->guessing==0 ) {
#line 112 "JParser.g"
				tsection = true; rsection = false; zsection = false; CurrentData=&DataZX;CurrentError=&dDataZX;CurrentCoh=&Rz;
#line 407 "JParser.cpp"
			}
			break;
		}
		case TZY:
		{
			match(TZY);
			if ( inputState->guessing==0 ) {
#line 113 "JParser.g"
				tsection = true; rsection = false; zsection = false; CurrentData=&DataZY;CurrentError=&dDataZY;CurrentCoh=&Rz;
#line 417 "JParser.cpp"
			}
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		switch ( LA(1)) {
		case SI:
		{
			match(SI);
			if ( inputState->guessing==0 ) {
#line 114 "JParser.g"
				convfactor = 1./(1000. * gplib::mu);
#line 435 "JParser.cpp"
			}
			break;
		}
		case FIELD:
		{
			match(FIELD);
			if ( inputState->guessing==0 ) {
#line 114 "JParser.g"
				convfactor = 1;
#line 445 "JParser.cpp"
			}
			break;
		}
		case NEWLINE:
		case UNITS:
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{
		switch ( LA(1)) {
		case UNITS:
		{
			match(UNITS);
			break;
		}
		case NEWLINE:
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(NEWLINE);
		size=datavalue();
		if ( inputState->guessing==0 ) {
#line 115 "JParser.g"
			
							if (CurrentData != NULL )
							{
								CurrentData->assign(size,0);
								CurrentError->assign(size,0);
								if (frequency.empty())
								{
									frequency.assign(size,-1);
									Rx.assign(size,0);
									Ry.assign(size,0);
									Rz.assign(size,0);
								}
							}
							
#line 495 "JParser.cpp"
		}
		match(NEWLINE);
		{ // ( ... )+
		int _cnt20=0;
		for (;;) {
			if (((LA(1) == UNDEF || LA(1) == ENTRY) && (LA(2) == UNDEF || LA(2) == ENTRY) && (LA(3) == UNDEF || LA(3) == ENTRY) && (LA(4) == UNDEF || LA(4) == ENTRY) && (LA(5) == UNDEF || LA(5) == ENTRY) && (LA(6) == NEWLINE || LA(6) == UNDEF || LA(6) == ENTRY) && (_tokenSet_11.member(LA(7))) && (_tokenSet_12.member(LA(8))) && (_tokenSet_13.member(LA(9))) && (_tokenSet_14.member(LA(10))))&&(zsection)) {
				zdata();
			}
			else if ((LA(1) == UNDEF || LA(1) == ENTRY) && (LA(2) == UNDEF || LA(2) == ENTRY) && (LA(3) == UNDEF || LA(3) == ENTRY) && (LA(4) == UNDEF || LA(4) == ENTRY) && (LA(5) == UNDEF || LA(5) == ENTRY) && (LA(6) == UNDEF || LA(6) == ENTRY) && (LA(7) == UNDEF || LA(7) == ENTRY) && (LA(8) == UNDEF || LA(8) == ENTRY) && (LA(9) == UNDEF || LA(9) == ENTRY) && (LA(10) == NEWLINE)) {
				{
				if (!(rsection))
					throw antlr::SemanticException("rsection");
				rdata();
				}
			}
			else if ((LA(1) == UNDEF || LA(1) == ENTRY) && (LA(2) == UNDEF || LA(2) == ENTRY) && (LA(3) == UNDEF || LA(3) == ENTRY) && (LA(4) == UNDEF || LA(4) == ENTRY) && (LA(5) == UNDEF || LA(5) == ENTRY) && (LA(6) == NEWLINE || LA(6) == UNDEF || LA(6) == ENTRY) && (_tokenSet_11.member(LA(7))) && (_tokenSet_12.member(LA(8))) && (_tokenSet_13.member(LA(9))) && (_tokenSet_14.member(LA(10)))) {
				{
				if (!(tsection))
					throw antlr::SemanticException("tsection");
				tdata();
				}
			}
			else {
				if ( _cnt20>=1 ) { goto _loop20; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt20++;
		}
		_loop20:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_15);
		} else {
			throw;
		}
	}
}

void JParser::zdata() {
#line 134 "JParser.g"
	double r1,r2,r3,r4,r5,r6=0;
#line 540 "JParser.cpp"
	
	try {      // for error handling
		r1=datavalue();
		r2=datavalue();
		r3=datavalue();
		r4=datavalue();
		r5=datavalue();
		{
		switch ( LA(1)) {
		case UNDEF:
		case ENTRY:
		{
			r6=datavalue();
			break;
		}
		case NEWLINE:
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 137 "JParser.g"
				if (r1 > 0)
						frequency.at(currindex) = 1./r1;
					else
						if (frequency.at(currindex) != 0)
							frequency.at(currindex) = fabs(r1);
					CurrentData->at(currindex) = convfactor * (r2 + gplib::I * r3);
					CurrentError->at(currindex) = convfactor * r4;
					CurrentCoh->at(currindex) = r6;
					if (r2 == -1000000000 || r3 == -1000000000 || r2 == -999)
						frequency.at(currindex) = 0;
					currindex++;
					zassigned = true;
#line 581 "JParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_16);
		} else {
			throw;
		}
	}
}

void JParser::rdata() {
#line 151 "JParser.g"
	double r1,r2,r3,r4,r5,r6,r7,r8,r9=0;
#line 597 "JParser.cpp"
	
	try {      // for error handling
		r1=datavalue();
		r2=datavalue();
		r3=datavalue();
		r4=datavalue();
		r5=datavalue();
		r6=datavalue();
		r7=datavalue();
		r8=datavalue();
		r9=datavalue();
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 155 "JParser.g"
			if (r1 > 0)
						frequency.at(currindex) = 1./r1;
					else
						frequency.at(currindex) = r1;
						
					double factor = sqrt(2 * gplib::PI * frequency.at(currindex)/gplib::mu);
					CurrentData->at(currindex) = factor * r2 *(cos(r3/180.0*gplib::PI)+ gplib::I*sin(r3/180.0*gplib::PI));
					CurrentError->at(currindex) = sqrt(pow(factor *cos(r3/180.0*gplib::PI)+ sin(r3/180.0*gplib::PI),2) 
					                + pow(factor*abs(r2)/180.0* gplib::PI,2) * (pow(cos(r3/180.0*gplib::PI),2)+ pow(sin(r3/180.0*gplib::PI),2)) );
				  	currindex++; 
				  	rassigned = true;
#line 623 "JParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_16);
		} else {
			throw;
		}
	}
}

void JParser::tdata() {
#line 170 "JParser.g"
	double r1,r2,r3,r4,r5,r6;
#line 639 "JParser.cpp"
	
	try {      // for error handling
		r1=datavalue();
		r2=datavalue();
		r3=datavalue();
		r4=datavalue();
		r5=datavalue();
		{
		switch ( LA(1)) {
		case UNDEF:
		case ENTRY:
		{
			r6=datavalue();
			break;
		}
		case NEWLINE:
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(NEWLINE);
		if ( inputState->guessing==0 ) {
#line 173 "JParser.g"
				if (r1 > 0)
						frequency.at(currindex) = 1./r1;
					else
						frequency.at(currindex) = r1;
						
					CurrentData->at(currindex) = r2 + gplib::I * r3;
					CurrentError->at(currindex) = r4;
					currindex++;
					tassigned = true;
#line 677 "JParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_16);
		} else {
			throw;
		}
	}
}

void JParser::initializeASTFactory( antlr::ASTFactory& )
{
}
const char* JParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"NEWLINE",
	"COMMENT",
	"AZIMUTH",
	"LATITUDE",
	"LONGITUDE",
	"ELEVATION",
	"STATION",
	"EQUAL",
	"ZXX",
	"ZXY",
	"ZYX",
	"ZYY",
	"RXX",
	"RXY",
	"RYX",
	"RYY",
	"TZX",
	"TZY",
	"SI",
	"FIELD",
	"UNITS",
	"UNDEF",
	"ENTRY",
	"PLUS",
	"MINUS",
	"WS",
	"DIGIT",
	"CHAR",
	"OTHER",
	0
};

const unsigned long JParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const antlr::BitSet JParser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long JParser::_tokenSet_1_data_[] = { 67110848UL, 0UL, 0UL, 0UL };
// AZIMUTH LATITUDE LONGITUDE ELEVATION STATION ENTRY 
const antlr::BitSet JParser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long JParser::_tokenSet_2_data_[] = { 104853520UL, 0UL, 0UL, 0UL };
// NEWLINE ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_2(_tokenSet_2_data_,4);
const unsigned long JParser::_tokenSet_3_data_[] = { 96470992UL, 0UL, 0UL, 0UL };
// NEWLINE AZIMUTH LATITUDE LONGITUDE ELEVATION STATION SI FIELD UNITS 
// ENTRY 
const antlr::BitSet JParser::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long JParser::_tokenSet_4_data_[] = { 117444560UL, 0UL, 0UL, 0UL };
// NEWLINE AZIMUTH LATITUDE LONGITUDE ELEVATION STATION EQUAL UNITS UNDEF 
// ENTRY 
const antlr::BitSet JParser::_tokenSet_4(_tokenSet_4_data_,4);
const unsigned long JParser::_tokenSet_5_data_[] = { 104855568UL, 0UL, 0UL, 0UL };
// NEWLINE EQUAL ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_5(_tokenSet_5_data_,4);
const unsigned long JParser::_tokenSet_6_data_[] = { 134215632UL, 0UL, 0UL, 0UL };
// NEWLINE AZIMUTH LATITUDE LONGITUDE ELEVATION STATION ZXX ZXY ZYX ZYY 
// RXX RXY RYX RYY TZX TZY SI FIELD UNITS UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_6(_tokenSet_6_data_,4);
const unsigned long JParser::_tokenSet_7_data_[] = { 130027472UL, 0UL, 0UL, 0UL };
// NEWLINE AZIMUTH LATITUDE LONGITUDE ELEVATION STATION EQUAL SI FIELD 
// UNITS UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_7(_tokenSet_7_data_,4);
const unsigned long JParser::_tokenSet_8_data_[] = { 67108864UL, 0UL, 0UL, 0UL };
// ENTRY 
const antlr::BitSet JParser::_tokenSet_8(_tokenSet_8_data_,4);
const unsigned long JParser::_tokenSet_9_data_[] = { 16UL, 0UL, 0UL, 0UL };
// NEWLINE 
const antlr::BitSet JParser::_tokenSet_9(_tokenSet_9_data_,4);
const unsigned long JParser::_tokenSet_10_data_[] = { 100663312UL, 0UL, 0UL, 0UL };
// NEWLINE UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_10(_tokenSet_10_data_,4);
const unsigned long JParser::_tokenSet_11_data_[] = { 104853522UL, 0UL, 0UL, 0UL };
// EOF NEWLINE ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_11(_tokenSet_11_data_,4);
const unsigned long JParser::_tokenSet_12_data_[] = { 134213650UL, 0UL, 0UL, 0UL };
// EOF NEWLINE ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY SI FIELD UNITS UNDEF 
// ENTRY 
const antlr::BitSet JParser::_tokenSet_12(_tokenSet_12_data_,4);
const unsigned long JParser::_tokenSet_13_data_[] = { 130023442UL, 0UL, 0UL, 0UL };
// EOF NEWLINE SI FIELD UNITS UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_13(_tokenSet_13_data_,4);
const unsigned long JParser::_tokenSet_14_data_[] = { 117440530UL, 0UL, 0UL, 0UL };
// EOF NEWLINE UNITS UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_14(_tokenSet_14_data_,4);
const unsigned long JParser::_tokenSet_15_data_[] = { 4190210UL, 0UL, 0UL, 0UL };
// EOF ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY 
const antlr::BitSet JParser::_tokenSet_15(_tokenSet_15_data_,4);
const unsigned long JParser::_tokenSet_16_data_[] = { 104853506UL, 0UL, 0UL, 0UL };
// EOF ZXX ZXY ZYX ZYY RXX RXY RYX RYY TZX TZY UNDEF ENTRY 
const antlr::BitSet JParser::_tokenSet_16(_tokenSet_16_data_,4);


