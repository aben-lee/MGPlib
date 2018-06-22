#ifndef INC_JLexer_hpp_
#define INC_JLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20110618): "JParser.g" -> "JLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "JParserTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#include <antlr/CharBuffer.hpp>
#include <antlr/TokenStreamException.hpp>
#include <antlr/TokenStreamIOException.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/CharStreamException.hpp>
#include <antlr/CharStreamIOException.hpp>
#include <antlr/NoViableAltForCharException.hpp>
#line 1 "JParser.g"

	#include <iostream>	
	#include <iomanip>
	#include <string>
	#include <cstdlib>
	#include "types.h"

#line 13 "JLexer.cpp"
#line 20 "JLexer.hpp"
class CUSTOM_API JLexer : public antlr::CharScanner, public JParserTokenTypes
{
#line 1 "JParser.g"
#line 24 "JLexer.hpp"
private:
        void initLiterals(){};
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
        JLexer(std::istream& in): antlr::CharScanner(new antlr::CharBuffer(in),false)
        {
                initLiterals();
        }

        JLexer(antlr::InputBuffer& ib): antlr::CharScanner(ib,false)
        {
                initLiterals();
        }
        JLexer(const antlr::LexerSharedInputState& state): antlr::CharScanner(state,false)
        {
                initLiterals();
        }
        antlr::RefToken nextToken()
        {
                antlr::RefToken theRetToken;
                for (;;) {
                        antlr::RefToken theRetToken;
                        int _ttype = antlr::Token::INVALID_TYPE;
                        resetText();
                        try {   // for lexical and char stream error handling
                                switch ( LA(1)) {
                                case 0x3d /* '=' */ :
                                {
                                        mEQUAL(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                case 0x9 /* '\t' */ :
                                case 0x20 /* ' ' */ :
                                {
                                        mWS(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                case 0x23 /* '#' */ :
                                {
                                        mCOMMENT(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                case 0xa /* '\n' */ :
                                case 0xd /* '\r' */ :
                                {
                                        mNEWLINE(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                default:
                                        if ((LA(1) == 0x75 /* 'u' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x74 /* 't' */ ) && (LA(5) == 0x73 /* 's' */ ) && (true)) {
                                                mUNITS(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x66 /* 'f' */ ) && (LA(2) == 0x69 /* 'i' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x64 /* 'd' */ ) && (true)) {
                                                mFIELD(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x2e /* '.' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x2e /* '.' */ ) && (true) && (true)) {
                                                mSI(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6e /* 'n' */ ) && (LA(2) == 0x61 /* 'a' */ ) && (LA(3) == 0x6e /* 'n' */ ) && (true) && (true) && (true)) {
                                                mUNDEF(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x7a /* 'z' */ ) && (LA(2) == 0x78 /* 'x' */ ) && (LA(3) == 0x78 /* 'x' */ ) && (true) && (true) && (true)) {
                                                mZXX(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x7a /* 'z' */ ) && (LA(2) == 0x78 /* 'x' */ ) && (LA(3) == 0x79 /* 'y' */ ) && (true) && (true) && (true)) {
                                                mZXY(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x7a /* 'z' */ ) && (LA(2) == 0x79 /* 'y' */ ) && (LA(3) == 0x78 /* 'x' */ ) && (true) && (true) && (true)) {
                                                mZYX(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x7a /* 'z' */ ) && (LA(2) == 0x79 /* 'y' */ ) && (LA(3) == 0x79 /* 'y' */ ) && (true) && (true) && (true)) {
                                                mZYY(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x78 /* 'x' */ ) && (LA(3) == 0x78 /* 'x' */ ) && (true) && (true) && (true)) {
                                                mRXX(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x78 /* 'x' */ ) && (LA(3) == 0x79 /* 'y' */ ) && (true) && (true) && (true)) {
                                                mRXY(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x79 /* 'y' */ ) && (LA(3) == 0x78 /* 'x' */ ) && (true) && (true) && (true)) {
                                                mRYX(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x79 /* 'y' */ ) && (LA(3) == 0x79 /* 'y' */ ) && (true) && (true) && (true)) {
                                                mRYY(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x7a /* 'z' */ ) && (LA(3) == 0x78 /* 'x' */ ) && (true) && (true) && (true)) {
                                                mTZX(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x7a /* 'z' */ ) && (LA(3) == 0x79 /* 'y' */ ) && (true) && (true) && (true)) {
                                                mTZY(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x6c /* 'l' */ ) && (LA(3) == 0x6f /* 'o' */ )) {
                                                mLONGITUDE(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x6c /* 'l' */ ) && (LA(3) == 0x61 /* 'a' */ )) {
                                                mLATITUDE(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x65 /* 'e' */ )) {
                                                mELEVATION(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x61 /* 'a' */ )) {
                                                mAZIMUTH(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x3e /* '>' */ ) && (LA(2) == 0x73 /* 's' */ )) {
                                                mSTATION(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((_tokenSet_0.member(LA(1))) && (true) && (true) && (true) && (true) && (true)) {
                                                mENTRY(true);
                                                theRetToken=_returnToken;
                                        }
                                else {
                                        if (LA(1)==EOF_CHAR)
                                        {
                                                uponEOF();
                                                _returnToken = makeToken(antlr::Token::EOF_TYPE);
                                        }
                                        else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
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
        public: void mUNDEF(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = UNDEF;
                std::string::size_type _saveIndex;

                match("nan");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mZXX(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = ZXX;
               std::string::size_type _saveIndex;

               match("zxx");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mZXY(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = ZXY;
               std::string::size_type _saveIndex;

               match("zxy");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }

        public: void mZYX(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ZYX;
                std::string::size_type _saveIndex;

                match("zyx");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mZYY(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = ZYY;
               std::string::size_type _saveIndex;

               match("zyy");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mRXX(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RXX;
               std::string::size_type _saveIndex;

               match("rxx");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mRXY(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RXY;
               std::string::size_type _saveIndex;

               match("rxy");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mRYX(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RYX;
               std::string::size_type _saveIndex;

               match("ryx");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }

        public: void mRYY(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RYY;
               std::string::size_type _saveIndex;

               match("ryy");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mTZX(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = TZX;
                std::string::size_type _saveIndex;

                match("tzx");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTZY(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = TZY;
               std::string::size_type _saveIndex;

               match("tzy");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mUNITS(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = UNITS;
               std::string::size_type _saveIndex;

               match("units");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }

        public: void mSI(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = SI;
                std::string::size_type _saveIndex;

                match("s.i.");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mFIELD(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = FIELD;
               std::string::size_type _saveIndex;

               match("field");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mELEVATION(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = ELEVATION;
               std::string::size_type _saveIndex;

               match(">elevation");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mLONGITUDE(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = LONGITUDE;
               std::string::size_type _saveIndex;

               match(">longitude");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mLATITUDE(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = LATITUDE;
               std::string::size_type _saveIndex;

               match(">latitude");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mAZIMUTH(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = AZIMUTH;
                std::string::size_type _saveIndex;

                match(">azimuth");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mSTATION(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = STATION;
                std::string::size_type _saveIndex;

                match(">station");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mEQUAL(bool _createToken)
        {
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
        protected: void mPLUS(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = PLUS;
                std::string::size_type _saveIndex;

                match('+' /* charlit */ );
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        protected: void mMINUS(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MINUS;
                std::string::size_type _saveIndex;

                match('-' /* charlit */ );
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mWS(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = WS;
                std::string::size_type _saveIndex;

                { // ( ... )+
                int _cnt55=0;
                for (;;) {
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
                        default:
                        {
                                if ( _cnt55>=1 ) { goto _loop55; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
                        }
                        }
                        _cnt55++;
                }
                _loop55:;
                }  // ( ... )+
        #line 237 "JParser.g"
                _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
        #line 520 "JLexer.cpp"
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mENTRY(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ENTRY;
                std::string::size_type _saveIndex;

                {
                switch ( LA(1)) {
                case 0x2b /* '+' */ :
                {
                        mPLUS(false);
                        break;
                }
                case 0x2d /* '-' */ :
                {
                        mMINUS(false);
                        break;
                }
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
                        mCHAR(false);
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
                default:
                {
                        throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
                }
                }
                }
                { // ( ... )*
                for (;;) {
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
                                mCHAR(false);
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
                        case 0x2c /* ',' */ :
                        case 0x2e /* '.' */ :
                        case 0x2f /* '/' */ :
                        case 0x3a /* ':' */ :
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
                        case 0x2b /* '+' */ :
                        {
                                mPLUS(false);
                                break;
                        }
                        case 0x2d /* '-' */ :
                        {
                                mMINUS(false);
                                break;
                        }
                        default:
                        {
                                goto _loop59;
                        }
                        }
                }
                _loop59:;
                } // ( ... )*
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        protected: void mCHAR(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = CHAR;
                std::string::size_type _saveIndex;

                {
                matchRange('a','z');
                }
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }

        protected: void mDIGIT(bool _createToken)
        {
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
        protected: void mOTHER(bool _createToken)
        {
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
                case 0x2c /* ',' */ :
                {
                        match(',' /* charlit */ );
                        break;
                }
                case 0x2e /* '.' */ :
                {
                        match('.' /* charlit */ );
                        break;
                }
                case 0x2f /* '/' */ :
                {
                        match('/' /* charlit */ );
                        break;
                }
                case 0x3a /* ':' */ :
                {
                        match(':' /* charlit */ );
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
                case 0x5f /* '_' */ :
                {
                        match('_' /* charlit */ );
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
        public: void mCOMMENT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = COMMENT;
                std::string::size_type _saveIndex;

                match('#' /* charlit */ );
                { // ( ... )*
                for (;;) {
                        if ((_tokenSet_1.member(LA(1)))) {
                                {
                                match(_tokenSet_1);
                                }
                        }
                        else {
                                goto _loop63;
                        }

                }
                _loop63:;
                } // ( ... )*
                mNEWLINE(false);
        #line 249 "JParser.g"

                                        //$setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP);

        #line 891 "JLexer.cpp"
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }

        public: void mNEWLINE(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = NEWLINE;
                std::string::size_type _saveIndex;

                {
                switch ( LA(1)) {
                case 0xa /* '\n' */ :
                {
                        match('\n' /* charlit */ );
                        break;
                }
                case 0xd /* '\r' */ :
                {
                        match('\r' /* charlit */ );
                        match('\n' /* charlit */ );
                        break;
                }
                default:
                {
                        throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());
                }
                }
                }
        #line 257 "JParser.g"
                newline();
        #line 926 "JLexer.cpp"
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
private:
	
        static const unsigned long _tokenSet_0_data_[] = { 0UL, 67053568UL, 0UL, 134217726UL, 0UL, 0UL, 0UL, 0UL };
        static const antlr::BitSet _tokenSet_0(_tokenSet_0_data_,8);
        static const unsigned long _tokenSet_1_data_[] = { 4294958079UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL };
        // 0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xb 0xc 0xe 0xf 0x10 0x11 0x12
        // 0x13 0x14 0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f
        static const antlr::BitSet _tokenSet_1(_tokenSet_1_data_,8);
};

#endif /*INC_JLexer_hpp_*/
