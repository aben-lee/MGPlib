header {
	#include <iostream>	
	#include "types.h"
	#include "convert.h"
	#include <complex>	
}
options {
	language="Cpp";
	namespaceStd="std"; 
	namespaceAntlr="antlr";
}


class EDIParser extends Parser;
options {
	genHashLines = true;		// include line number information
	k=10;
	buildAST = false;
}
{
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
}

		

option
{double currvalue; bool isint = false; double *currdouble;}
	: ( "NFREQ" {isint = true; currdouble = NULL;}
		| "LATITUDE" {isint = false; currdouble = &latitude; }
		| "LONGITUDE" {isint = false; currdouble = &longitude;}
		| "AZIMUTH" {isint = false; currdouble = &azimuth;}
		| "ELEVATION" {isint = false; currdouble = &elevation;}
		| "REFLONG" {isint = false; currdouble = &longitude;}
		| "REFLAT" {isint = false; currdouble = &latitude;}
		| a:STRING {currdouble = NULL; isint = false;})
		EQUAL (
		(DATE) => DATE
		|(lat_long) => currvalue = lat_long 
		| (NUMBER) => currvalue=datavalue
		| STRING)
		{ if (isint)
			{	nfreq = int(currvalue);}
		  else
		  	if (currdouble != NULL) *currdouble = currvalue;}
	;
	
option_list
	: (option)*
	;

//data_block
//	: KEYWORD
//	| KEYWORD option_list
//	| KEYWORD data_set
//	| KEYWORD option_list data_set
//	;
head_block
	: HEAD option_list
	;
info_block
	: ">INFO" option_list
	;
info_text
	: (~SPECIAL)* SPECIAL 
	;
emeas_block
	: ">EMEAS" option_list
	;
hmeas_block
	: ">HMEAS" option_list
	;
def_meas_section
	: EQUAL "DEFINEMEAS" option_list (emeas_block | hmeas_block)+
	;
spectrasect_block
	: SPECIAL EQUAL "SPECTRASET" option_list ("//" INT)? (NUMBER)+
	;
spectra_block
	: SPECIAL "SPECTRA" option_list ";" (datavalue)+
	;
spectra_section
	: spectrasect_block (spectra_block)*
	;
	
mtsect_block 
	: SPECIAL EQUAL "MTSECT" option_list
	;

mt_complex_data_block
{double ldnfreq; int lnfreq; double currvalue; int currindex = 0; gplib::pcompdata currvect;
	std::complex<double> localconv;}
	: 
		(">ZXXR" {currvect = &DataXX; localconv = convfactor;}
		|">ZXXI" {currvect = &DataXX; localconv = gplib::I * convfactor;}
		|">ZXYR" {currvect = &DataXY; localconv = convfactor;}
		|">ZXYI" {currvect = &DataXY; localconv = gplib::I * convfactor;}
		|">ZYXR" {currvect = &DataYX; localconv = convfactor;}
		|">ZYXI" {currvect = &DataYX; localconv = gplib::I * convfactor;}
		|">ZYYR" {currvect = &DataYY; localconv = convfactor;}
		|">ZYYI" {currvect = &DataYY; localconv = gplib::I * convfactor;}
		|">TXR.EXP" {currvect = &DataZX; localconv = convfactor;}
		|">TXI.EXP" {currvect = &DataZX; localconv = gplib::I * convfactor;}
		|">TYR.EXP" {currvect = &DataZY; localconv = convfactor;}
		|">TYI.EXP" {currvect = &DataZY; localconv = gplib::I * convfactor;})
		{if (currvect->empty()) currvect->assign(nfreq,0); }
		option_list SLASH SLASH ldnfreq=datavalue {lnfreq = int(ldnfreq);
		if (currvect->size() != lnfreq) {
		std::cout << nfreq << " " << lnfreq << std::endl;
		currvect->assign(lnfreq,0);}
		}  
		(currvalue=datavalue
			{currvect->at(currindex) += localconv * currvalue; currindex++;})+
	{}
	;
