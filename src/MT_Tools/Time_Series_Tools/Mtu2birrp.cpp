#include <iostream>
#include <string>
#include "Util.h"
#include "TimeSeriesData.h"
#include "FatalException.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: mtu2birrp.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Converts MTU-Format and other MT data into Birrp Ascii format for processing with the birrp code 
 * (basically just 5 ascii columns with the data).  
 */

void WriteInfoAndAsk(string &infilename, string &outfilename)
  {
    cout << "This is mtu2birrp: Convert Phoenix time series to birrp-ascii"
        << endl << endl;
    cout << "Usage: mtu2birrp infilename outfilename" << endl;
    cout << "Ending .asc will be automatically assigned to outfilename" << endl
        << endl;
    cout << "This is Version: " << version << endl << endl;
    infilename = AskFilename("Input Filename: ");
    cout << "Birrp-Ascii-Filename without extension: ";
    cin >> outfilename;
  }
int main(int argc, char *argv[])
  {
    string infilename, outfilename;

    if(argc != 2)
    {
        WriteInfoAndAsk(infilename, outfilename);
    }
    else
    {
        Document opt;
                    char* buffer = argv[1];
                    if(opt.Parse(buffer).HasParseError())
                    {
                        FILE *fp = fopen(argv[1], "r");
                        if (!fp) {
                            printf("file '%s' not found\n", argv[1]);
                            return -1;
                        }

                        fseek(fp, 0, SEEK_END);
                        size_t filesize = (size_t)ftell(fp);
                        fseek(fp, 0, SEEK_SET);
                        buffer = (char*)malloc(filesize + 1);
                        size_t readLength = fread(buffer, 1, filesize, fp);
                        buffer[readLength] = '\0';
                        fclose(fp);

                        opt.Parse(buffer);

                    }

                    {

                        printf("Input JSON is valid.\n");
                        printf("\nAccess values in document:\n");
                        assert(opt.IsObject());

                        assert(opt.HasMember("infilename"));
                        assert(opt["infilename"].IsString());
                        infilename = opt["infilename"].GetString();

                        assert(opt.HasMember("outfilename"));
                        assert(opt["outfilename"].IsString());
                        outfilename = opt["outfilename"].GetString();

    }
                    free(buffer);      // 释放json内存

    }

    TimeSeriesData Data;
    try
      {
        Data.GetData(infilename);
        Data.WriteAsBirrp(outfilename);
      } catch (const FatalException &e)
      {
        cerr << e.what() << endl;
      }
  }
/*@}*/
