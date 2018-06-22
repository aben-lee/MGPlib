#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T17:18:32
#
#-------------------------------------------------
BASE_DIR = $$PWD/
QT       -= gui

TARGET = antlr
TEMPLATE = lib
DESTDIR        = $$BASE_DIR/lib

DEFINES += HAVEANTLR

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEPENDPATH     += . cpp
INCLUDEPATH    += . cpp

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpp/src/ANTLRUtil.cpp \
    cpp/src/ASTFactory.cpp \
    cpp/src/ASTNULLType.cpp \
    cpp/src/ASTRefCount.cpp \
    cpp/src/BaseAST.cpp \
    cpp/src/BitSet.cpp \
    cpp/src/CharBuffer.cpp \
    cpp/src/CharScanner.cpp \
    cpp/src/CommonAST.cpp \
    cpp/src/CommonASTWithHiddenTokens.cpp \
    cpp/src/CommonHiddenStreamToken.cpp \
    cpp/src/CommonToken.cpp \
    cpp/src/dll.cpp \
    cpp/src/InputBuffer.cpp \
    cpp/src/LLkParser.cpp \
    cpp/src/MismatchedCharException.cpp \
    cpp/src/MismatchedTokenException.cpp \
    cpp/src/NoViableAltException.cpp \
    cpp/src/NoViableAltForCharException.cpp \
    cpp/src/Parser.cpp \
    cpp/src/RecognitionException.cpp \
    cpp/src/String.cpp \
    cpp/src/Token.cpp \
    cpp/src/TokenBuffer.cpp \
    cpp/src/TokenRefCount.cpp \
    cpp/src/TokenStreamBasicFilter.cpp \
    cpp/src/TokenStreamHiddenTokenFilter.cpp \
    cpp/src/TokenStreamRewriteEngine.cpp \
    cpp/src/TokenStreamSelector.cpp \
    cpp/src/TreeParser.cpp


HEADERS += \
    cpp/antlr/ANTLRException.hpp \
    cpp/antlr/ANTLRUtil.hpp \
    cpp/antlr/AST.hpp \
    cpp/antlr/ASTArray.hpp \
    cpp/antlr/ASTFactory.hpp \
    cpp/antlr/ASTNULLType.hpp \
    cpp/antlr/ASTPair.hpp \
    cpp/antlr/ASTRefCount.hpp \
    cpp/antlr/BaseAST.hpp \
    cpp/antlr/BitSet.hpp \
    cpp/antlr/CharBuffer.hpp \
    cpp/antlr/CharInputBuffer.hpp \
    cpp/antlr/CharScanner.hpp \
    cpp/antlr/CharStreamException.hpp \
    cpp/antlr/CharStreamIOException.hpp \
    cpp/antlr/CircularQueue.hpp \
    cpp/antlr/CommonAST.hpp \
    cpp/antlr/CommonASTWithHiddenTokens.hpp \
    cpp/antlr/CommonHiddenStreamToken.hpp \
    cpp/antlr/CommonToken.hpp \
    cpp/antlr/config.hpp \
    cpp/antlr/InputBuffer.hpp \
    cpp/antlr/IOException.hpp \
    cpp/antlr/LexerSharedInputState.hpp \
    cpp/antlr/LLkParser.hpp \
    cpp/antlr/MismatchedCharException.hpp \
    cpp/antlr/MismatchedTokenException.hpp \
    cpp/antlr/NoViableAltException.hpp \
    cpp/antlr/NoViableAltForCharException.hpp \
    cpp/antlr/Parser.hpp \
    cpp/antlr/ParserSharedInputState.hpp \
    cpp/antlr/RecognitionException.hpp \
    cpp/antlr/RefCount.hpp \
    cpp/antlr/SemanticException.hpp \
    cpp/antlr/String.hpp \
    cpp/antlr/Token.hpp \
    cpp/antlr/TokenBuffer.hpp \
    cpp/antlr/TokenRefCount.hpp \
    cpp/antlr/TokenStream.hpp \
    cpp/antlr/TokenStreamBasicFilter.hpp \
    cpp/antlr/TokenStreamException.hpp \
    cpp/antlr/TokenStreamHiddenTokenFilter.hpp \
    cpp/antlr/TokenStreamIOException.hpp \
    cpp/antlr/TokenStreamRecognitionException.hpp \
    cpp/antlr/TokenStreamRetryException.hpp \
    cpp/antlr/TokenStreamRewriteEngine.hpp \
    cpp/antlr/TokenStreamSelector.hpp \
    cpp/antlr/TokenWithIndex.hpp \
    cpp/antlr/TreeParser.hpp \
    cpp/antlr/TreeParserSharedInputState.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}



