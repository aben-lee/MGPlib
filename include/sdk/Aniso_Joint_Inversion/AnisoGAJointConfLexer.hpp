#ifndef INC_AnisoGAJointConfLexer_hpp_
#define INC_AnisoGAJointConfLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20100319): "AnisoGAJointConf.g" -> "AnisoGAJointConfLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "AnisoGAJointConfParserTokenTypes.hpp"

#include <antlr/CharScanner.hpp>
#include <antlr/CharBuffer.hpp>
#include <antlr/TokenStreamException.hpp>
#include <antlr/TokenStreamIOException.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/CharStreamException.hpp>
#include <antlr/CharStreamIOException.hpp>
#include <antlr/NoViableAltForCharException.hpp>
#line 1 "AnisoGAJointConf.g"
#line 13 "AnisoGAJointConfLexer.cpp"

	#include <string>
	#include <vector>
	#include <iostream>
	#include <cstdlib>

#line 19 "AnisoGAJointConfLexer.hpp"
class CUSTOM_API AnisoGAJointConfLexer : public antlr::CharScanner, public AnisoGAJointConfParserTokenTypes
{
#line 1 "AnisoGAJointConf.g"
#line 23 "AnisoGAJointConfLexer.hpp"
private:
        void initLiterals()
        {
        }
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
        AnisoGAJointConfLexer(std::istream& in)
            : antlr::CharScanner(new antlr::CharBuffer(in),false)
    {
            initLiterals();
    }
        AnisoGAJointConfLexer(antlr::InputBuffer& ib)
            : antlr::CharScanner(ib,false)
    {
            initLiterals();
    }
        AnisoGAJointConfLexer(const antlr::LexerSharedInputState& state)
            : antlr::CharScanner(state,false)
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
                                case 0xa /* '\n' */ :
                                case 0xd /* '\r' */ :
                                case 0x20 /* ' ' */ :
                                {
                                        mWS(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                case 0x2b /* '+' */ :
                                case 0x2d /* '-' */ :
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
                                        mNUMBER(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                case 0x2f /* '/' */ :
                                {
                                        mCOMMENT(true);
                                        theRetToken=_returnToken;
                                        break;
                                }
                                default:
                                        if ((LA(1) == 0x6d /* 'm' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x66 /* 'f' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x78 /* 'x' */ ) && (LA(8) == 0x70 /* 'p' */ ) && (LA(9) == 0x6f /* 'o' */ ) && (LA(10) == 0x6e /* 'n' */ )) {
                                                mMTFITEXPONENTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x63 /* 'c' */ ) && (LA(2) == 0x6f /* 'o' */ ) && (LA(3) == 0x6f /* 'o' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x6e /* 'n' */ ) && (LA(7) == 0x67 /* 'g' */ ) && (LA(8) == 0x72 /* 'r' */ ) && (LA(9) == 0x61 /* 'a' */ ) && (LA(10) == 0x74 /* 't' */ )) {
                                                mCOOLINGRATIOT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x67 /* 'g' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6e /* 'n' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (LA(5) == 0x72 /* 'r' */ ) && (LA(6) == 0x61 /* 'a' */ ) && (LA(7) == 0x74 /* 't' */ ) && (LA(8) == 0x69 /* 'i' */ ) && (LA(9) == 0x6f /* 'o' */ ) && (LA(10) == 0x6e /* 'n' */ )) {
                                                mGENERATIONST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6d /* 'm' */ ) && (LA(2) == 0x75 /* 'u' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x61 /* 'a' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x69 /* 'i' */ ) && (LA(7) == 0x6f /* 'o' */ ) && (LA(8) == 0x6e /* 'n' */ ) && (LA(9) == 0x70 /* 'p' */ ) && (LA(10) == 0x72 /* 'r' */ )) {
                                                mMUTATIONPROBT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x63 /* 'c' */ ) && (LA(2) == 0x72 /* 'r' */ ) && (LA(3) == 0x6f /* 'o' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x6f /* 'o' */ ) && (LA(7) == 0x76 /* 'v' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (LA(9) == 0x72 /* 'r' */ ) && (LA(10) == 0x70 /* 'p' */ )) {
                                                mCROSSOVERPROBT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6e /* 'n' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x6f /* 'o' */ ) && (LA(6) == 0x72 /* 'r' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x72 /* 'r' */ ) && (LA(9) == 0x72 /* 'r' */ ) && (LA(10) == 0x6f /* 'o' */ )) {
                                                mTENSORERRORT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x70 /* 'p' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x61 /* 'a' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x65 /* 'e' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x72 /* 'r' */ ) && (LA(8) == 0x72 /* 'r' */ ) && (LA(9) == 0x6f /* 'o' */ ) && (LA(10) == 0x72 /* 'r' */ )) {
                                                mPHASEERRORT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6f /* 'o' */ ) && (LA(2) == 0x75 /* 'u' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x70 /* 'p' */ ) && (LA(5) == 0x75 /* 'u' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x62 /* 'b' */ ) && (LA(8) == 0x61 /* 'a' */ ) && (LA(9) == 0x73 /* 's' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mOUTPUTBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6d /* 'm' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x6e /* 'n' */ ) && (LA(5) == 0x70 /* 'p' */ ) && (LA(6) == 0x75 /* 'u' */ ) && (LA(7) == 0x74 /* 't' */ ) && (LA(8) == 0x64 /* 'd' */ ) && (LA(9) == 0x61 /* 'a' */ ) && (LA(10) == 0x74 /* 't' */ )) {
                                                mMTINPUTDATAT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x70 /* 'p' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6e /* 'n' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x6f /* 'o' */ ) && (LA(7) == 0x72 /* 'r' */ ) && (LA(8) == 0x64 /* 'd' */ ) && (LA(9) == 0x61 /* 'a' */ ) && (LA(10) == 0x74 /* 't' */ )) {
                                                mPTENSORDATAT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x6e /* 'n' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (LA(5) == 0x61 /* 'a' */ ) && (LA(6) == 0x6c /* 'l' */ ) && (LA(7) == 0x69 /* 'i' */ ) && (LA(8) == 0x6e /* 'n' */ ) && (LA(9) == 0x67 /* 'g' */ ) && (LA(10) == 0x67 /* 'g' */ )) {
                                                mANNEALINGGENERATIONT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x63 /* 'c' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x69 /* 'i' */ ) && (LA(8) == 0x7a /* 'z' */ ) && (LA(9) == 0x65 /* 'e' */ ) && (LA(10) == 0x73 /* 's' */ )) {
                                                mTHICKSIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x62 /* 'b' */ ) && (LA(8) == 0x61 /* 'a' */ ) && (LA(9) == 0x73 /* 's' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mSTRIKEBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x73 /* 's' */ ) && (LA(8) == 0x74 /* 't' */ ) && (LA(9) == 0x65 /* 'e' */ ) && (LA(10) == 0x70 /* 'p' */ )) {
                                                mSTRIKESTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x73 /* 's' */ ) && (LA(8) == 0x69 /* 'i' */ ) && (LA(9) == 0x7a /* 'z' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mSTRIKESIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x64 /* 'd' */ ) && (LA(2) == 0x73 /* 's' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x72 /* 'r' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x6b /* 'k' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x62 /* 'b' */ ) && (LA(9) == 0x61 /* 'a' */ ) && (LA(10) == 0x73 /* 's' */ )) {
                                                mDSTRIKEBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x64 /* 'd' */ ) && (LA(2) == 0x73 /* 's' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x72 /* 'r' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x6b /* 'k' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x73 /* 's' */ ) && (LA(9) == 0x74 /* 't' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mDSTRIKESTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x64 /* 'd' */ ) && (LA(2) == 0x73 /* 's' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x72 /* 'r' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x6b /* 'k' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x73 /* 's' */ ) && (LA(9) == 0x69 /* 'i' */ ) && (LA(10) == 0x7a /* 'z' */ )) {
                                                mDSTRIKESIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x63 /* 'c' */ ) && (LA(2) == 0x6f /* 'o' */ ) && (LA(3) == 0x6e /* 'n' */ ) && (LA(4) == 0x64 /* 'd' */ ) && (LA(5) == 0x64 /* 'd' */ ) && (LA(6) == 0x69 /* 'i' */ ) && (LA(7) == 0x66 /* 'f' */ ) && (LA(8) == 0x66 /* 'f' */ ) && (LA(9) == 0x77 /* 'w' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mCONDDIFFWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x6f /* 'o' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x72 /* 'r' */ ) && (LA(8) == 0x6f /* 'o' */ ) && (LA(9) == 0x70 /* 'p' */ ) && (LA(10) == 0x79 /* 'y' */ )) {
                                                mANISOTROPYWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x64 /* 'd' */ ) && (LA(8) == 0x69 /* 'i' */ ) && (LA(9) == 0x66 /* 'f' */ ) && (LA(10) == 0x66 /* 'f' */ )) {
                                                mSTRIKEDIFFWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x76 /* 'v' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x64 /* 'd' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x66 /* 'f' */ ) && (LA(7) == 0x66 /* 'f' */ ) && (LA(8) == 0x77 /* 'w' */ ) && (LA(9) == 0x65 /* 'e' */ ) && (LA(10) == 0x69 /* 'i' */ )) {
                                                mVELDIFFWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x6f /* 'o' */ ) && (LA(6) == 0x76 /* 'v' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x6c /* 'l' */ ) && (LA(9) == 0x77 /* 'w' */ ) && (LA(10) == 0x65 /* 'e' */ )) {
                                                mANISOVELWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x64 /* 'd' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x74 /* 't' */ ) && (LA(5) == 0x61 /* 'a' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x74 /* 't' */ ) && (LA(8) == 0x72 /* 'r' */ ) && (LA(9) == 0x69 /* 'i' */ ) && (LA(10) == 0x6b /* 'k' */ )) {
                                                mDELTASTRIKEDIFFWEIGHTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x73 /* 's' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x61 /* 'a' */ ) && (LA(4) == 0x72 /* 'r' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x69 /* 'i' */ ) && (LA(8) == 0x6d /* 'm' */ ) && (LA(9) == 0x65 /* 'e' */ ) && (true)) {
                                                mSTARTTIMET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x63 /* 'c' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x62 /* 'b' */ ) && (LA(7) == 0x61 /* 'a' */ ) && (LA(8) == 0x73 /* 's' */ ) && (LA(9) == 0x65 /* 'e' */ ) && (true)) {
                                                mTHICKBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x63 /* 'c' */ ) && (LA(5) == 0x6b /* 'k' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x74 /* 't' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (LA(9) == 0x70 /* 'p' */ ) && (true)) {
                                                mTHICKSTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x72 /* 'r' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x69 /* 'i' */ ) && (LA(7) == 0x7a /* 'z' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (LA(9) == 0x73 /* 's' */ ) && (true)) {
                                                mARESSIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x76 /* 'v' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x69 /* 'i' */ ) && (LA(7) == 0x7a /* 'z' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (LA(9) == 0x73 /* 's' */ ) && (true)) {
                                                mAVELSIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x76 /* 'v' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x72 /* 'r' */ ) && (LA(6) == 0x61 /* 'a' */ ) && (LA(7) == 0x74 /* 't' */ ) && (LA(8) == 0x69 /* 'i' */ ) && (LA(9) == 0x6f /* 'o' */ ) && (true)) {
                                                mAVELRATIOT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x69 /* 'i' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x74 /* 't' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x6d /* 'm' */ ) && (LA(8) == 0x70 /* 'p' */ ) && (true) && (true)) {
                                                mINITTEMPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x73 /* 's' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (LA(5) == 0x72 /* 'r' */ ) && (LA(6) == 0x72 /* 'r' */ ) && (LA(7) == 0x6f /* 'o' */ ) && (LA(8) == 0x72 /* 'r' */ ) && (true) && (true)) {
                                                mRESERRORT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x73 /* 's' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x7a /* 'z' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x73 /* 's' */ ) && (true) && (true)) {
                                                mRESSIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x76 /* 'v' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x7a /* 'z' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x73 /* 's' */ ) && (true) && (true)) {
                                                mVELSIZEST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x72 /* 'r' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x62 /* 'b' */ ) && (LA(6) == 0x61 /* 'a' */ ) && (LA(7) == 0x73 /* 's' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (true) && (true)) {
                                                mARESBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x72 /* 'r' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x70 /* 'p' */ ) && (true) && (true)) {
                                                mARESSTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x76 /* 'v' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x62 /* 'b' */ ) && (LA(6) == 0x61 /* 'a' */ ) && (LA(7) == 0x73 /* 's' */ ) && (LA(8) == 0x65 /* 'e' */ ) && (true) && (true)) {
                                                mAVELBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x61 /* 'a' */ ) && (LA(2) == 0x76 /* 'v' */ ) && (LA(3) == 0x65 /* 'e' */ ) && (LA(4) == 0x6c /* 'l' */ ) && (LA(5) == 0x73 /* 's' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (LA(8) == 0x70 /* 'p' */ ) && (true) && (true)) {
                                                mAVELSTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x76 /* 'v' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x62 /* 'b' */ ) && (LA(5) == 0x6f /* 'o' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (true) && (true) && (true)) {
                                                mVERBOSET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x70 /* 'p' */ ) && (LA(2) == 0x6f /* 'o' */ ) && (LA(3) == 0x70 /* 'p' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x7a /* 'z' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (true) && (true) && (true)) {
                                                mPOPSIZET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x68 /* 'h' */ ) && (LA(3) == 0x72 /* 'r' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (LA(5) == 0x61 /* 'a' */ ) && (LA(6) == 0x64 /* 'd' */ ) && (LA(7) == 0x73 /* 's' */ ) && (true) && (true) && (true)) {
                                                mTHREADST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x65 /* 'e' */ ) && (LA(2) == 0x6e /* 'n' */ ) && (LA(3) == 0x64 /* 'd' */ ) && (LA(4) == 0x74 /* 't' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x6d /* 'm' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (true) && (true) && (true)) {
                                                mENDTIMET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x65 /* 'e' */ ) && (LA(2) == 0x6c /* 'l' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x74 /* 't' */ ) && (LA(5) == 0x69 /* 'i' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x74 /* 't' */ ) && (true) && (true) && (true)) {
                                                mELITISTT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x73 /* 's' */ ) && (LA(4) == 0x62 /* 'b' */ ) && (LA(5) == 0x61 /* 'a' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (true) && (true) && (true)) {
                                                mRESBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x72 /* 'r' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x73 /* 's' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x70 /* 'p' */ ) && (true) && (true) && (true)) {
                                                mRESSTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x76 /* 'v' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x62 /* 'b' */ ) && (LA(5) == 0x61 /* 'a' */ ) && (LA(6) == 0x73 /* 's' */ ) && (LA(7) == 0x65 /* 'e' */ ) && (true) && (true) && (true)) {
                                                mVELBASET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x76 /* 'v' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x74 /* 't' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (LA(7) == 0x70 /* 'p' */ ) && (true) && (true) && (true)) {
                                                mVELSTEPT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x77 /* 'w' */ ) && (LA(2) == 0x65 /* 'e' */ ) && (LA(3) == 0x69 /* 'i' */ ) && (LA(4) == 0x67 /* 'g' */ ) && (LA(5) == 0x68 /* 'h' */ ) && (LA(6) == 0x74 /* 't' */ ) && (LA(7) == 0x73 /* 's' */ ) && (true) && (true) && (true)) {
                                                mWEIGHTST(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x67 /* 'g' */ ) && (LA(2) == 0x61 /* 'a' */ ) && (LA(3) == 0x74 /* 't' */ ) && (LA(4) == 0x79 /* 'y' */ ) && (LA(5) == 0x70 /* 'p' */ ) && (LA(6) == 0x65 /* 'e' */ ) && (true) && (true) && (true) && (true)) {
                                                mGATYPET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x66 /* 'f' */ ) && (LA(2) == 0x61 /* 'a' */ ) && (LA(3) == 0x6c /* 'l' */ ) && (LA(4) == 0x73 /* 's' */ ) && (LA(5) == 0x65 /* 'e' */ ) && (true) && (true) && (true) && (true) && (true)) {
                                                mFALSE(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6d /* 'm' */ ) && (LA(2) == 0x74 /* 't' */ ) && (LA(3) == 0x66 /* 'f' */ ) && (LA(4) == 0x69 /* 'i' */ ) && (LA(5) == 0x74 /* 't' */ ) && (true) && (true) && (true) && (true) && (true)) {
                                                mMTFITT(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x74 /* 't' */ ) && (LA(2) == 0x72 /* 'r' */ ) && (LA(3) == 0x75 /* 'u' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (true) && (true) && (true) && (true) && (true) && (true)) {
                                                mTRUE(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if ((LA(1) == 0x6d /* 'm' */ ) && (LA(2) == 0x6f /* 'o' */ ) && (LA(3) == 0x64 /* 'd' */ ) && (LA(4) == 0x65 /* 'e' */ ) && (true) && (true) && (true) && (true) && (true) && (true)) {
                                                mMODET(true);
                                                theRetToken=_returnToken;
                                        }
                                        else if (((LA(1) >= 0x61 /* 'a' */  && LA(1) <= 0x7a /* 'z' */ )) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true)) {
                                                mSTRING(true);
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
        public: void mTRUE(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = TRUE;
               std::string::size_type _saveIndex;

               match("true");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mFALSE(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = FALSE;
                std::string::size_type _saveIndex;

                match("false");
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
               int _cnt262=0;
               for (;;) {
                       switch ( LA(1)) {
                       case 0x20 /* ' ' */ :
                       {
                               match(' ' /* charlit */ );
                               break;
                       }
                       case 0xa /* '\n' */ :
                       case 0xd /* '\r' */ :
                       {
                               mNEWLINE(false);
                               break;
                       }
                       case 0x9 /* '\t' */ :
                       {
                               match('\t' /* charlit */ );
                               break;
                       }
                       default:
                       {
                               if ( _cnt262>=1 ) { goto _loop262; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
                       }
                       }
                       _cnt262++;
               }
               _loop262:;
               }  // ( ... )+
               if ( inputState->guessing==0 ) {
       #line 195 "AnisoGAJointConf.g"
                       _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
       #line 410 "AnisoGAJointConfLexer.cpp"
               }
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        protected: void mNEWLINE(bool _createToken)
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
                if ( inputState->guessing==0 ) {
        #line 221 "AnisoGAJointConf.g"
                        newline();
        #line 447 "AnisoGAJointConfLexer.cpp"
                }
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mSTRING(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = STRING;
                std::string::size_type _saveIndex;

                mCHAR(false);
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
                        case 0x2b /* '+' */ :
                        case 0x2c /* ',' */ :
                        case 0x2d /* '-' */ :
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
                        default:
                        {
                                goto _loop265;
                        }
                        }
                }
                _loop265:;
                } // ( ... )*
                _ttype = testLiteralsTable(_ttype);
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
        public: void mNUMBER(bool _createToken)
        {
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
                bool synPredMatched270 = false;
                if (((_tokenSet_0.member(LA(1))) && (_tokenSet_0.member(LA(2))) && (true) && (true) && (true) && (true) && (true) && (true) && (true) && (true))) {
                        int _m270 = mark();
                        synPredMatched270 = true;
                        inputState->guessing++;
                        try {
                                {
                                mREAL(false);
                                }
                        }
                        catch (antlr::RecognitionException& pe) {
                                synPredMatched270 = false;
                        }
                        rewind(_m270);
                        inputState->guessing--;
                }
                if ( synPredMatched270 ) {
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
        protected: void mREAL(bool _createToken)
        {
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

        protected: void mINT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = INT;
                std::string::size_type _saveIndex;

                { // ( ... )+
                int _cnt285=0;
                for (;;) {
                        if (((LA(1) >= 0x30 /* '0' */  && LA(1) <= 0x39 /* '9' */ ))) {
                                mDIGIT(false);
                        }
                        else {
                                if ( _cnt285>=1 ) { goto _loop285; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine(), getColumn());}
                        }

                        _cnt285++;
                }
                _loop285:;
                }  // ( ... )+
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

                match('/' /* charlit */ );
                match('/' /* charlit */ );
                { // ( ... )*
                for (;;) {
                        if ((_tokenSet_1.member(LA(1)))) {
                                {
                                match(_tokenSet_1);
                                }
                        }
                        else {
                                goto _loop277;
                        }

                }
                _loop277:;
                } // ( ... )*
                mNEWLINE(false);
                if ( inputState->guessing==0 ) {
        #line 212 "AnisoGAJointConf.g"

                                                _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;

        #line 955 "AnisoGAJointConfLexer.cpp"
                }
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mVERBOSET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = VERBOSET;
                std::string::size_type _saveIndex;

                match("verbose");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mMTFITEXPONENTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MTFITEXPONENTT;
                std::string::size_type _saveIndex;

                match("mtfitexponent");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mPOPSIZET(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = POPSIZET;
               std::string::size_type _saveIndex;

               match("popsize");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mINITTEMPT(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = INITTEMPT;
               std::string::size_type _saveIndex;

               match("inittemp");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mCOOLINGRATIOT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = COOLINGRATIOT;
                std::string::size_type _saveIndex;

                match("coolingratio");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mGENERATIONST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = GENERATIONST;
                std::string::size_type _saveIndex;

                match("generations");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mMUTATIONPROBT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MUTATIONPROBT;
                std::string::size_type _saveIndex;

                match("mutationprob");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mCROSSOVERPROBT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = CROSSOVERPROBT;
                std::string::size_type _saveIndex;

                match("crossoverprob");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTHREADST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = THREADST;
                std::string::size_type _saveIndex;

                match("threads");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mSTARTTIMET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = STARTTIMET;
                std::string::size_type _saveIndex;

                match("starttime");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mENDTIMET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ENDTIMET;
                std::string::size_type _saveIndex;

                match("endtime");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTENSORERRORT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = TENSORERRORT;
                std::string::size_type _saveIndex;

                match("tensorerror");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mRESERRORT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = RESERRORT;
                std::string::size_type _saveIndex;

                match("reserror");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mPHASEERRORT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = PHASEERRORT;
                std::string::size_type _saveIndex;

                match("phaseerror");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mGATYPET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = GATYPET;
                std::string::size_type _saveIndex;

                match("gatype");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mOUTPUTBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = OUTPUTBASET;
                std::string::size_type _saveIndex;

                match("outputbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mMODET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MODET;
                std::string::size_type _saveIndex;

                match("mode");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mMTFITT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MTFITT;
                std::string::size_type _saveIndex;

                match("mtfit");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mMTINPUTDATAT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = MTINPUTDATAT;
                std::string::size_type _saveIndex;

                match("mtinputdata");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mPTENSORDATAT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = PTENSORDATAT;
                std::string::size_type _saveIndex;

                match("ptensordata");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mANNEALINGGENERATIONT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ANNEALINGGENERATIONT;
                std::string::size_type _saveIndex;

                match("annealinggeneration");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mELITISTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ELITISTT;
                std::string::size_type _saveIndex;

                match("elitist");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTHICKBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = THICKBASET;
                std::string::size_type _saveIndex;

                match("thickbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTHICKSTEPT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = THICKSTEPT;
                std::string::size_type _saveIndex;

                match("thickstep");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mTHICKSIZEST(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = THICKSIZEST;
               std::string::size_type _saveIndex;

               match("thicksizes");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mRESBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = RESBASET;
                std::string::size_type _saveIndex;

                match("resbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mRESSTEPT(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RESSTEPT;
               std::string::size_type _saveIndex;

               match("resstep");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mRESSIZEST(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = RESSIZEST;
               std::string::size_type _saveIndex;

               match("ressizes");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mVELBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = VELBASET;
                std::string::size_type _saveIndex;

                match("velbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mVELSTEPT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = VELSTEPT;
                std::string::size_type _saveIndex;

                match("velstep");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mVELSIZEST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = VELSIZEST;
                std::string::size_type _saveIndex;

                match("velsizes");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mARESBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ARESBASET;
                std::string::size_type _saveIndex;

                match("aresbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mARESSTEPT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ARESSTEPT;
                std::string::size_type _saveIndex;

                match("aresstep");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mARESSIZEST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ARESSIZEST;
                std::string::size_type _saveIndex;

                match("aressizes");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mAVELBASET(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = AVELBASET;
                std::string::size_type _saveIndex;

                match("avelbase");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mAVELSTEPT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = AVELSTEPT;
                std::string::size_type _saveIndex;

                match("avelstep");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mAVELSIZEST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = AVELSIZEST;
                std::string::size_type _saveIndex;

                match("avelsizes");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mSTRIKEBASET(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = STRIKEBASET;
               std::string::size_type _saveIndex;

               match("strikebase");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mSTRIKESTEPT(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = STRIKESTEPT;
               std::string::size_type _saveIndex;

               match("strikestep");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mSTRIKESIZEST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = STRIKESIZEST;
                std::string::size_type _saveIndex;

                match("strikesizes");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mDSTRIKEBASET(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = DSTRIKEBASET;
               std::string::size_type _saveIndex;

               match("dstrikebase");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mDSTRIKESTEPT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = DSTRIKESTEPT;
                std::string::size_type _saveIndex;

                match("dstrikestep");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mDSTRIKESIZEST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = DSTRIKESIZEST;
                std::string::size_type _saveIndex;

                match("dstrikesizes");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mWEIGHTST(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = WEIGHTST;
                std::string::size_type _saveIndex;

                match("weights");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mCONDDIFFWEIGHTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = CONDDIFFWEIGHTT;
                std::string::size_type _saveIndex;

                match("conddiffweight");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mANISOTROPYWEIGHTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = ANISOTROPYWEIGHTT;
                std::string::size_type _saveIndex;

                match("anisotropyweight");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mSTRIKEDIFFWEIGHTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = STRIKEDIFFWEIGHTT;
                std::string::size_type _saveIndex;

                match("strikediffweight");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mVELDIFFWEIGHTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = VELDIFFWEIGHTT;
                std::string::size_type _saveIndex;

                match("veldiffweight");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mANISOVELWEIGHTT(bool _createToken)
        {
               int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
               _ttype = ANISOVELWEIGHTT;
               std::string::size_type _saveIndex;

               match("anisovelweight");
               if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                  _token = makeToken(_ttype);
                  _token->setText(text.substr(_begin, text.length()-_begin));
               }
               _returnToken = _token;
               _saveIndex=0;
       }
        public: void mDELTASTRIKEDIFFWEIGHTT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = DELTASTRIKEDIFFWEIGHTT;
                std::string::size_type _saveIndex;

                match("deltastrikediffweight");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
        public: void mAVELRATIOT(bool _createToken)
        {
                int _ttype; antlr::RefToken _token; std::string::size_type _begin = text.length();
                _ttype = AVELRATIOT;
                std::string::size_type _saveIndex;

                match("avelratio");
                if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
                   _token = makeToken(_ttype);
                   _token->setText(text.substr(_begin, text.length()-_begin));
                }
                _returnToken = _token;
                _saveIndex=0;
        }
private:
	
        static const unsigned long _tokenSet_0_data_[]= { 0UL, 67059712UL, 0UL, 0UL, 0UL, 0UL };
        static const antlr::BitSet _tokenSet_0(_tokenSet_0_data_,6);
        static const unsigned long _tokenSet_1_data_[]= { 4294958079UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL };
        static const antlr::BitSet _tokenSet_1(_tokenSet_1_data_,8);
};

#endif /*INC_AnisoGAJointConfLexer_hpp_*/
