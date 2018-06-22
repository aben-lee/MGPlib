 #include <string>
 #include "SurfInvGaConfParser.hpp"
 #include "SurfInvGaConfLexer.hpp"
#include <fstream>
#include <algorithm>
 #include <CFatalException.h>

using namespace std;

 class SurfInvGaConf{
public: 
void GetData(std::ifstream &instream)
{
SurfInvGaConfLexer lexer(instream);
SurfInvGaConfParser parser(lexer);
parser.configfile();
verbose= parser.verbose;
usevrefmodel= parser.usevrefmodel;
vrefmodel= parser.vrefmodel;
backgroundmodel= parser.backgroundmodel;
fitexponent= parser.fitexponent;
popsize= parser.popsize;
inittemp= parser.inittemp;
coolingratio= parser.coolingratio;
generations= parser.generations;
mutationprob= parser.mutationprob;
crossoverprob= parser.crossoverprob;
poisson= parser.poisson;
threads= parser.threads;
errorlevel= parser.errorlevel;
gatype= parser.gatype;
outputbase= parser.outputbase;
inputdata= parser.inputdata;
annealinggeneration= parser.annealinggeneration;
elitist= parser.elitist;
thickbase.assign(parser.thickbase.size(),0);
copy(parser.thickbase.begin(),parser.thickbase.end(),thickbase.begin());
thickstep.assign(parser.thickstep.size(),0);
copy(parser.thickstep.begin(),parser.thickstep.end(),thickstep.begin());
thicksizes.assign(parser.thicksizes.size(),0);
copy(parser.thicksizes.begin(),parser.thicksizes.end(),thicksizes.begin());
svelbase.assign(parser.svelbase.size(),0);
copy(parser.svelbase.begin(),parser.svelbase.end(),svelbase.begin());
svelstep.assign(parser.svelstep.size(),0);
copy(parser.svelstep.begin(),parser.svelstep.end(),svelstep.begin());
svelsizes.assign(parser.svelsizes.size(),0);
copy(parser.svelsizes.begin(),parser.svelsizes.end(),svelsizes.begin());
weights.assign(parser.weights.size(),0);
copy(parser.weights.begin(),parser.weights.end(),weights.begin());
}

void GetData(std::string filename)
{
ifstream infile;
infile.open(filename.c_str());
infile.peek();
if (!infile)
  throw CFatalException("No Configurationfile found !");
 GetData(infile);infile.close();
}
void WriteData(std::ofstream &outstream)
{
outstream << "verbose"  << "=" ;
outstream << (verbose ? "true" : "false") << endl;
outstream << "usevrefmodel"  << "=" ;
outstream << (usevrefmodel ? "true" : "false") << endl;
outstream << "vrefmodel"  << "=" ;
outstream << vrefmodel << endl;
outstream << "backgroundmodel"  << "=" ;
outstream << backgroundmodel << endl;
outstream << "fitexponent"  << "=" ;
outstream << fitexponent << endl;
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
outstream << "poisson"  << "=" ;
outstream << poisson << endl;
outstream << "threads"  << "=" ;
outstream << threads << endl;
outstream << "errorlevel"  << "=" ;
outstream << errorlevel << endl;
outstream << "gatype"  << "=" ;
outstream << gatype << endl;
outstream << "outputbase"  << "=" ;
outstream << outputbase << endl;
outstream << "inputdata"  << "=" ;
outstream << inputdata << endl;
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

outstream << "svelbase"  << "=" ;
for (size_t i = 0; i < svelbase.size(); ++i)
  outstream << svelbase.at(i) << " ";
outstream << endl;

outstream << "svelstep"  << "=" ;
for (size_t i = 0; i < svelstep.size(); ++i)
  outstream << svelstep.at(i) << " ";
outstream << endl;

outstream << "svelsizes"  << "=" ;
for (size_t i = 0; i < svelsizes.size(); ++i)
  outstream << svelsizes.at(i) << " ";
outstream << endl;

outstream << "weights"  << "=" ;
for (size_t i = 0; i < weights.size(); ++i)
  outstream << weights.at(i) << " ";
outstream << endl;

}
void WriteData(std::string filename)
{
ofstream confout(filename.c_str());
WriteData(confout);
}

bool verbose;
bool usevrefmodel;
std::string vrefmodel;
std::string backgroundmodel;
int fitexponent;
int popsize;
double inittemp;
double coolingratio;
int generations;
double mutationprob;
double crossoverprob;
double poisson;
int threads;
double errorlevel;
std::string gatype;
std::string outputbase;
std::string inputdata;
int annealinggeneration;
bool elitist;
std::vector< double > thickbase;
std::vector< double > thickstep;
std::vector< int > thicksizes;
std::vector< double > svelbase;
std::vector< double > svelstep;
std::vector< int > svelsizes;
std::vector< double > weights;
SurfInvGaConf(std::string filename){GetData(filename);}
SurfInvGaConf(){}
};
