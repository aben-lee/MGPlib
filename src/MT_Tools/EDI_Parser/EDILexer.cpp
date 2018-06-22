/* $ANTLR 2.7.7 (20110618): "EdiParser2.g" -> "EDILexer.cpp"$ */
#include "EDILexer.hpp"
#include <antlr/CharBuffer.hpp>
#include <antlr/TokenStreamException.hpp>
#include <antlr/TokenStreamIOException.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/CharStreamException.hpp>
#include <antlr/CharStreamIOException.hpp>
#include <antlr/NoViableAltForCharException.hpp>

#line 1 "EdiParser2.g"
#line 13 "EDILexer.cpp"
EDILexer::EDILexer(std::istream& in)
	: antlr::CharScanner(new antlr::CharBuffer(in),false)
{
	initLiterals();
}

EDILexer::EDILexer(antlr::InputBuffer& ib)
	: antlr::CharScanner(ib,false)
{
	initLiterals();
}

EDILexer::EDILexer(const antlr::LexerSharedInputState& state)
	: antlr::CharScanner(state,false)
{
	initLiterals();
}

void EDILexer::initLiterals()
{
	literals[">ZYYI.VAR"] = 51;
	literals[">TYI.EXP"] = 38;
	literals[">TXI.EXP"] = 36;
	literals[">TYVAR.EXP"] = 54;
	literals[">ZXYI"] = 30;
	literals["NFREQ"] = 4;
	literals[">ZXYR"] = 29;
	literals[">ZROT"] = 55;
	literals[">ZXXI"] = 28;
	literals[">ZYX.VAR"] = 49;
	literals["REFLAT"] = 10;
	literals[">ZXX.VAR"] = 43;
	literals[">ZXXR"] = 27;
	literals[">HMEAS"] = 19;
	literals["REFLONG"] = 9;
	literals["MTSECT"] = 26;
	literals[">END"] = 58;
	literals["LONGITUDE"] = 6;
	literals[";"] = 25;
	literals[">ZYYI"] = 34;
	literals[">ZYYR"] = 33;
	literals[">ZXYR.VAR"] = 44;
	literals["LATITUDE"] = 5;
	literals[">ZXXR.VAR"] = 41;
	literals[">ZYXI"] = 32;
	literals[">TXVAR.EXP"] = 53;
	literals[">ZYXR.VAR"] = 47;
	literals[">ZYYR.VAR"] = 50;
	literals[">ZYXR"] = 31;
	literals[">TYR.EXP"] = 37;
	literals[">TXR.EXP"] = 35;
	literals["AZIMUTH"] = 7;
	literals[">EMEAS"] = 18;
	literals["ELEVATION"] = 8;
	literals[">ZYY.VAR"] = 52;
	literals[">ZXY.VAR"] = 46;
	literals[">FREQ"] = 40;
	literals["//"] = 22;
	literals["SPECTRA"] = 24;
	literals[">INFO"] = 16;
	literals["SPECTRASET"] = 21;
	literals[">ZXXI.VAR"] = 42;
	literals[">ZXYI.VAR"] = 45;
	literals["DEFINEMEAS"] = 20;
	literals[">ZYXI.VAR"] = 48;
}

