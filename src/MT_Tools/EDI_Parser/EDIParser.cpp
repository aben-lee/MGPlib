/* $ANTLR 2.7.7 (20110618): "EdiParser2.g" -> "EDIParser.cpp"$ */
#include "EDIParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "EdiParser2.g"
#line 8 "EDIParser.cpp"
EDIParser::EDIParser(antlr::TokenBuffer& tokenBuf, int k)
: antlr::LLkParser(tokenBuf,k)
{
}

EDIParser::EDIParser(antlr::TokenBuffer& tokenBuf)
: antlr::LLkParser(tokenBuf,10)
{
}

EDIParser::EDIParser(antlr::TokenStream& lexer, int k)
: antlr::LLkParser(lexer,k)
{
}

EDIParser::EDIParser(antlr::TokenStream& lexer)
: antlr::LLkParser(lexer,10)
{
}

EDIParser::EDIParser(const antlr::ParserSharedInputState& state)
: antlr::LLkParser(state,10)
{
}

void EDIParser::option() {
	antlr::RefToken  a = antlr::nullToken;
#line 55 "EdiParser2.g"
	double currvalue; bool isint = false; double *currdouble;
#line 38 "EDIParser.cpp"
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case LITERAL_NFREQ:
		{
			match(LITERAL_NFREQ);
			if ( inputState->guessing==0 ) {
#line 57 "EdiParser2.g"
				isint = true; currdouble = NULL;
#line 49 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_LATITUDE:
		{
			match(LITERAL_LATITUDE);
			if ( inputState->guessing==0 ) {
#line 58 "EdiParser2.g"
				isint = false; currdouble = &latitude;
#line 59 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_LONGITUDE:
		{
			match(LITERAL_LONGITUDE);
			if ( inputState->guessing==0 ) {
#line 59 "EdiParser2.g"
				isint = false; currdouble = &longitude;
#line 69 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_AZIMUTH:
		{
			match(LITERAL_AZIMUTH);
			if ( inputState->guessing==0 ) {
#line 60 "EdiParser2.g"
				isint = false; currdouble = &azimuth;
#line 79 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_ELEVATION:
		{
			match(LITERAL_ELEVATION);
			if ( inputState->guessing==0 ) {
#line 61 "EdiParser2.g"
				isint = false; currdouble = &elevation;
#line 89 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_REFLONG:
		{
			match(LITERAL_REFLONG);
			if ( inputState->guessing==0 ) {
#line 62 "EdiParser2.g"
				isint = false; currdouble = &longitude;
#line 99 "EDIParser.cpp"
			}
			break;
		}
		case LITERAL_REFLAT:
		{
			match(LITERAL_REFLAT);
			if ( inputState->guessing==0 ) {
#line 63 "EdiParser2.g"
				isint = false; currdouble = &latitude;
#line 109 "EDIParser.cpp"
			}
			break;
		}
		case STRING:
		{
			a = LT(1);
			match(STRING);
			if ( inputState->guessing==0 ) {
#line 64 "EdiParser2.g"
				currdouble = NULL; isint = false;
#line 120 "EDIParser.cpp"
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
		switch ( LA(1)) {
		case DATE:
		{
			match(DATE);
			break;
		}
		case STRING:
		{
			match(STRING);
			break;
		}
		default:
			bool synPredMatched7 = false;
			if (((LA(1) == NUMBER) && (LA(2) == COLON) && (LA(3) == NUMBER) && (LA(4) == COLON) && (LA(5) == NUMBER) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10))))) {
				int _m7 = mark();
				synPredMatched7 = true;
				inputState->guessing++;
				try {
					{
					lat_long();
					}
				}
				catch (antlr::RecognitionException& pe) {
					synPredMatched7 = false;
				}
				rewind(_m7);
				inputState->guessing--;
			}
			if ( synPredMatched7 ) {
				currvalue=lat_long();
			}
			else {
				bool synPredMatched9 = false;
				if (((LA(1) == NUMBER) && (_tokenSet_0.member(LA(2))) && (_tokenSet_0.member(LA(3))) && (_tokenSet_0.member(LA(4))) && (_tokenSet_0.member(LA(5))) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10))))) {
					int _m9 = mark();
					synPredMatched9 = true;
					inputState->guessing++;
					try {
						{
						match(NUMBER);
						}
					}
					catch (antlr::RecognitionException& pe) {
						synPredMatched9 = false;
					}
					rewind(_m9);
					inputState->guessing--;
				}
				if ( synPredMatched9 ) {
					currvalue=datavalue();
				}
		else {
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}}
		}
		if ( inputState->guessing==0 ) {
#line 70 "EdiParser2.g"
			if (isint)
						{	nfreq = int(currvalue);}
					  else
					  	if (currdouble != NULL) *currdouble = currvalue;
#line 194 "EDIParser.cpp"
		}
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

double  EDIParser::lat_long() {
#line 210 "EdiParser2.g"
	double r;
#line 210 "EDIParser.cpp"
#line 210 "EdiParser2.g"
	double v1=0; double v2=0; double v3=0;
#line 213 "EDIParser.cpp"
	
	try {      // for error handling
		v1=datavalue();
		match(COLON);
		v2=datavalue();
		match(COLON);
		v3=datavalue();
		if ( inputState->guessing==0 ) {
#line 213 "EdiParser2.g"
			
					if (v1 > 0)
						r = v1 + v2/60. + v3/3600.;
					else
						r = v1 - v2/60. - v3/3600.;
				
#line 229 "EDIParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
	return r;
}

double  EDIParser::datavalue() {
#line 222 "EdiParser2.g"
	double r;
#line 246 "EDIParser.cpp"
	antlr::RefToken  currvalue = antlr::nullToken;
	
	try {      // for error handling
		currvalue = LT(1);
		match(NUMBER);
		if ( inputState->guessing==0 ) {
#line 224 "EdiParser2.g"
			gplib::convert(currvalue->getText(),r);
#line 255 "EDIParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_0);
		} else {
			throw;
		}
	}
	return r;
}

void EDIParser::option_list() {
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if (((LA(1) >= LITERAL_NFREQ && LA(1) <= STRING)) && (LA(2) == EQUAL) && (LA(3) == STRING || LA(3) == DATE || LA(3) == NUMBER) && (_tokenSet_0.member(LA(4))) && (_tokenSet_0.member(LA(5))) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10)))) {
				option();
			}
			else {
				goto _loop12;
			}
			
		}
		_loop12:;
		} // ( ... )*
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

void EDIParser::head_block() {
	
	try {      // for error handling
		match(HEAD);
		option_list();
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

void EDIParser::info_block() {
	
	try {      // for error handling
		match(16);
		option_list();
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

void EDIParser::info_text() {
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((_tokenSet_2.member(LA(1)))) {
				matchNot(SPECIAL);
			}
			else {
				goto _loop17;
			}
			
		}
		_loop17:;
		} // ( ... )*
		match(SPECIAL);
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_3);
		} else {
			throw;
		}
	}
}

void EDIParser::emeas_block() {
	
	try {      // for error handling
		match(18);
		option_list();
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		} else {
			throw;
		}
	}
}

void EDIParser::hmeas_block() {
	
	try {      // for error handling
		match(19);
		option_list();
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_4);
		} else {
			throw;
		}
	}
}

void EDIParser::def_meas_section() {
	
	try {      // for error handling
		match(EQUAL);
		match(LITERAL_DEFINEMEAS);
		option_list();
		{ // ( ... )+
		int _cnt22=0;
		for (;;) {
			switch ( LA(1)) {
			case 18:
			{
				emeas_block();
				break;
			}
			case 19:
			{
				hmeas_block();
				break;
			}
			default:
			{
				if ( _cnt22>=1 ) { goto _loop22; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			}
			_cnt22++;
		}
		_loop22:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void EDIParser::spectrasect_block() {
	
	try {      // for error handling
		match(SPECIAL);
		match(EQUAL);
		match(LITERAL_SPECTRASET);
		option_list();
		{
		switch ( LA(1)) {
		case 22:
		{
			match(22);
			match(INT);
			break;
		}
		case NUMBER:
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		{ // ( ... )+
		int _cnt26=0;
		for (;;) {
			if ((LA(1) == NUMBER)) {
				match(NUMBER);
			}
			else {
				if ( _cnt26>=1 ) { goto _loop26; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt26++;
		}
		_loop26:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void EDIParser::spectra_block() {
	
	try {      // for error handling
		match(SPECIAL);
		match(LITERAL_SPECTRA);
		option_list();
		match(25);
		{ // ( ... )+
		int _cnt29=0;
		for (;;) {
			if ((LA(1) == NUMBER)) {
				datavalue();
			}
			else {
				if ( _cnt29>=1 ) { goto _loop29; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt29++;
		}
		_loop29:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void EDIParser::spectra_section() {
	
	try {      // for error handling
		spectrasect_block();
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == SPECIAL) && (LA(2) == LITERAL_SPECTRA)) {
				spectra_block();
			}
			else {
				goto _loop32;
			}
			
		}
		_loop32:;
		} // ( ... )*
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void EDIParser::mtsect_block() {
	
	try {      // for error handling
		match(SPECIAL);
		match(EQUAL);
		match(LITERAL_MTSECT);
		option_list();
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_6);
		} else {
			throw;
		}
	}
}

void EDIParser::mt_complex_data_block() {
#line 118 "EdiParser2.g"
	double ldnfreq; int lnfreq; double currvalue; int currindex = 0; gplib::pcompdata currvect;
		std::complex<double> localconv;
#line 557 "EDIParser.cpp"
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case 27:
		{
			match(27);
			if ( inputState->guessing==0 ) {
#line 122 "EdiParser2.g"
				currvect = &DataXX; localconv = convfactor;
#line 568 "EDIParser.cpp"
			}
			break;
		}
		case 28:
		{
			match(28);
			if ( inputState->guessing==0 ) {
#line 123 "EdiParser2.g"
				currvect = &DataXX; localconv = gplib::I * convfactor;
#line 578 "EDIParser.cpp"
			}
			break;
		}
		case 29:
		{
			match(29);
			if ( inputState->guessing==0 ) {
#line 124 "EdiParser2.g"
				currvect = &DataXY; localconv = convfactor;
#line 588 "EDIParser.cpp"
			}
			break;
		}
		case 30:
		{
			match(30);
			if ( inputState->guessing==0 ) {
#line 125 "EdiParser2.g"
				currvect = &DataXY; localconv = gplib::I * convfactor;
#line 598 "EDIParser.cpp"
			}
			break;
		}
		case 31:
		{
			match(31);
			if ( inputState->guessing==0 ) {
#line 126 "EdiParser2.g"
				currvect = &DataYX; localconv = convfactor;
#line 608 "EDIParser.cpp"
			}
			break;
		}
		case 32:
		{
			match(32);
			if ( inputState->guessing==0 ) {
#line 127 "EdiParser2.g"
				currvect = &DataYX; localconv = gplib::I * convfactor;
#line 618 "EDIParser.cpp"
			}
			break;
		}
		case 33:
		{
			match(33);
			if ( inputState->guessing==0 ) {
#line 128 "EdiParser2.g"
				currvect = &DataYY; localconv = convfactor;
#line 628 "EDIParser.cpp"
			}
			break;
		}
		case 34:
		{
			match(34);
			if ( inputState->guessing==0 ) {
#line 129 "EdiParser2.g"
				currvect = &DataYY; localconv = gplib::I * convfactor;
#line 638 "EDIParser.cpp"
			}
			break;
		}
		case 35:
		{
			match(35);
			if ( inputState->guessing==0 ) {
#line 130 "EdiParser2.g"
				currvect = &DataZX; localconv = convfactor;
#line 648 "EDIParser.cpp"
			}
			break;
		}
		case 36:
		{
			match(36);
			if ( inputState->guessing==0 ) {
#line 131 "EdiParser2.g"
				currvect = &DataZX; localconv = gplib::I * convfactor;
#line 658 "EDIParser.cpp"
			}
			break;
		}
		case 37:
		{
			match(37);
			if ( inputState->guessing==0 ) {
#line 132 "EdiParser2.g"
				currvect = &DataZY; localconv = convfactor;
#line 668 "EDIParser.cpp"
			}
			break;
		}
		case 38:
		{
			match(38);
			if ( inputState->guessing==0 ) {
#line 133 "EdiParser2.g"
				currvect = &DataZY; localconv = gplib::I * convfactor;
#line 678 "EDIParser.cpp"
			}
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 134 "EdiParser2.g"
			if (currvect->empty()) currvect->assign(nfreq,0);
#line 691 "EDIParser.cpp"
		}
		option_list();
		match(SLASH);
		match(SLASH);
		ldnfreq=datavalue();
		if ( inputState->guessing==0 ) {
#line 135 "EdiParser2.g"
			lnfreq = int(ldnfreq);
#line 700 "EDIParser.cpp"
		}
		if (!(lnfreq == nfreq))
			throw antlr::SemanticException("lnfreq == nfreq");
		{ // ( ... )+
		int _cnt37=0;
		for (;;) {
			if ((LA(1) == NUMBER)) {
				currvalue=datavalue();
				if ( inputState->guessing==0 ) {
#line 138 "EdiParser2.g"
					currvect->at(currindex) += localconv * currvalue; currindex++;
#line 712 "EDIParser.cpp"
				}
			}
			else {
				if ( _cnt37>=1 ) { goto _loop37; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt37++;
		}
		_loop37:;
		}  // ( ... )+
		if ( inputState->guessing==0 ) {
#line 139 "EdiParser2.g"
#line 725 "EDIParser.cpp"
		}
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void EDIParser::mt_real_data_block() {
	antlr::RefToken  k = antlr::nullToken;
#line 141 "EdiParser2.g"
	double ldnfreq; int lnfreq; double currvalue; int currindex = 0; gplib::prealdata currvect;
#line 742 "EDIParser.cpp"
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case 40:
		{
			match(40);
			if ( inputState->guessing==0 ) {
#line 144 "EdiParser2.g"
				currvect = &frequency;
#line 753 "EDIParser.cpp"
			}
			break;
		}
		case 41:
		{
			match(41);
			if ( inputState->guessing==0 ) {
#line 145 "EdiParser2.g"
				currvect = &dDataXX;
#line 763 "EDIParser.cpp"
			}
			break;
		}
		case 42:
		{
			match(42);
			if ( inputState->guessing==0 ) {
#line 146 "EdiParser2.g"
				currvect = &dDataXX;
#line 773 "EDIParser.cpp"
			}
			break;
		}
		case 43:
		{
			match(43);
			if ( inputState->guessing==0 ) {
#line 147 "EdiParser2.g"
				currvect = &dDataXX;
#line 783 "EDIParser.cpp"
			}
			break;
		}
		case 44:
		{
			match(44);
			if ( inputState->guessing==0 ) {
#line 148 "EdiParser2.g"
				currvect = &dDataXY;
#line 793 "EDIParser.cpp"
			}
			break;
		}
		case 45:
		{
			match(45);
			if ( inputState->guessing==0 ) {
#line 149 "EdiParser2.g"
				currvect = &dDataXY;
#line 803 "EDIParser.cpp"
			}
			break;
		}
		case 46:
		{
			match(46);
			if ( inputState->guessing==0 ) {
#line 150 "EdiParser2.g"
				currvect = &dDataXY;
#line 813 "EDIParser.cpp"
			}
			break;
		}
		case 47:
		{
			match(47);
			if ( inputState->guessing==0 ) {
#line 151 "EdiParser2.g"
				currvect = &dDataYX;
#line 823 "EDIParser.cpp"
			}
			break;
		}
		case 48:
		{
			match(48);
			if ( inputState->guessing==0 ) {
#line 152 "EdiParser2.g"
				currvect = &dDataYX;
#line 833 "EDIParser.cpp"
			}
			break;
		}
		case 49:
		{
			match(49);
			if ( inputState->guessing==0 ) {
#line 153 "EdiParser2.g"
				currvect = &dDataYX;
#line 843 "EDIParser.cpp"
			}
			break;
		}
		case 50:
		{
			match(50);
			if ( inputState->guessing==0 ) {
#line 154 "EdiParser2.g"
				currvect = &dDataYY;
#line 853 "EDIParser.cpp"
			}
			break;
		}
		case 51:
		{
			match(51);
			if ( inputState->guessing==0 ) {
#line 155 "EdiParser2.g"
				currvect = &dDataYY;
#line 863 "EDIParser.cpp"
			}
			break;
		}
		case 52:
		{
			match(52);
			if ( inputState->guessing==0 ) {
#line 156 "EdiParser2.g"
				currvect = &dDataYY;
#line 873 "EDIParser.cpp"
			}
			break;
		}
		case 53:
		{
			match(53);
			if ( inputState->guessing==0 ) {
#line 157 "EdiParser2.g"
				currvect = &dDataZX;
#line 883 "EDIParser.cpp"
			}
			break;
		}
		case 54:
		{
			match(54);
			if ( inputState->guessing==0 ) {
#line 158 "EdiParser2.g"
				currvect = &dDataZY;
#line 893 "EDIParser.cpp"
			}
			break;
		}
		case 55:
		{
			match(55);
			if ( inputState->guessing==0 ) {
#line 159 "EdiParser2.g"
				currvect = &rotangles;
#line 903 "EDIParser.cpp"
			}
			break;
		}
		case KEYWORD:
		{
			k = LT(1);
			match(KEYWORD);
			if ( inputState->guessing==0 ) {
#line 160 "EdiParser2.g"
				currvect = NULL;
#line 914 "EDIParser.cpp"
			}
			break;
		}
		default:
		{
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
		if ( inputState->guessing==0 ) {
#line 161 "EdiParser2.g"
			if (currvect != NULL && currvect->empty()) currvect->assign(nfreq,0);
#line 927 "EDIParser.cpp"
		}
		option_list();
		match(SLASH);
		match(SLASH);
		ldnfreq=datavalue();
		if ( inputState->guessing==0 ) {
#line 162 "EdiParser2.g"
			lnfreq = int(ldnfreq);
#line 936 "EDIParser.cpp"
		}
		{ // ( ... )+
		int _cnt41=0;
		for (;;) {
			if ((LA(1) == NUMBER)) {
				currvalue=datavalue();
				if ( inputState->guessing==0 ) {
#line 164 "EdiParser2.g"
					if (currvect != NULL)
								   {
									if ((currvect != &frequency) && (currvect != &rotangles)) 
										currvect->at(currindex) = sqrt(currvalue); 
									else
										currvect->at(currindex) = currvalue;
									}
									currindex++;
#line 953 "EDIParser.cpp"
				}
			}
			else {
				if ( _cnt41>=1 ) { goto _loop41; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt41++;
		}
		_loop41:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_7);
		} else {
			throw;
		}
	}
}

void EDIParser::mt_section() {
	
	try {      // for error handling
		mtsect_block();
		{ // ( ... )+
		int _cnt46=0;
		for (;;) {
			if ((_tokenSet_6.member(LA(1)))) {
				{
				switch ( LA(1)) {
				case COMMENT:
				{
					match(COMMENT);
					break;
				}
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				case 40:
				case 41:
				case 42:
				case 43:
				case 44:
				case 45:
				case 46:
				case 47:
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case KEYWORD:
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
				case 40:
				case 41:
				case 42:
				case 43:
				case 44:
				case 45:
				case 46:
				case 47:
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case KEYWORD:
				{
					mt_real_data_block();
					break;
				}
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				{
					mt_complex_data_block();
					break;
				}
				default:
				{
					throw antlr::NoViableAltException(LT(1), getFilename());
				}
				}
				}
			}
			else {
				if ( _cnt46>=1 ) { goto _loop46; } else {throw antlr::NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt46++;
		}
		_loop46:;
		}  // ( ... )+
	}
	catch (antlr::RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}

void EDIParser::end_block() {
	
	try {      // for error handling
		match(58);
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

void EDIParser::edi_file() {
#line 191 "EdiParser2.g"
	
		zassigned = false;
		rassigned = false;
		tassigned = false;
		latitude = 0;
		longitude =0;
		elevation = 0;
		azimuth = 0;
		nfreq = 0;
		convfactor = 1.;
		name = "default";
	
#line 1122 "EDIParser.cpp"
	
	try {      // for error handling
		head_block();
		{
		if ((LA(1) == 16) && ((LA(2) >= LITERAL_NFREQ && LA(2) <= REAL)) && ((LA(3) >= LITERAL_NFREQ && LA(3) <= REAL)) && ((LA(4) >= LITERAL_NFREQ && LA(4) <= REAL)) && (_tokenSet_0.member(LA(5))) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10)))) {
			info_block();
		}
		else if (((LA(1) >= LITERAL_NFREQ && LA(1) <= REAL)) && ((LA(2) >= LITERAL_NFREQ && LA(2) <= REAL)) && ((LA(3) >= LITERAL_NFREQ && LA(3) <= REAL)) && (_tokenSet_0.member(LA(4))) && (_tokenSet_0.member(LA(5))) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10)))) {
		}
		else {
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		
		}
		{
		if (((LA(1) >= LITERAL_NFREQ && LA(1) <= REAL)) && ((LA(2) >= LITERAL_NFREQ && LA(2) <= REAL)) && ((LA(3) >= LITERAL_NFREQ && LA(3) <= REAL)) && ((LA(4) >= LITERAL_NFREQ && LA(4) <= REAL)) && (_tokenSet_0.member(LA(5))) && (_tokenSet_0.member(LA(6))) && (_tokenSet_0.member(LA(7))) && (_tokenSet_0.member(LA(8))) && (_tokenSet_0.member(LA(9))) && (_tokenSet_0.member(LA(10)))) {
			info_text();
		}
		else if ((LA(1) == EQUAL) && (LA(2) == LITERAL_DEFINEMEAS) && (_tokenSet_9.member(LA(3))) && (_tokenSet_10.member(LA(4))) && (_tokenSet_11.member(LA(5))) && (_tokenSet_12.member(LA(6))) && (_tokenSet_13.member(LA(7))) && (_tokenSet_14.member(LA(8))) && (_tokenSet_15.member(LA(9))) && (_tokenSet_16.member(LA(10)))) {
		}
		else {
			throw antlr::NoViableAltException(LT(1), getFilename());
		}
		
		}
		def_meas_section();
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == SPECIAL) && (LA(2) == EQUAL) && (LA(3) == LITERAL_SPECTRASET)) {
				spectra_section();
			}
			else if ((LA(1) == SPECIAL) && (LA(2) == EQUAL) && (LA(3) == LITERAL_MTSECT)) {
				mt_section();
			}
			else {
				goto _loop52;
			}
			
		}
		_loop52:;
		} // ( ... )*
		{
		switch ( LA(1)) {
		case 58:
		{
			end_block();
			break;
		}
		case antlr::Token::EOF_TYPE:
		{
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
			recover(ex,_tokenSet_8);
		} else {
			throw;
		}
	}
}

void EDIParser::initializeASTFactory( antlr::ASTFactory& )
{
}
const char* EDIParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\"NFREQ\"",
	"\"LATITUDE\"",
	"\"LONGITUDE\"",
	"\"AZIMUTH\"",
	"\"ELEVATION\"",
	"\"REFLONG\"",
	"\"REFLAT\"",
	"STRING",
	"EQUAL",
	"DATE",
	"NUMBER",
	"HEAD",
	"\">INFO\"",
	"SPECIAL",
	"\">EMEAS\"",
	"\">HMEAS\"",
	"\"DEFINEMEAS\"",
	"\"SPECTRASET\"",
	"\"//\"",
	"INT",
	"\"SPECTRA\"",
	"\";\"",
	"\"MTSECT\"",
	"\">ZXXR\"",
	"\">ZXXI\"",
	"\">ZXYR\"",
	"\">ZXYI\"",
	"\">ZYXR\"",
	"\">ZYXI\"",
	"\">ZYYR\"",
	"\">ZYYI\"",
	"\">TXR.EXP\"",
	"\">TXI.EXP\"",
	"\">TYR.EXP\"",
	"\">TYI.EXP\"",
	"SLASH",
	"\">FREQ\"",
	"\">ZXXR.VAR\"",
	"\">ZXXI.VAR\"",
	"\">ZXX.VAR\"",
	"\">ZXYR.VAR\"",
	"\">ZXYI.VAR\"",
	"\">ZXY.VAR\"",
	"\">ZYXR.VAR\"",
	"\">ZYXI.VAR\"",
	"\">ZYX.VAR\"",
	"\">ZYYR.VAR\"",
	"\">ZYYI.VAR\"",
	"\">ZYY.VAR\"",
	"\">TXVAR.EXP\"",
	"\">TYVAR.EXP\"",
	"\">ZROT\"",
	"KEYWORD",
	"COMMENT",
	"\">END\"",
	"COLON",
	"WS",
	"EXKL",
	"DIGIT",
	"LETTER",
	"OTHER",
	"NONUMBER",
	"LEGAL_CHAR",
	"SIGN",
	"REAL",
	0
};

const unsigned long EDIParser::_tokenSet_0_data_[] = { 4294967282UL, 4294967295UL, 31UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER HEAD ">INFO" SPECIAL ">EMEAS" ">HMEAS" "DEFINEMEAS" 
// "SPECTRASET" "//" INT "SPECTRA" ";" "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" 
// ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" 
// ">TYI.EXP" SLASH ">FREQ" ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" 
// ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" 
// ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT 
// ">END" COLON WS EXKL DIGIT LETTER OTHER NONUMBER LEGAL_CHAR SIGN REAL 
const antlr::BitSet EDIParser::_tokenSet_0(_tokenSet_0_data_,8);
const unsigned long EDIParser::_tokenSet_1_data_[] = { 4294967280UL, 4294967295UL, 31UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER HEAD ">INFO" SPECIAL ">EMEAS" ">HMEAS" "DEFINEMEAS" 
// "SPECTRASET" "//" INT "SPECTRA" ";" "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" 
// ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" 
// ">TYI.EXP" SLASH ">FREQ" ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" 
// ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" 
// ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT 
// ">END" COLON WS EXKL DIGIT LETTER OTHER NONUMBER LEGAL_CHAR SIGN REAL 
const antlr::BitSet EDIParser::_tokenSet_1(_tokenSet_1_data_,8);
const unsigned long EDIParser::_tokenSet_2_data_[] = { 4294836208UL, 4294967295UL, 31UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER HEAD ">INFO" ">EMEAS" ">HMEAS" "DEFINEMEAS" 
// "SPECTRASET" "//" INT "SPECTRA" ";" "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" 
// ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" 
// ">TYI.EXP" SLASH ">FREQ" ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" 
// ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" 
// ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT 
// ">END" COLON WS EXKL DIGIT LETTER OTHER NONUMBER LEGAL_CHAR SIGN REAL 
const antlr::BitSet EDIParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long EDIParser::_tokenSet_3_data_[] = { 4096UL, 0UL, 0UL, 0UL };
// EQUAL 
const antlr::BitSet EDIParser::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long EDIParser::_tokenSet_4_data_[] = { 917506UL, 67108864UL, 0UL, 0UL };
// EOF SPECIAL ">EMEAS" ">HMEAS" ">END" 
const antlr::BitSet EDIParser::_tokenSet_4(_tokenSet_4_data_,4);
const unsigned long EDIParser::_tokenSet_5_data_[] = { 131074UL, 67108864UL, 0UL, 0UL };
// EOF SPECIAL ">END" 
const antlr::BitSet EDIParser::_tokenSet_5(_tokenSet_5_data_,4);
const unsigned long EDIParser::_tokenSet_6_data_[] = { 4160749568UL, 67108735UL, 0UL, 0UL };
// ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" ">ZYYI" ">TXR.EXP" 
// ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" ">FREQ" ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" 
// ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" 
// ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" 
// KEYWORD COMMENT 
const antlr::BitSet EDIParser::_tokenSet_6(_tokenSet_6_data_,4);
const unsigned long EDIParser::_tokenSet_7_data_[] = { 4160880642UL, 134217599UL, 0UL, 0UL };
// EOF SPECIAL ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" 
// ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" ">FREQ" ">ZXXR.VAR" 
// ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" 
// ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" 
// ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT ">END" 
const antlr::BitSet EDIParser::_tokenSet_7(_tokenSet_7_data_,4);
const unsigned long EDIParser::_tokenSet_8_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const antlr::BitSet EDIParser::_tokenSet_8(_tokenSet_8_data_,4);
const unsigned long EDIParser::_tokenSet_9_data_[] = { 790512UL, 0UL, 0UL, 0UL };
// "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING ">EMEAS" ">HMEAS" 
const antlr::BitSet EDIParser::_tokenSet_9(_tokenSet_9_data_,4);
const unsigned long EDIParser::_tokenSet_10_data_[] = { 925682UL, 67108864UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL SPECIAL ">EMEAS" ">HMEAS" ">END" 
const antlr::BitSet EDIParser::_tokenSet_10(_tokenSet_10_data_,4);
const unsigned long EDIParser::_tokenSet_11_data_[] = { 950258UL, 67108864UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" ">END" 
const antlr::BitSet EDIParser::_tokenSet_11(_tokenSet_11_data_,4);
const unsigned long EDIParser::_tokenSet_12_data_[] = { 70156274UL, 201326592UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" "SPECTRASET" "MTSECT" 
// ">END" COLON 
const antlr::BitSet EDIParser::_tokenSet_12(_tokenSet_12_data_,4);
const unsigned long EDIParser::_tokenSet_13_data_[] = { 4235100146UL, 268435327UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" "SPECTRASET" "//" 
// "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" ">ZYYI" 
// ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" ">FREQ" ">ZXXR.VAR" ">ZXXI.VAR" 
// ">ZXX.VAR" ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" ">ZYXI.VAR" 
// ">ZYX.VAR" ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" ">TYVAR.EXP" 
// ">ZROT" KEYWORD COMMENT ">END" COLON 
const antlr::BitSet EDIParser::_tokenSet_13(_tokenSet_13_data_,4);
const unsigned long EDIParser::_tokenSet_14_data_[] = { 4243488754UL, 268435455UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" "SPECTRASET" "//" 
// INT "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" ">ZYYR" 
// ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" SLASH ">FREQ" ">ZXXR.VAR" 
// ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" ">ZYXR.VAR" 
// ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" ">TXVAR.EXP" 
// ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT ">END" COLON 
const antlr::BitSet EDIParser::_tokenSet_14(_tokenSet_14_data_,4);
const unsigned long EDIParser::_tokenSet_15_data_[] = { 4260265970UL, 268435455UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" "SPECTRASET" "//" 
// INT "SPECTRA" "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" 
// ">ZYYR" ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" SLASH ">FREQ" 
// ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" 
// ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" 
// ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT ">END" COLON 
const antlr::BitSet EDIParser::_tokenSet_15(_tokenSet_15_data_,4);
const unsigned long EDIParser::_tokenSet_16_data_[] = { 4293820402UL, 268435455UL, 0UL, 0UL };
// EOF "NFREQ" "LATITUDE" "LONGITUDE" "AZIMUTH" "ELEVATION" "REFLONG" "REFLAT" 
// STRING EQUAL DATE NUMBER SPECIAL ">EMEAS" ">HMEAS" "SPECTRASET" "//" 
// INT "SPECTRA" ";" "MTSECT" ">ZXXR" ">ZXXI" ">ZXYR" ">ZXYI" ">ZYXR" ">ZYXI" 
// ">ZYYR" ">ZYYI" ">TXR.EXP" ">TXI.EXP" ">TYR.EXP" ">TYI.EXP" SLASH ">FREQ" 
// ">ZXXR.VAR" ">ZXXI.VAR" ">ZXX.VAR" ">ZXYR.VAR" ">ZXYI.VAR" ">ZXY.VAR" 
// ">ZYXR.VAR" ">ZYXI.VAR" ">ZYX.VAR" ">ZYYR.VAR" ">ZYYI.VAR" ">ZYY.VAR" 
// ">TXVAR.EXP" ">TYVAR.EXP" ">ZROT" KEYWORD COMMENT ">END" COLON 
const antlr::BitSet EDIParser::_tokenSet_16(_tokenSet_16_data_,4);


