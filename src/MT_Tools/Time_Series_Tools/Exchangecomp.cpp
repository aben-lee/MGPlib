#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "TimeSeriesData.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"

using namespace std;
using namespace gplib;
using namespace rapidjson;

string version = "$Id: exchangecomp.cpp 1816 2009-09-07 11:28:35Z mmoorkamp $";

int main(int argc, char *argv[])
  {
    TimeSeriesData TsData;
    string mtufilename, compfilename;
    int compindex;

    try
    {
    if( argc != 2 )
    {
    cout
        << "This is exchangecomp: Exchange one component of MTU file by contents of ascii file"
        << endl << endl;
    cout
        << " Output will have the same name as MTU Input with '.rep' appended "
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    cout << "Mtu filename: ";
    cin >> mtufilename;

    cout << "Component filename: ";
    cin >> compfilename;

    cout << "Enter target component number (Ex,Ey,Hx,Hy): ";
    cin >> compindex;

    }
    else
    {
        Document opt;
        char* buffer = argv[1];
        if(opt.Parse(buffer).HasParseError())
        {
            FILE *fp = fopen(argv[1], "r");
            if (!fp)
            {
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
            assert(opt.IsObject());   // Document is a JSON value represents the root of DOM. Root can be either an object or array.

            assert(opt.HasMember("mtufilename"));
            assert(opt["mtufilename"].IsString());
            mtufilename = opt["mtufilename"].GetString();
            assert(opt.HasMember("compfilename"));
            assert(opt["compfilename"].IsString());
            compfilename = opt["compfilename"].GetString();
            assert(opt["compindex"].IsInt());   // Number is a JSON type, but C++ needs more specific type.
            compindex = opt["compindex"].GetDouble(); // Alternative (double)document["lowfreq"]
        }
        free(buffer);      // 释放json内存
    }


    TsData.GetData(mtufilename);

    vector<double> compdata;
    ifstream compfile(compfilename.c_str());
    copy(istream_iterator<double> (compfile), istream_iterator<double> (),
        back_inserter(compdata));
    if (compdata.size() != TsData.GetData().GetEx().GetData().size())
      {
        std::cerr << "Number of points incompatible !";
        return 100;
      }

    std::vector<double>::iterator outit;
    switch (compindex)
      {
    case 1:
      outit = TsData.GetData().GetEx().GetData().begin();
      break;
    case 2:
      outit = TsData.GetData().GetEy().GetData().begin();
      break;
    case 3:
      outit = TsData.GetData().GetHx().GetData().begin();
      break;
    case 4:
      outit = TsData.GetData().GetHy().GetData().begin();
      break;
    default:
      std::cerr << "Invalid component selection !";
      return 100;
      break;
      }
    copy(compdata.begin(), compdata.end(), outit);
    TsData.WriteAsMtu(mtufilename + ".rep");
    }

    catch( FatalException& fataException )
        {
            printf( "%s", fataException.what());
        }
        catch ( ... )
        {
            printf( "\nCaught unknown exception\n" );
        }

    system("pause");
    return 0;
  }