antlr::RefToken EDILexer::nextToken()
{
	antlr::RefToken theRetToken;
	for (;;) {
		antlr::RefToken theRetToken;
		int _ttype = antlr::Token::INVALID_TYPE;
		setCommitToPath(false);
		resetText();
		try {   // for lexical and char stream error handling
			switch ( LA(1)) {
			case 0x9 /* '\t' */ :
			case 0xa /* '\n' */ :
			case 0xd /* '\r' */ :
			case 0x20 /* ' ' */ :
			{
				mWS(true);
				theRetToken=_returnToken;
				break;
			}
			case 0x3d /* '=' */ :
			{
				mEQUAL(true);
				theRetToken=_returnToken;
				break;
			}
			case 0x21 /* '!' */ :
			{
				mEXKL(true);
				theRetToken=_returnToken;
				break;
			}
			default:
				if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x61 /* 'a' */ ) && (LA(5) == 0x64 /* 'd' */ ) && (true) && (true) && (true) && (true) && (true)) {
					mHEAD(true);
					theRetToken=_returnToken;
				}
				else if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ )) && ((LA(2) >= 0x30 /* '0' */  && LA(2) <= 0x39 /* '9' */ )) && (LA(3) == 0x2f /* '/' */ )) {
					mDATE(true);
					theRetToken=_returnToken;
				}
				else if ((LA(1) == 0x3e /* '>' */ ) && (_tokenSet_0.member(LA(2))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mKEYWORD(true);
					theRetToken=_returnToken;
				}
				else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x21 /* '!' */ )) {
					mCOMMENT(true);
					theRetToken=_returnToken;
				}
				else if ((LA(1) == 0x3e /* '>' */ ) && (true)) {
					mSPECIAL(true);
					theRetToken=_returnToken;
				}
				else if ((_tokenSet_0.member(LA(1))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mSTRING(true);
					theRetToken=_returnToken;
				}
				else if ((LA(1) == 0x2f /* '/' */ ) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mSLASH(true);
					theRetToken=_returnToken;
				}
				else if ((LA(1) == 0x3a /* ':' */ ) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mCOLON(true);
					theRetToken=_returnToken;
				}
				else if ((_tokenSet_1.member(LA(1))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mNUMBER(true);
					theRetToken=_returnToken;
				}
				else if ((_tokenSet_2.member(LA(1))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mLEGAL_CHAR(true);
					theRetToken=_returnToken;
				}
				else if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ )) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mDIGIT(true);
					theRetToken=_returnToken;
				}
				else if ((_tokenSet_3.member(LA(1))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
					mOTHER(true);
					theRetToken=_returnToken;
				}
			else {
				if (LA(1)==EOF_CHAR)
				{
					uponEOF();
					_returnToken = makeToken(antlr::Token::EOF_TYPE);
				}
				else {consume(); goto tryAgain;}
			}
			}
			if ( !_returnToken )
				goto tryAgain; // found SKIP token

			_ttype = _returnToken->getType();
			_ttype = testLiteralsTable(_ttype);
			_returnToken->setType(_ttype);
			return _returnToken;
		}
		catch (antlr::RecognitionException& e) {
			if ( !getCommitToPath() ) {
				consume();
				goto tryAgain;
			}
				throw antlr::TokenStreamRecognitionException(e);
		}
		catch (antlr::CharStreamIOException& csie) {
			throw antlr::TokenStreamIOException(csie.io);
		}
		catch (antlr::CharStreamException& cse) {
			throw antlr::TokenStreamException(cse.getMessage());
		}
tryAgain:;
	}
}

