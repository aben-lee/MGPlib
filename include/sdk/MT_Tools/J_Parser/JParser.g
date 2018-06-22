header {
	#include <iostream>	
	#include <iomanip>
	#include <string>
	#include <cstdlib>
	#include "types.h"
}
options {
	language="Cpp";
	namespaceStd="std"; 
	namespaceAntlr="antlr";
}


class JParser extends Parser;
options {
	genHashLines = true;		// include line number information
	k=10;
	buildAST = false;
}
{
private:
	bool zsection;
	bool rsection;
	bool tsection;
	bool isstring;
	int currindex;
	gplib::pcompdata CurrentData;
	gplib::prealdata CurrentError;
	gplib::prealdata CurrentCoh;
	double convfactor;
	double *currdouble;
public:
	gplib::trealdata frequency;
	gplib::trealdata Rx;
	gplib::trealdata Ry;
	gplib::trealdata Rz;
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
    double misdat;
    std::string name;
    bool tassigned;
	bool zassigned;
	bool rassigned;
}
jfile
{
	zassigned = false;
	rassigned = false;
	tassigned = false;
	latitude = 0;
	longitude =0;
	elevation = 0;
	azimuth = 0;
	name = "default";
}
	: commentblock informationblock name=stringvalue
		 NEWLINE datablock EOF
	;
	
commentblock
	:   (COMMENT)*
	;
	
informationblock
	{double temp;}
	: ((AZIMUTH {currdouble = &azimuth; isstring = false; std::cout << "Reading Az. ";}
		| LATITUDE {currdouble = &latitude; isstring = false;std::cout << "Reading Lat. ";}
		| LONGITUDE {currdouble = &longitude; isstring = false;std::cout << "Reading Long. ";}
		| ELEVATION {currdouble = &elevation; isstring = false;std::cout << "Reading El. ";}
		| STATION {isstring = true;}
		| MISDAT {currdouble = &misdat; isstring = false;std::cout << "Reading MisDat. ";})
		EQUAL ({isstring}? name=stringvalue {std::cout << name << std::endl;}
			| temp=datavalue {*currdouble = temp;std::cout << temp << std::endl;})? NEWLINE)* 
	;
	


datablock
	: 
	(datasection)+
	;
datasection
{
	CurrentData = NULL;
	zsection = false;
	rsection = false;
	tsection = false;
	currindex =0;
	convfactor = 1/(1000 * gplib::mu);
	int size;}
	: ( ZXX {zsection = true; rsection = false; CurrentData=&DataXX;CurrentError=&dDataXX;CurrentCoh=&Rx;}
		| ZXY {zsection = true; rsection = false;CurrentData=&DataXY;CurrentError=&dDataXY;CurrentCoh=&Rx;} 
		| ZYX {zsection = true; rsection = false;CurrentData=&DataYX;CurrentError=&dDataYX;CurrentCoh=&Ry;}
		| ZYY {zsection = true; rsection = false;CurrentData=&DataYY;CurrentError=&dDataYY;CurrentCoh=&Ry;}
		| RXX {rsection = true; zsection = false;CurrentData=&DataXX;CurrentError=&dDataXX;}
		| RXY {rsection = true; zsection = false;CurrentData=&DataXY;CurrentError=&dDataXY;}
		| RYX {rsection = true; zsection = false;CurrentData=&DataYX;CurrentError=&dDataYX;}
		| RYY {rsection = true; zsection = false;CurrentData=&DataYY;CurrentError=&dDataYY;}
		| TZX {tsection = true; rsection = false; zsection = false; CurrentData=&DataZX;CurrentError=&dDataZX;CurrentCoh=&Rz;}
		| TZY {tsection = true; rsection = false; zsection = false; CurrentData=&DataZY;CurrentError=&dDataZY;CurrentCoh=&Rz;})
		(SI {convfactor = 1./(1000. * gplib::mu);}| FIELD{convfactor = 1;})? (UNITS)?
		NEWLINE size=datavalue {
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
				}
		NEWLINE ({zsection}? zdata| 
			({rsection}? rdata)|
			({tsection}? tdata))+
		;

