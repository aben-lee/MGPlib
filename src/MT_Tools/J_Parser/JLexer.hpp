#ifndef INC_JLexer_hpp_
#define INC_JLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20110618): "JParser.g" -> "JLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "JParserTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 1 "JParser.g"

	#include <iostream>	
	#include <iomanip>
	#include <string>
	#include <cstdlib>
	#include "types.h"

#line 20 "JLexer.hpp"
class CUSTOM_API JLexer : public antlr::CharScanner, public JParserTokenTypes
{
#line 1 "JParser.g"
#line 24 "JLexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	JLexer(std::istream& in);
	JLexer(antlr::InputBuffer& ib);
	JLexer(const antlr::LexerSharedInputState& state);
	antlr::RefToken nextToken();
	public: void mUNDEF(bool _createToken);
	public: void mZXX(bool _createToken);
	public: void mZXY(bool _createToken);
	public: void mZYX(bool _createToken);
	public: void mZYY(bool _createToken);
	public: void mRXX(bool _createToken);
	public: void mRXY(bool _createToken);
	public: void mRYX(bool _createToken);
	public: void mRYY(bool _createToken);
	public: void mTZX(bool _createToken);
	public: void mTZY(bool _createToken);
	public: void mUNITS(bool _createToken);
	public: void mSI(bool _createToken);
	public: void mFIELD(bool _createToken);
	public: void mELEVATION(bool _createToken);
	public: void mLONGITUDE(bool _createToken);
	public: void mLATITUDE(bool _createToken);
	public: void mAZIMUTH(bool _createToken);
	public: void mSTATION(bool _createToken);
	public: void mEQUAL(bool _createToken);
	protected: void mPLUS(bool _createToken);
	protected: void mMINUS(bool _createToken);
	public: void mWS(bool _createToken);
	public: void mENTRY(bool _createToken);
	protected: void mCHAR(bool _createToken);
	protected: void mDIGIT(bool _createToken);
	protected: void mOTHER(bool _createToken);
	public: void mCOMMENT(bool _createToken);
	public: void mNEWLINE(bool _createToken);
private:
	
	static const unsigned long _tokenSet_0_data_[];
	static const antlr::BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const antlr::BitSet _tokenSet_1;
};

#endif /*INC_JLexer_hpp_*/