void EDILexer::mHEAD(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = HEAD;
	std::string::size_type _saveIndex;
	
	match(">head");
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mKEYWORD(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = KEYWORD;
	std::string::size_type _saveIndex;
	
	mSPECIAL(false);
	mSTRING(false);
	_ttype = testLiteralsTable(_ttype);
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mSPECIAL(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = SPECIAL;
	std::string::size_type _saveIndex;
	
	match('>' /* charlit */ );
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mSTRING(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = STRING;
	std::string::size_type _saveIndex;
	
	switch ( LA(1)) {
	case 0x61 /* 'a' */ :
	case 0x62 /* 'b' */ :
	case 0x63 /* 'c' */ :
	case 0x64 /* 'd' */ :
	case 0x65 /* 'e' */ :
	case 0x66 /* 'f' */ :
	case 0x67 /* 'g' */ :
	case 0x68 /* 'h' */ :
	case 0x69 /* 'i' */ :
	case 0x6a /* 'j' */ :
	case 0x6b /* 'k' */ :
	case 0x6c /* 'l' */ :
	case 0x6d /* 'm' */ :
	case 0x6e /* 'n' */ :
	case 0x6f /* 'o' */ :
	case 0x70 /* 'p' */ :
	case 0x71 /* 'q' */ :
	case 0x72 /* 'r' */ :
	case 0x73 /* 's' */ :
	case 0x74 /* 't' */ :
	case 0x75 /* 'u' */ :
	case 0x76 /* 'v' */ :
	case 0x77 /* 'w' */ :
	case 0x78 /* 'x' */ :
	case 0x79 /* 'y' */ :
	case 0x7a /* 'z' */ :
	{
		mLETTER(false);
		{ // ( ... )*
		for (;;) {
			if ((_tokenSet_2.member(LA(1)))) {
				mLEGAL_CHAR(false);
			}
			else {
				goto _loop78;
			}
			
		}
		_loop78:;
		} // ( ... )*
		break;
	}
	case 0x22 /* '\"' */ :
	{
		{
		match('\"' /* charlit */ );
		{ // ( ... )*
		for (;;) {
			switch ( LA(1)) {
			case 0x23 /* '#' */ :
			case 0x24 /* '$' */ :
			case 0x25 /* '%' */ :
			case 0x26 /* '&' */ :
			case 0x27 /* '\'' */ :
			case 0x28 /* '(' */ :
			case 0x29 /* ')' */ :
			case 0x2a /* '*' */ :
			case 0x2b /* '+' */ :
			case 0x2c /* ',' */ :
			case 0x2d /* '-' */ :
			case 0x2e /* '.' */ :
			case 0x2f /* '/' */ :
			case 0x30 /* '0' */ :
			case 0x31 /* '1' */ :
			case 0x32 /* '2' */ :
			case 0x33 /* '3' */ :
			case 0x34 /* '4' */ :
			case 0x35 /* '5' */ :
			case 0x36 /* '6' */ :
			case 0x37 /* '7' */ :
			case 0x38 /* '8' */ :
			case 0x39 /* '9' */ :
			case 0x3a /* ':' */ :
			case 0x3b /* ';' */ :
			case 0x3c /* '<' */ :
			case 0x3f /* '?' */ :
			case 0x40 /* '@' */ :
			case 0x5b /* '[' */ :
			case 0x5d /* ']' */ :
			case 0x5e /* '^' */ :
			case 0x5f /* '_' */ :
			case 0x61 /* 'a' */ :
			case 0x62 /* 'b' */ :
			case 0x63 /* 'c' */ :
			case 0x64 /* 'd' */ :
			case 0x65 /* 'e' */ :
			case 0x66 /* 'f' */ :
			case 0x67 /* 'g' */ :
			case 0x68 /* 'h' */ :
			case 0x69 /* 'i' */ :
			case 0x6a /* 'j' */ :
			case 0x6b /* 'k' */ :
			case 0x6c /* 'l' */ :
			case 0x6d /* 'm' */ :
			case 0x6e /* 'n' */ :
			case 0x6f /* 'o' */ :
			case 0x70 /* 'p' */ :
			case 0x71 /* 'q' */ :
			case 0x72 /* 'r' */ :
			case 0x73 /* 's' */ :
			case 0x74 /* 't' */ :
			case 0x75 /* 'u' */ :
			case 0x76 /* 'v' */ :
			case 0x77 /* 'w' */ :
			case 0x78 /* 'x' */ :
			case 0x79 /* 'y' */ :
			case 0x7a /* 'z' */ :
			case 0x7b /* '{' */ :
			case 0x7c /* '|' */ :
			case 0x7d /* '}' */ :
			case 0x7e /* '~' */ :
			{
				mLEGAL_CHAR(false);
				break;
			}
			case 0x20 /* ' ' */ :
			{
				match(' ' /* charlit */ );
				break;
			}
			default:
			{
				goto _loop81;
			}
			}
		}
		_loop81:;
		} // ( ... )*
		match('\"' /* charlit */ );
		}
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mWS(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = WS;
	std::string::size_type _saveIndex;
	
	{
	switch ( LA(1)) {
	case 0x20 /* ' ' */ :
	{
		match(' ' /* charlit */ );
		break;
	}
	case 0x9 /* '\t' */ :
	{
		match('\t' /* charlit */ );
		break;
	}
	case 0xd /* '\r' */ :
	{
		match('\r' /* charlit */ );
		match('\n' /* charlit */ );
		if ( inputState->guessing==0 ) {
#line 245 "EdiParser2.g"
			newline();
#line 414 "EDILexer.cpp"
		}
		break;
	}
	case 0xa /* '\n' */ :
	{
		match('\n' /* charlit */ );
		if ( inputState->guessing==0 ) {
#line 246 "EdiParser2.g"
			newline();
#line 424 "EDILexer.cpp"
		}
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	}
	if ( inputState->guessing==0 ) {
#line 248 "EdiParser2.g"
		_ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
#line 437 "EDILexer.cpp"
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mEQUAL(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = EQUAL;
	std::string::size_type _saveIndex;
	
	match('=' /* charlit */ );
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mSLASH(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = SLASH;
	std::string::size_type _saveIndex;
	
	match('/' /* charlit */ );
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mEXKL(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = EXKL;
	std::string::size_type _saveIndex;
	
	match('!' /* charlit */ );
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mCOLON(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = COLON;
	std::string::size_type _saveIndex;
	
	match(':' /* charlit */ );
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mCOMMENT(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = COMMENT;
	std::string::size_type _saveIndex;
	
	mSPECIAL(false);
	mEXKL(false);
	{ // ( ... )*
	for (;;) {
		if ((_tokenSet_4.member(LA(1)))) {
			matchNot('!' /* charlit */ );
		}
		else {
			goto _loop67;
		}
		
	}
	_loop67:;
	} // ( ... )*
	mEXKL(false);
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mNUMBER(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = NUMBER;
	std::string::size_type _saveIndex;
	
	{
	switch ( LA(1)) {
	case 0x2b /* '+' */ :
	{
		match('+' /* charlit */ );
		break;
	}
	case 0x2d /* '-' */ :
	{
		match('-' /* charlit */ );
		break;
	}
	case 0x2e /* '.' */ :
	case 0x30 /* '0' */ :
	case 0x31 /* '1' */ :
	case 0x32 /* '2' */ :
	case 0x33 /* '3' */ :
	case 0x34 /* '4' */ :
	case 0x35 /* '5' */ :
	case 0x36 /* '6' */ :
	case 0x37 /* '7' */ :
	case 0x38 /* '8' */ :
	case 0x39 /* '9' */ :
	{
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	}
	{
	bool synPredMatched72 = false;
	if (((_tokenSet_5.member(LA(1))) && (_tokenSet_5.member(LA(2))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true))) {
		int _m72 = mark();
		synPredMatched72 = true;
		inputState->guessing++;
		try {
			{
			mREAL(false);
			}
		}
		catch (antlr::RecognitionException& pe) {
			synPredMatched72 = false;
		}
		rewind(_m72);
		inputState->guessing--;
	}
	if ( synPredMatched72 ) {
		mREAL(false);
	}
	else if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ )) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
		mINT(false);
	}
	else {
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	
	}
	{
	if ((LA(1) == 0x65 /* 'e' */ )) {
		{
		match('e' /* charlit */ );
		}
		{
		switch ( LA(1)) {
		case 0x2b /* '+' */ :
		{
			match('+' /* charlit */ );
			break;
		}
		case 0x2d /* '-' */ :
		{
			match('-' /* charlit */ );
			break;
		}
		case 0x30 /* '0' */ :
		case 0x31 /* '1' */ :
		case 0x32 /* '2' */ :
		case 0x33 /* '3' */ :
		case 0x34 /* '4' */ :
		case 0x35 /* '5' */ :
		case 0x36 /* '6' */ :
		case 0x37 /* '7' */ :
		case 0x38 /* '8' */ :
		case 0x39 /* '9' */ :
		{
			break;
		}
		default:
		{
			throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
		}
		}
		}
		mINT(false);
	}
	else {
	}
	
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mREAL(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = REAL;
	std::string::size_type _saveIndex;
	
	{
	switch ( LA(1)) {
	case 0x2e /* '.' */ :
	{
		match('.' /* charlit */ );
		mINT(false);
		break;
	}
	case 0x30 /* '0' */ :
	case 0x31 /* '1' */ :
	case 0x32 /* '2' */ :
	case 0x33 /* '3' */ :
	case 0x34 /* '4' */ :
	case 0x35 /* '5' */ :
	case 0x36 /* '6' */ :
	case 0x37 /* '7' */ :
	case 0x38 /* '8' */ :
	case 0x39 /* '9' */ :
	{
		mINT(false);
		match('.' /* charlit */ );
		{
		if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ ))) {
			mINT(false);
		}
		else {
		}
		
		}
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mINT(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = INT;
	std::string::size_type _saveIndex;
	
	{ // ( ... )+
	int _cnt90=0;
	for (;;) {
		if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ ))) {
			mDIGIT(false);
		}
		else {
			if ( _cnt90>=1 ) { goto _loop90; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
		}
		
		_cnt90++;
	}
	_loop90:;
	}  // ( ... )+
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mLETTER(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = LETTER;
	std::string::size_type _saveIndex;
	
	matchRange('a','z');
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mLEGAL_CHAR(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = LEGAL_CHAR;
	std::string::size_type _saveIndex;
	
	switch ( LA(1)) {
	case 0x61 /* 'a' */ :
	case 0x62 /* 'b' */ :
	case 0x63 /* 'c' */ :
	case 0x64 /* 'd' */ :
	case 0x65 /* 'e' */ :
	case 0x66 /* 'f' */ :
	case 0x67 /* 'g' */ :
	case 0x68 /* 'h' */ :
	case 0x69 /* 'i' */ :
	case 0x6a /* 'j' */ :
	case 0x6b /* 'k' */ :
	case 0x6c /* 'l' */ :
	case 0x6d /* 'm' */ :
	case 0x6e /* 'n' */ :
	case 0x6f /* 'o' */ :
	case 0x70 /* 'p' */ :
	case 0x71 /* 'q' */ :
	case 0x72 /* 'r' */ :
	case 0x73 /* 's' */ :
	case 0x74 /* 't' */ :
	case 0x75 /* 'u' */ :
	case 0x76 /* 'v' */ :
	case 0x77 /* 'w' */ :
	case 0x78 /* 'x' */ :
	case 0x79 /* 'y' */ :
	case 0x7a /* 'z' */ :
	{
		mLETTER(false);
		break;
	}
	case 0x30 /* '0' */ :
	case 0x31 /* '1' */ :
	case 0x32 /* '2' */ :
	case 0x33 /* '3' */ :
	case 0x34 /* '4' */ :
	case 0x35 /* '5' */ :
	case 0x36 /* '6' */ :
	case 0x37 /* '7' */ :
	case 0x38 /* '8' */ :
	case 0x39 /* '9' */ :
	{
		mDIGIT(false);
		break;
	}
	case 0x23 /* '#' */ :
	case 0x24 /* '$' */ :
	case 0x25 /* '%' */ :
	case 0x26 /* '&' */ :
	case 0x27 /* '\'' */ :
	case 0x28 /* '(' */ :
	case 0x29 /* ')' */ :
	case 0x2a /* '*' */ :
	case 0x2b /* '+' */ :
	case 0x2c /* ',' */ :
	case 0x2d /* '-' */ :
	case 0x2e /* '.' */ :
	case 0x3b /* ';' */ :
	case 0x3c /* '<' */ :
	case 0x3f /* '?' */ :
	case 0x40 /* '@' */ :
	case 0x5b /* '[' */ :
	case 0x5d /* ']' */ :
	case 0x5e /* '^' */ :
	case 0x5f /* '_' */ :
	case 0x7b /* '{' */ :
	case 0x7c /* '|' */ :
	case 0x7d /* '}' */ :
	case 0x7e /* '~' */ :
	{
		mOTHER(false);
		break;
	}
	case 0x3a /* ':' */ :
	{
		mCOLON(false);
		break;
	}
	case 0x2f /* '/' */ :
	{
		mSLASH(false);
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mDATE(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = DATE;
	std::string::size_type _saveIndex;
	
	mDIGIT(false);
	mDIGIT(false);
	match('/' /* charlit */ );
	mDIGIT(false);
	mDIGIT(false);
	match('/' /* charlit */ );
	mDIGIT(false);
	mDIGIT(false);
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mDIGIT(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = DIGIT;
	std::string::size_type _saveIndex;
	
	matchRange('0','9');
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mOTHER(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = OTHER;
	std::string::size_type _saveIndex;
	
	switch ( LA(1)) {
	case 0x27 /* '\'' */ :
	{
		match('\'' /* charlit */ );
		break;
	}
	case 0x23 /* '#' */ :
	{
		match('#' /* charlit */ );
		break;
	}
	case 0x24 /* '$' */ :
	{
		match('$' /* charlit */ );
		break;
	}
	case 0x25 /* '%' */ :
	{
		match('%' /* charlit */ );
		break;
	}
	case 0x26 /* '&' */ :
	{
		match('&' /* charlit */ );
		break;
	}
	case 0x28 /* '(' */ :
	{
		match('(' /* charlit */ );
		break;
	}
	case 0x29 /* ')' */ :
	{
		match(')' /* charlit */ );
		break;
	}
	case 0x2a /* '*' */ :
	{
		match('*' /* charlit */ );
		break;
	}
	case 0x2b /* '+' */ :
	{
		match('+' /* charlit */ );
		break;
	}
	case 0x2c /* ',' */ :
	{
		match(',' /* charlit */ );
		break;
	}
	case 0x2d /* '-' */ :
	{
		match('-' /* charlit */ );
		break;
	}
	case 0x2e /* '.' */ :
	{
		match('.' /* charlit */ );
		break;
	}
	case 0x3b /* ';' */ :
	{
		match(';' /* charlit */ );
		break;
	}
	case 0x3c /* '<' */ :
	{
		match('<' /* charlit */ );
		break;
	}
	case 0x3f /* '?' */ :
	{
		match('?' /* charlit */ );
		break;
	}
	case 0x40 /* '@' */ :
	{
		match('@' /* charlit */ );
		break;
	}
	case 0x5b /* '[' */ :
	{
		match('[' /* charlit */ );
		break;
	}
	case 0x5d /* ']' */ :
	{
		match(']' /* charlit */ );
		break;
	}
	case 0x5e /* '^' */ :
	{
		match('^' /* charlit */ );
		break;
	}
	case 0x5f /* '_' */ :
	{
		match('_' /* charlit */ );
		break;
	}
	case 0x7b /* '{' */ :
	{
		match('{' /* charlit */ );
		break;
	}
	case 0x7c /* '|' */ :
	{
		match('|' /* charlit */ );
		break;
	}
	case 0x7d /* '}' */ :
	{
		match('}' /* charlit */ );
		break;
	}
	case 0x7e /* '~' */ :
	{
		match('~' /* charlit */ );
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mNONUMBER(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = NONUMBER;
	std::string::size_type _saveIndex;
	
	switch ( LA(1)) {
	case 0x4e /* 'N' */ :
	{
		match("Nan");
		break;
	}
	case 0x69 /* 'i' */ :
	{
		match("inf");
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}

void EDILexer::mSIGN(bool _createToken) {
	int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
	_ttype = SIGN;
	std::string::size_type _saveIndex;
	
	switch ( LA(1)) {
	case 0x2b /* '+' */ :
	{
		match('+' /* charlit */ );
		break;
	}
	case 0x2d /* '-' */ :
	{
		match('-' /* charlit */ );
		break;
	}
	default:
	{
		throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
	}
	}
	if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
	   _token = makeToken(_ttype);
	   _token->setText(text.substr(_begin, text.length()-_begin));
	}
	_returnToken = _token;
	_saveIndex=0;
}


const unsigned long EDILexer::_tokenSet_0_data_[] = { 0UL, 4UL, 0UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// \" 
const antlr::BitSet EDILexer::_tokenSet_0(_tokenSet_0_data_,10);
const unsigned long EDILexer::_tokenSet_1_data_[] = { 0UL, 67069952UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// + - . 0 1 2 3 4 5 6 7 8 9 
const antlr::BitSet EDILexer::_tokenSet_1(_tokenSet_1_data_,10);
const unsigned long EDILexer::_tokenSet_2_data_[] = { 0UL, 2684354552UL, 3892314113UL, 2147483646UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// # $ % & \' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < ? @ 
const antlr::BitSet EDILexer::_tokenSet_2(_tokenSet_2_data_,10);
const unsigned long EDILexer::_tokenSet_3_data_[] = { 0UL, 2550169592UL, 3892314113UL, 2013265920UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// # $ % & \' ( ) * + , - . ; < ? @ 
const antlr::BitSet EDILexer::_tokenSet_3(_tokenSet_3_data_,10);
const unsigned long EDILexer::_tokenSet_4_data_[] = { 4294967288UL, 4294967293UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xa 0xb 0xc 0xd 0xe 0xf 0x10 0x11 0x12 0x13 
// 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f   \" # $ 
// % & \' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D 
const antlr::BitSet EDILexer::_tokenSet_4(_tokenSet_4_data_,16);
const unsigned long EDILexer::_tokenSet_5_data_[] = { 0UL, 67059712UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// . 0 1 2 3 4 5 6 7 8 9 
const antlr::BitSet EDILexer::_tokenSet_5(_tokenSet_5_data_,10);

