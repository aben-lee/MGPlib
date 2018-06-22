#ifndef INC_EDILexer_hpp_
#define INC_EDILexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20110618): "EdiParser2.g" -> "EDILexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "EDIParserTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 1 "EdiParser2.g"

	#include <iostream>	
	#include "types.h"
	#include "convert.h"
	#include <complex>	

#line 19 "EDILexer.hpp"
class CUSTOM_API EDILexer : public antlr::CharScanner, public EDIParserTokenTypes
{
#line 1 "EdiParser2.g"
#line 23 "EDILexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	EDILexer(std::istream& in);
	EDILexer(antlr::InputBuffer& ib);
	EDILexer(const antlr::LexerSharedInputState& state);
	antlr::RefToken nextToken();
	public: void mHEAD(bool _createToken);
	public: void mKEYWORD(bool _createToken);
	public: void mSPECIAL(bool _createToken);
	public: void mSTRING(bool _createToken);
	public: void mWS(bool _createToken);
	public: void mEQUAL(bool _createToken);
	public: void mSLASH(bool _createToken);
	public: void mEXKL(bool _createToken);
	public: void mCOLON(bool _createToken);
	public: void mCOMMENT(bool _createToken);
	public: void mNUMBER(bool _createToken);
	protected: void mREAL(bool _createToken);
	protected: void mINT(bool _createToken);
	protected: void mLETTER(bool _createToken);
	public: void mLEGAL_CHAR(bool _createToken);
	public: void mDATE(bool _createToken);
	public: void mDIGIT(bool _createToken);
	public: void mOTHER(bool _createToken);
	protected: void mNONUMBER(bool _createToken);
	protected: void mSIGN(bool _createToken);
private:
	
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
};

#endif /*INC_EDILexer_hpp_*/
