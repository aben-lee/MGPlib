header {
	#include <string>
	#include <vector>
	#include <iostream>
	#include <cstdlib>
}
options {
	language="Cpp";
	namespaceStd="std"; 
	namespaceAntlr="antlr";
}


class AnisoGAJointConfParser extends Parser;
options {
	genHashLines = true;		// include line number information
	k=10;
	buildAST = false;
}

{
private: 
int i; double dtemp; int itemp; std::string stemp; bool btemp;
public: 
bool verbose;
int mtfitexponent;
int popsize;
double inittemp;
double coolingratio;
int generations;
double mutationprob;
double crossoverprob;
int threads;
double starttime;
double endtime;
double tensorerror;
double reserror;
double phaseerror;
std::string gatype;
std::string outputbase;
std::string mode;
std::string mtfit;
std::string mtinputdata;
std::string ptensordata;
int annealinggeneration;
bool elitist;
std::vector< double > thickbase;
std::vector< double > thickstep;
std::vector< int > thicksizes;
std::vector< double > resbase;
std::vector< double > resstep;
std::vector< int > ressizes;
std::vector< double > velbase;
std::vector< double > velstep;
std::vector< int > velsizes;
std::vector< double > aresbase;
std::vector< double > aresstep;
std::vector< int > aressizes;
std::vector< double > avelbase;
std::vector< double > avelstep;
std::vector< int > avelsizes;
std::vector< double > strikebase;
std::vector< double > strikestep;
std::vector< int > strikesizes;
std::vector< double > dstrikebase;
std::vector< double > dstrikestep;
std::vector< int > dstrikesizes;
std::vector< double > weights;
double conddiffweight;
double anisotropyweight;
double strikediffweight;
double veldiffweight;
double anisovelweight;
double deltastrikediffweight;
double avelratio;
}
configentry 
:(
(VERBOSET)=>VERBOSET EQUAL verbose= boolvalue|
(MTFITEXPONENTT)=>MTFITEXPONENTT EQUAL (NUMBER)=> mtfitexponent= numvalue|
(POPSIZET)=>POPSIZET EQUAL (NUMBER)=> popsize= numvalue|
(INITTEMPT)=>INITTEMPT EQUAL (NUMBER)=> inittemp= numvalue|
(COOLINGRATIOT)=>COOLINGRATIOT EQUAL (NUMBER)=> coolingratio= numvalue|
(GENERATIONST)=>GENERATIONST EQUAL (NUMBER)=> generations= numvalue|
(MUTATIONPROBT)=>MUTATIONPROBT EQUAL (NUMBER)=> mutationprob= numvalue|
(CROSSOVERPROBT)=>CROSSOVERPROBT EQUAL (NUMBER)=> crossoverprob= numvalue|
(THREADST)=>THREADST EQUAL (NUMBER)=> threads= numvalue|
(STARTTIMET)=>STARTTIMET EQUAL (NUMBER)=> starttime= numvalue|
(ENDTIMET)=>ENDTIMET EQUAL (NUMBER)=> endtime= numvalue|
(TENSORERRORT)=>TENSORERRORT EQUAL (NUMBER)=> tensorerror= numvalue|
(RESERRORT)=>RESERRORT EQUAL (NUMBER)=> reserror= numvalue|
(PHASEERRORT)=>PHASEERRORT EQUAL (NUMBER)=> phaseerror= numvalue|
(GATYPET)=>GATYPET EQUAL (STRING)=> gatype= stringvalue|
(OUTPUTBASET)=>OUTPUTBASET EQUAL (STRING)=> outputbase= stringvalue|
(MODET)=>MODET EQUAL (STRING)=> mode= stringvalue|
(MTFITT)=>MTFITT EQUAL (STRING)=> mtfit= stringvalue|
(MTINPUTDATAT)=>MTINPUTDATAT EQUAL (STRING)=> mtinputdata= stringvalue|
(PTENSORDATAT)=>PTENSORDATAT EQUAL (STRING)=> ptensordata= stringvalue|
(ANNEALINGGENERATIONT)=>ANNEALINGGENERATIONT EQUAL (NUMBER)=> annealinggeneration= numvalue|
(ELITISTT)=>ELITISTT EQUAL elitist= boolvalue|
(THICKBASET)=>THICKBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < thickbase.size()) {thickbase.at(i) = dtemp;} else{thickbase.push_back(dtemp);}++i;})+|
(THICKSTEPT)=>THICKSTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < thickstep.size()) {thickstep.at(i) = dtemp;} else{thickstep.push_back(dtemp);}++i;})+|
(THICKSIZEST)=>THICKSIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < thicksizes.size()) {thicksizes.at(i) = itemp;} else{thicksizes.push_back(itemp);}++i;})+|
(RESBASET)=>RESBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < resbase.size()) {resbase.at(i) = dtemp;} else{resbase.push_back(dtemp);}++i;})+|
(RESSTEPT)=>RESSTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < resstep.size()) {resstep.at(i) = dtemp;} else{resstep.push_back(dtemp);}++i;})+|
(RESSIZEST)=>RESSIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < ressizes.size()) {ressizes.at(i) = itemp;} else{ressizes.push_back(itemp);}++i;})+|
(VELBASET)=>VELBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < velbase.size()) {velbase.at(i) = dtemp;} else{velbase.push_back(dtemp);}++i;})+|
(VELSTEPT)=>VELSTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < velstep.size()) {velstep.at(i) = dtemp;} else{velstep.push_back(dtemp);}++i;})+|
(VELSIZEST)=>VELSIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < velsizes.size()) {velsizes.at(i) = itemp;} else{velsizes.push_back(itemp);}++i;})+|
(ARESBASET)=>ARESBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < aresbase.size()) {aresbase.at(i) = dtemp;} else{aresbase.push_back(dtemp);}++i;})+|
(ARESSTEPT)=>ARESSTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < aresstep.size()) {aresstep.at(i) = dtemp;} else{aresstep.push_back(dtemp);}++i;})+|
(ARESSIZEST)=>ARESSIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < aressizes.size()) {aressizes.at(i) = itemp;} else{aressizes.push_back(itemp);}++i;})+|
(AVELBASET)=>AVELBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < avelbase.size()) {avelbase.at(i) = dtemp;} else{avelbase.push_back(dtemp);}++i;})+|
(AVELSTEPT)=>AVELSTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < avelstep.size()) {avelstep.at(i) = dtemp;} else{avelstep.push_back(dtemp);}++i;})+|
(AVELSIZEST)=>AVELSIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < avelsizes.size()) {avelsizes.at(i) = itemp;} else{avelsizes.push_back(itemp);}++i;})+|
(STRIKEBASET)=>STRIKEBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < strikebase.size()) {strikebase.at(i) = dtemp;} else{strikebase.push_back(dtemp);}++i;})+|
(STRIKESTEPT)=>STRIKESTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < strikestep.size()) {strikestep.at(i) = dtemp;} else{strikestep.push_back(dtemp);}++i;})+|
(STRIKESIZEST)=>STRIKESIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < strikesizes.size()) {strikesizes.at(i) = itemp;} else{strikesizes.push_back(itemp);}++i;})+|
(DSTRIKEBASET)=>DSTRIKEBASET EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < dstrikebase.size()) {dstrikebase.at(i) = dtemp;} else{dstrikebase.push_back(dtemp);}++i;})+|
(DSTRIKESTEPT)=>DSTRIKESTEPT EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < dstrikestep.size()) {dstrikestep.at(i) = dtemp;} else{dstrikestep.push_back(dtemp);}++i;})+|
(DSTRIKESIZEST)=>DSTRIKESIZEST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (itemp = numvalue { if (i < dstrikesizes.size()) {dstrikesizes.at(i) = itemp;} else{dstrikesizes.push_back(itemp);}++i;})+|
(WEIGHTST)=>WEIGHTST EQUAL {i = 0; dtemp = 0; stemp = ""; btemp = false;}
(NUMBER)=> (dtemp = numvalue { if (i < weights.size()) {weights.at(i) = dtemp;} else{weights.push_back(dtemp);}++i;})+|
(CONDDIFFWEIGHTT)=>CONDDIFFWEIGHTT EQUAL (NUMBER)=> conddiffweight= numvalue|
(ANISOTROPYWEIGHTT)=>ANISOTROPYWEIGHTT EQUAL (NUMBER)=> anisotropyweight= numvalue|
(STRIKEDIFFWEIGHTT)=>STRIKEDIFFWEIGHTT EQUAL (NUMBER)=> strikediffweight= numvalue|
(VELDIFFWEIGHTT)=>VELDIFFWEIGHTT EQUAL (NUMBER)=> veldiffweight= numvalue|
(ANISOVELWEIGHTT)=>ANISOVELWEIGHTT EQUAL (NUMBER)=> anisovelweight= numvalue|
(DELTASTRIKEDIFFWEIGHTT)=>DELTASTRIKEDIFFWEIGHTT EQUAL (NUMBER)=> deltastrikediffweight= numvalue|
(AVELRATIOT)=>AVELRATIOT EQUAL (NUMBER)=> avelratio= numvalue);