zdata
	{double r1,r2,r3,r4,r5,r6=0;}
	: r1=datavalue r2=datavalue r3=datavalue r4=datavalue r5=datavalue (r6=datavalue)? NEWLINE
	{	if (r1 > 0)
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
		zassigned = true;}
	;
	
rdata
	{double r1,r2,r3,r4,r5,r6,r7,r8,r9=0;}
	: r1=datavalue r2=datavalue r3=datavalue r4=datavalue r5=datavalue 
	  r6=datavalue r7=datavalue r8=datavalue r9=datavalue  NEWLINE
	  {if (r1 > 0)
			frequency.at(currindex) = 1./r1;
		else
			frequency.at(currindex) = r1;
			
		double factor = sqrt(2 * gplib::PI * frequency.at(currindex)/gplib::mu);
		CurrentData->at(currindex) = factor * r2 *(cos(r3/180.0*gplib::PI)+ gplib::I*sin(r3/180.0*gplib::PI));
		CurrentError->at(currindex) = sqrt(pow(factor *cos(r3/180.0*gplib::PI)+ sin(r3/180.0*gplib::PI),2) 
		                + pow(factor*abs(r2)/180.0* gplib::PI,2) * (pow(cos(r3/180.0*gplib::PI),2)+ pow(sin(r3/180.0*gplib::PI),2)) );
	  	currindex++; 
	  	rassigned = true;}
	;


                    
tdata
	{double r1,r2,r3,r4,r5,r6;}
	: r1=datavalue r2=datavalue r3=datavalue r4=datavalue r5=datavalue (r6=datavalue)? NEWLINE
	{	if (r1 > 0)
			frequency.at(currindex) = 1./r1;
		else
			frequency.at(currindex) = r1;
			
		CurrentData->at(currindex) = r2 + gplib::I * r3;
		CurrentError->at(currindex) = r4;
		currindex++;
		tassigned = true;}
	;


datavalue returns [double r]
	: ( (UNDEF)=> UNDEF {r = -1000000000;}
		| currvalue:ENTRY {r = atof(currvalue->getText().c_str());})
	;

stringvalue returns [std::string r]
	: currvalue:ENTRY {r = currvalue->getText();}
	;

class JLexer extends Lexer;
options{
	caseSensitive = false;
	k=6;
	filter = false;
}
	UNDEF: "nan";
	ZXX: "zxx";
	ZXY: "zxy";
	ZYX: "zyx";
	ZYY: "zyy";
	RXX: "rxx";
	RXY: "rxy";
	RYX: "ryx";
	RYY: "ryy";
	TZX: "tzx";
	TZY: "tzy";
	UNITS: "units";
	SI: "s.i." ;
	FIELD: "field";

ELEVATION:
	">elevation";
LONGITUDE:
	">longitude";
LATITUDE:
	">latitude";
AZIMUTH:
	 ">azimuth";
STATION:
	 ">station";
MISDAT:
     ">misdat";
EQUAL:
	 '='
	 ;
protected
PLUS : '+';
protected
MINUS : '-';

WS     :
    (' ' 
    | '\t' 
    )+
    {_ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; } 
  ;
  


ENTRY
	: (PLUS|MINUS|CHAR|DIGIT)(CHAR|DIGIT|OTHER|PLUS|MINUS)* 
	;
	
COMMENT
	:	'#'
		(~('\n'|'\r'))* NEWLINE
		{
			//$setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP);
		}
	;	
NEWLINE
	: (   '\n'
		| '\r' '\n'
		)
	{ newline();}
	;

protected	
DIGIT
	:	'0'..'9'
	;
protected	
CHAR
	: ('a'..'z')
	;
protected
OTHER
	:  '\'' | '#' | '$' | '%' | '&' | '(' | ')'| '*' | ',' |  '.' |
	'/' | ':'| ';' | '<' |  '?' | '@' | '[' | ']'| '^'| '{' | '|' |
	'}' | '~' | '_'
	;
