 #include <string>
 #include "AnisoGAJointConfParser.hpp"
 #include "AnisoGAJointConfLexer.hpp"
 #include <fstream>
 #include <algorithm>
 #include <CFMException.h>
using namespace std;
 class AnisoGAJointConf{
public: 
void GetData(std::ifstream &instream)
 {
 AnisoGAJointConfLexer lexer(instream);
 AnisoGAJointConfParser parser(lexer);
 parser.configfile();
 verbose= parser.verbose;
 mtfitexponent= parser.mtfitexponent;
 popsize= parser.popsize;
 inittemp= parser.inittemp;
 coolingratio= parser.coolingratio;
 generations= parser.generations;
 mutationprob= parser.mutationprob;
 crossoverprob= parser.crossoverprob;
 threads= parser.threads;
 starttime= parser.starttime;
 endtime= parser.endtime;
 tensorerror= parser.tensorerror;
 reserror= parser.reserror;
 phaseerror= parser.phaseerror;
 gatype= parser.gatype;
 outputbase= parser.outputbase;
 mode= parser.mode;
 mtfit= parser.mtfit;
 mtinputdata= parser.mtinputdata;
 ptensordata= parser.ptensordata;
 annealinggeneration= parser.annealinggeneration;
 elitist= parser.elitist;
 thickbase.assign(parser.thickbase.size(),0);
 copy(parser.thickbase.begin(),parser.thickbase.end(),thickbase.begin());
 thickstep.assign(parser.thickstep.size(),0);
 copy(parser.thickstep.begin(),parser.thickstep.end(),thickstep.begin());
 thicksizes.assign(parser.thicksizes.size(),0);
 copy(parser.thicksizes.begin(),parser.thicksizes.end(),thicksizes.begin());
 resbase.assign(parser.resbase.size(),0);
 copy(parser.resbase.begin(),parser.resbase.end(),resbase.begin());
 resstep.assign(parser.resstep.size(),0);
 copy(parser.resstep.begin(),parser.resstep.end(),resstep.begin());
 ressizes.assign(parser.ressizes.size(),0);
 copy(parser.ressizes.begin(),parser.ressizes.end(),ressizes.begin());
 velbase.assign(parser.velbase.size(),0);
 copy(parser.velbase.begin(),parser.velbase.end(),velbase.begin());
 velstep.assign(parser.velstep.size(),0);
 copy(parser.velstep.begin(),parser.velstep.end(),velstep.begin());
 velsizes.assign(parser.velsizes.size(),0);
 copy(parser.velsizes.begin(),parser.velsizes.end(),velsizes.begin());
 aresbase.assign(parser.aresbase.size(),0);
 copy(parser.aresbase.begin(),parser.aresbase.end(),aresbase.begin());
 aresstep.assign(parser.aresstep.size(),0);
 copy(parser.aresstep.begin(),parser.aresstep.end(),aresstep.begin());
 aressizes.assign(parser.aressizes.size(),0);
 copy(parser.aressizes.begin(),parser.aressizes.end(),aressizes.begin());
 avelbase.assign(parser.avelbase.size(),0);
 copy(parser.avelbase.begin(),parser.avelbase.end(),avelbase.begin());
 avelstep.assign(parser.avelstep.size(),0);
 copy(parser.avelstep.begin(),parser.avelstep.end(),avelstep.begin());
 avelsizes.assign(parser.avelsizes.size(),0);
 copy(parser.avelsizes.begin(),parser.avelsizes.end(),avelsizes.begin());
 strikebase.assign(parser.strikebase.size(),0);
 copy(parser.strikebase.begin(),parser.strikebase.end(),strikebase.begin());
 strikestep.assign(parser.strikestep.size(),0);
 copy(parser.strikestep.begin(),parser.strikestep.end(),strikestep.begin());
 strikesizes.assign(parser.strikesizes.size(),0);
 copy(parser.strikesizes.begin(),parser.strikesizes.end(),strikesizes.begin());
 dstrikebase.assign(parser.dstrikebase.size(),0);
 copy(parser.dstrikebase.begin(),parser.dstrikebase.end(),dstrikebase.begin());
 dstrikestep.assign(parser.dstrikestep.size(),0);
 copy(parser.dstrikestep.begin(),parser.dstrikestep.end(),dstrikestep.begin());
 dstrikesizes.assign(parser.dstrikesizes.size(),0);
 copy(parser.dstrikesizes.begin(),parser.dstrikesizes.end(),dstrikesizes.begin());
 weights.assign(parser.weights.size(),0);
 copy(parser.weights.begin(),parser.weights.end(),weights.begin());
 conddiffweight= parser.conddiffweight;
 anisotropyweight= parser.anisotropyweight;
 strikediffweight= parser.strikediffweight;
 veldiffweight= parser.veldiffweight;
 anisovelweight= parser.anisovelweight;
 deltastrikediffweight= parser.deltastrikediffweight;
 avelratio= parser.avelratio;
 }
void GetData(std::string filename)
 {
 ifstream infile;
 infile.open(filename.c_str());
 infile.peek();
 if (!infile)
   throw CFMException("No Configurationfile found !");
  GetData(infile);infile.close();
 }
void WriteData(std::ofstream &outstream)
{
outstream << "verbose"  << "=" ;
outstream << (verbose ? "true" : "false") << endl;
outstream << "mtfitexponent"  << "=" ;
outstream << mtfitexponent << endl;
outstream << "popsize"  << "=" ;
outstream << popsize << endl;
outstream << "inittemp"  << "=" ;
outstream << inittemp << endl;
outstream << "coolingratio"  << "=" ;
outstream << coolingratio << endl;
outstream << "generations"  << "=" ;
outstream << generations << endl;
outstream << "mutationprob"  << "=" ;
outstream << mutationprob << endl;
outstream << "crossoverprob"  << "=" ;
outstream << crossoverprob << endl;
outstream << "threads"  << "=" ;
outstream << threads << endl;
outstream << "starttime"  << "=" ;
outstream << starttime << endl;
outstream << "endtime"  << "=" ;
outstream << endtime << endl;
outstream << "tensorerror"  << "=" ;
outstream << tensorerror << endl;
outstream << "reserror"  << "=" ;
outstream << reserror << endl;
outstream << "phaseerror"  << "=" ;
outstream << phaseerror << endl;
outstream << "gatype"  << "=" ;
outstream << gatype << endl;
outstream << "outputbase"  << "=" ;
outstream << outputbase << endl;
outstream << "mode"  << "=" ;
outstream << mode << endl;
outstream << "mtfit"  << "=" ;
outstream << mtfit << endl;
outstream << "mtinputdata"  << "=" ;
outstream << mtinputdata << endl;
outstream << "ptensordata"  << "=" ;
outstream << ptensordata << endl;
outstream << "annealinggeneration"  << "=" ;
outstream << annealinggeneration << endl;
outstream << "elitist"  << "=" ;
outstream << (elitist ? "true" : "false") << endl;
outstream << "thickbase"  << "=" ;
for (size_t i = 0; i < thickbase.size(); ++i)
  outstream << thickbase.at(i) << " ";
outstream << endl;

outstream << "thickstep"  << "=" ;
for (size_t i = 0; i < thickstep.size(); ++i)
  outstream << thickstep.at(i) << " ";
outstream << endl;

outstream << "thicksizes"  << "=" ;
for (size_t i = 0; i < thicksizes.size(); ++i)
  outstream << thicksizes.at(i) << " ";
outstream << endl;

outstream << "resbase"  << "=" ;
for (size_t i = 0; i < resbase.size(); ++i)
  outstream << resbase.at(i) << " ";
outstream << endl;

outstream << "resstep"  << "=" ;
for (size_t i = 0; i < resstep.size(); ++i)
  outstream << resstep.at(i) << " ";
outstream << endl;

outstream << "ressizes"  << "=" ;
for (size_t i = 0; i < ressizes.size(); ++i)
  outstream << ressizes.at(i) << " ";
outstream << endl;

outstream << "velbase"  << "=" ;
for (size_t i = 0; i < velbase.size(); ++i)
  outstream << velbase.at(i) << " ";
outstream << endl;

outstream << "velstep"  << "=" ;
for (size_t i = 0; i < velstep.size(); ++i)
  outstream << velstep.at(i) << " ";
outstream << endl;

outstream << "velsizes"  << "=" ;
for (size_t i = 0; i < velsizes.size(); ++i)
  outstream << velsizes.at(i) << " ";
outstream << endl;

outstream << "aresbase"  << "=" ;
for (size_t i = 0; i < aresbase.size(); ++i)
  outstream << aresbase.at(i) << " ";
outstream << endl;

outstream << "aresstep"  << "=" ;
for (size_t i = 0; i < aresstep.size(); ++i)
  outstream << aresstep.at(i) << " ";
outstream << endl;

outstream << "aressizes"  << "=" ;
for (size_t i = 0; i < aressizes.size(); ++i)
  outstream << aressizes.at(i) << " ";
outstream << endl;

outstream << "avelbase"  << "=" ;
for (size_t i = 0; i < avelbase.size(); ++i)
  outstream << avelbase.at(i) << " ";
outstream << endl;

outstream << "avelstep"  << "=" ;
for (size_t i = 0; i < avelstep.size(); ++i)
  outstream << avelstep.at(i) << " ";
outstream << endl;

outstream << "avelsizes"  << "=" ;
for (size_t i = 0; i < avelsizes.size(); ++i)
  outstream << avelsizes.at(i) << " ";
outstream << endl;

outstream << "strikebase"  << "=" ;
for (size_t i = 0; i < strikebase.size(); ++i)
  outstream << strikebase.at(i) << " ";
outstream << endl;

outstream << "strikestep"  << "=" ;
for (size_t i = 0; i < strikestep.size(); ++i)
  outstream << strikestep.at(i) << " ";
outstream << endl;

outstream << "strikesizes"  << "=" ;
for (size_t i = 0; i < strikesizes.size(); ++i)
  outstream << strikesizes.at(i) << " ";
outstream << endl;

outstream << "dstrikebase"  << "=" ;
for (size_t i = 0; i < dstrikebase.size(); ++i)
  outstream << dstrikebase.at(i) << " ";
outstream << endl;

outstream << "dstrikestep"  << "=" ;
for (size_t i = 0; i < dstrikestep.size(); ++i)
  outstream << dstrikestep.at(i) << " ";
outstream << endl;

outstream << "dstrikesizes"  << "=" ;
for (size_t i = 0; i < dstrikesizes.size(); ++i)
  outstream << dstrikesizes.at(i) << " ";
outstream << endl;

outstream << "weights"  << "=" ;
for (size_t i = 0; i < weights.size(); ++i)
  outstream << weights.at(i) << " ";
outstream << endl;

outstream << "conddiffweight"  << "=" ;
outstream << conddiffweight << endl;
outstream << "anisotropyweight"  << "=" ;
outstream << anisotropyweight << endl;
outstream << "strikediffweight"  << "=" ;
outstream << strikediffweight << endl;
outstream << "veldiffweight"  << "=" ;
outstream << veldiffweight << endl;
outstream << "anisovelweight"  << "=" ;
outstream << anisovelweight << endl;
outstream << "deltastrikediffweight"  << "=" ;
outstream << deltastrikediffweight << endl;
outstream << "avelratio"  << "=" ;
outstream << avelratio << endl;
}
void WriteData(std::string filename);
{
ofstream confout(filename.c_str())
WriteData(confout);}
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
AnisoGAJointConf(std::string filename){GetData(filename);}
AnisoGAJointConf(){}
};