configfile {
verbose = false;
mtfitexponent = 2;
conddiffweight = 1;
anisotropyweight = 1;
strikediffweight = 1;
veldiffweight = 1;
anisovelweight = 1;
deltastrikediffweight = 1;
}
	: (configentry (COMMENT)?)+ (COMMENT)* EOF
	;
	
numvalue returns [double r]
	: currvalue:NUMBER {r = atof(currvalue->getText().c_str());}
	;

boolvalue returns [bool r]
	: (TRUE {r = true;} | FALSE {r = false;})
	;
	
stringvalue returns [std::string r]
	: currvalue:STRING {r = currvalue->getText();}
	;
	

class AnisoGAJointConfLexer extends Lexer;
options{
	caseSensitive = false;
	k=10;
	filter = false;
}

EQUAL : '=' ;
TRUE  : "true";
FALSE : "false";
 
WS     :
    (' ' 
    | NEWLINE
    | '\t' 
    )+
    {_ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; } 
  ;
  
STRING
	options {testLiterals = true;}:
	CHAR (CHAR|DIGIT|OTHER)*
	;

NUMBER : ('+'|'-')?
		 	((REAL) =>
		 	REAL
		 	| INT) 
		 	(('e')('+'|'-')?INT)?;

COMMENT
	:	'/''/'
		(~('\n'|'\r'))* NEWLINE
		{
			$setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP);
		}
	;	