mt_real_data_block
{double ldnfreq; int lnfreq; double currvalue; int currindex = 0; gplib::prealdata currvect;}
	: 
		(">FREQ" {currvect = &frequency;}
		|">ZXXR.VAR" {currvect = &dDataXX;}
		|">ZXXI.VAR" {currvect = &dDataXX;}
		|">ZXX.VAR" {currvect = &dDataXX;}
		|">ZXYR.VAR" {currvect = &dDataXY;}
		|">ZXYI.VAR" {currvect = &dDataXY;}
		|">ZXY.VAR" {currvect = &dDataXY;}
		|">ZYXR.VAR" {currvect = &dDataYX;}
		|">ZYXI.VAR" {currvect = &dDataYX;}
		|">ZYX.VAR" {currvect = &dDataYX;}
		|">ZYYR.VAR" {currvect = &dDataYY;}
		|">ZYYI.VAR" {currvect = &dDataYY;}
		|">ZYY.VAR" {currvect = &dDataYY;}
		|">TXVAR.EXP" {currvect = &dDataZX;}
		|">TYVAR.EXP" {currvect = &dDataZY;}
		|">ZROT" {currvect = &rotangles;}
		| k:KEYWORD {currvect = NULL; }) 
		option_list SLASH SLASH ldnfreq=datavalue {lnfreq = int(ldnfreq); std::cout << lnfreq << std::endl; if (currvect != NULL) currvect->assign(lnfreq,0);}  
		(currvalue=datavalue
			{if (currvect != NULL)
			   {
				if ((currvect != &frequency) && (currvect != &rotangles)) 
					currvect->at(currindex) = sqrt(currvalue); 
				else
					currvect->at(currindex) = currvalue;
				}
				currindex++;})+
	;

//mt_data_block
//{double dnfreq; int nfreq; double currvalue; int currindex = 0;}
//	:  k:KEYWORD 
//		option_list SLASH SLASH dnfreq=datavalue {nfreq = int(dnfreq);}  
//		(currvalue=datavalue
//			)+
//	{std::cout << "Mt Data Block Keyword" << k->getText() << std::endl << std::flush;}
//	;

mt_section
	: mtsect_block ((COMMENT)? (mt_real_data_block|mt_complex_data_block))+
	;

end_block
	: ">END"
	;

edi_file
{
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
}
	:	head_block (info_block)? (info_text)? def_meas_section
	(spectra_section
	|mt_section)*
	(end_block)?
;

lat_long returns [double r]
{double v1=0; double v2=0; double v3=0; }
	:  v1=datavalue COLON v2=datavalue COLON v3=datavalue
	{ 
		if (v1 > 0)
			r = v1 + v2/60. + v3/3600.;
		else
			r = v1 - v2/60. - v3/3600.;
	}
	;		


datavalue returns [double r]
	: currvalue:NUMBER
	{gplib::convert(currvalue->getText(),r);}
	;

class EDILexer extends Lexer;
options{
	caseSensitive = false;
	k=10;
	charVocabulary = '\3' .. '\377';
	filter = true;
}
HEAD: ">head";

KEYWORD 
	options {testLiterals = true;
	}
	: SPECIAL STRING
	;

WS     :
    ( ' ' 
    | '\t' 
    | '\r' '\n' { newline(); } 
    | '\n' { newline();}
    ) 
    {_ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; } 
  ;

EQUAL
	: '='
	;
	
SPECIAL
	: '>'
	;
SLASH
	: '/'
	;	
EXKL
	: '!'
	;
COLON
	: ':'
	;
	
COMMENT
	: SPECIAL EXKL (~'!')* EXKL
	;	

NUMBER : ('+'|'-')?
		 	((REAL) =>
		 	REAL
		 	| INT) 
		 	(('e')('+'|'-')?INT)?
		 ;
		 	
STRING
	: LETTER (LEGAL_CHAR)*  | ('"' (LEGAL_CHAR|' ')* '"')  
	;


DATE
	: DIGIT DIGIT '/' DIGIT DIGIT '/' DIGIT DIGIT
	;
		

DIGIT
	:	'0'..'9'
	;	

protected
LETTER 
	: 'a'..'z'  
	; 

OTHER
	:  '\'' | '#' | '$' | '%' | '&' | '(' | ')'| '*' | '+' | ',' | '-' | '.' |
	  ';' | '<' |  '?' | '@' | '[' | ']'| '^'| '_' |  '{' | '|' | 
	'}' | '~' 
	;
protected

NONUMBER
	: "Nan" | "inf"
	;

LEGAL_CHAR
	: LETTER | DIGIT | OTHER | COLON | SLASH
	;

protected
INT
	: (DIGIT)+
	;
	
protected
SIGN
	: '+' | '-'
	;

protected
REAL:
	( '.' INT | INT '.' (INT)? )
;


//OPTION
//	: a:OPTION_NAME EQUAL b:OPTION_ARG
//	{std::cout << "Entered option: " <<a->getText() <<" Value: " << b->getText() << std::endl << std::flush;}
//	;
	
//protected
//OPTION_NAME
//	: LETTER (LETTER | DIGIT)*
//	;
	
//protected	
//OPTION_ARG
//	:	((NUMBER) => NUMBER
//		|(DATE) => DATE
//		|(LAT_LONG) => LAT_LONG
//		| STRING) 
//		{std::cout << "Found Option Argument" << std::endl << std::flush;}
//	;

