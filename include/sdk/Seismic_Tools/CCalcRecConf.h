 #include <string>
 #include "CCalcRecConfParser.hpp"
 #include "CCalcRecConfLexer.hpp"
 #include <fstream>
 #include <algorithm>
 #include <CFatalException.h>
 using namespace std;

 class CCalcRecConf{
public: 
void GetData(std::ifstream &instream)
{
ifstream infile;
infile.open(filename.c_str());
infile.peek();
if (!infile)
  throw CFatalException("No Configurationfile found !");
 GetData(infile);infile.close();
}
void GetData(std::string filename)
{
CCalcRecConfLexer lexer(instream);
CCalcRecConfParser parser(lexer);
parser.configfile();
cc= parser.cc;
sigma= parser.sigma;
shift= parser.shift;
recmethod= parser.recmethod;
normalize= parser.normalize;
}
void WriteData(std::ofstream &outstream)
{
outstream << "cc"  << "=" ;
outstream << cc << endl;
outstream << "sigma"  << "=" ;
outstream << sigma << endl;
outstream << "shift"  << "=" ;
outstream << shift << endl;
outstream << "recmethod"  << "=" ;
outstream << recmethod << endl;
outstream << "normalize"  << "=" ;
outstream << (normalize ? "true" : "false") << endl;
}
void WriteData(std::string filename)
{
ofstream confout(filename.c_str());
WriteData(confout);
}
double cc;
double sigma;
int shift;
std::string recmethod;
bool normalize;
CCalcRecConf(std::string filename){GetData(filename);}
CCalcRecConf(){}
};