protected
NEWLINE
	: (   '\n'
		| '\r' '\n'
		)
	{ newline();}
	;

protected
REAL:
	( '.' INT | INT '.' (INT)? )
;
protected
INT
	: (DIGIT)+
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
	:  '\'' | '#' | '$' | '%' | '&' | '(' | ')'| '*' | '+' | ',' | '-' | '.' |
	'/' | ':'| ';' | '<' |  '?' | '@' | '[' | ']'| '^'| '_' |  '{' | '|' |
	'}' | '~'
	;
VERBOSET: "verbose";
MTFITEXPONENTT: "mtfitexponent";
POPSIZET: "popsize";
INITTEMPT: "inittemp";
COOLINGRATIOT: "coolingratio";
GENERATIONST: "generations";
MUTATIONPROBT: "mutationprob";
CROSSOVERPROBT: "crossoverprob";
THREADST: "threads";
STARTTIMET: "starttime";
ENDTIMET: "endtime";
TENSORERRORT: "tensorerror";
RESERRORT: "reserror";
PHASEERRORT: "phaseerror";
GATYPET: "gatype";
OUTPUTBASET: "outputbase";
MODET: "mode";
MTFITT: "mtfit";
MTINPUTDATAT: "mtinputdata";
PTENSORDATAT: "ptensordata";
ANNEALINGGENERATIONT: "annealinggeneration";
ELITISTT: "elitist";
THICKBASET: "thickbase";
THICKSTEPT: "thickstep";
THICKSIZEST: "thicksizes";
RESBASET: "resbase";
RESSTEPT: "resstep";
RESSIZEST: "ressizes";
VELBASET: "velbase";
VELSTEPT: "velstep";
VELSIZEST: "velsizes";
ARESBASET: "aresbase";
ARESSTEPT: "aresstep";
ARESSIZEST: "aressizes";
AVELBASET: "avelbase";
AVELSTEPT: "avelstep";
AVELSIZEST: "avelsizes";
STRIKEBASET: "strikebase";
STRIKESTEPT: "strikestep";
STRIKESIZEST: "strikesizes";
DSTRIKEBASET: "dstrikebase";
DSTRIKESTEPT: "dstrikestep";
DSTRIKESIZEST: "dstrikesizes";
WEIGHTST: "weights";
CONDDIFFWEIGHTT: "conddiffweight";
ANISOTROPYWEIGHTT: "anisotropyweight";
STRIKEDIFFWEIGHTT: "strikediffweight";
VELDIFFWEIGHTT: "veldiffweight";
ANISOVELWEIGHTT: "anisovelweight";
DELTASTRIKEDIFFWEIGHTT: "deltastrikediffweight";
AVELRATIOT: "avelratio";
