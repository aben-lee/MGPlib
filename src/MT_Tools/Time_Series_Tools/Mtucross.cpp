#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "TimeSeriesData.h"
#include "miscfunc.h"
#include "Util.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: mtuadaptive.cpp 942 2007-04-08 16:13:01Z max $";

int main(int argc, char *argv[])
  {

    TimeSeriesData Data1, Data2;

    int index;
    string data1filename, data2filename;

    try
    {
        if( argc != 2 )
        {
    cout
        << "This is tscross: Calculate the 0 lag cross-correlation between components of two times series"
        << endl << endl;
    cout << " The program will ask for reference and input filename. " << endl;
    cout
        << " The cross correlation for each component is written to the screen."
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    data1filename = AskFilename("Data file 1: ");

    cout << "Component Index (Hx,Hy,Ex,Ey): ";
    cin >> index;

    data2filename = AskFilename("Data file 2: ");

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
                            assert(opt.IsObject());   // Document is a JSON value represents the root of DOM. Root can be either an object or array.

                            assert(opt.HasMember("data1filename"));
                            assert(opt["data1filename"].IsString());
                            data1filename = opt["data1filename"].GetString();

                            assert(opt.HasMember("data2filename"));
                            assert(opt["data2filename"].IsString());
                            data2filename = opt["data2filename"].GetString();


                            assert(opt["index"].IsNumber());
                            assert(opt["index"].IsInt());
                            index = opt["index"].GetInt();
                        }
                        free(buffer);
        }
    Data1.GetData(data1filename);
    Data2.GetData(data2filename);
    cout << "Data1 Start time: " << Data1.GetData().GetTime().front() << endl;
    cout << "Dat2 Start time: " << Data2.GetData().GetTime().front() << endl;
    if (Data1.GetData().GetTime().front() != Data2.GetData().GetTime().front())
      {
        cerr << "Time series not synchronized !" << endl;
        return 100;
      }

    int length = Data1.GetData().Size();

    cout << "Input End time: " << Data1.GetData().GetTime().back() << endl;
    cout << "Reference End time: " << Data2.GetData().GetTime().back() << endl;

    TimeSeriesComponent *RefComp;
    switch (index)
      {
    case 1:
      RefComp = &Data1.GetData().GetHx();
      break;
    case 2:
      RefComp = &Data1.GetData().GetHy();
      break;
    case 3:
      RefComp = &Data1.GetData().GetEx();
      break;
    case 4:
      RefComp = &Data1.GetData().GetEy();
      break;
    default:
      cerr << "Component index not valid !";
      return 100;
      break;
      }
    double cross = Cross(RefComp->GetData(), Data2.GetData().GetHx().GetData(),
        0, length);
    cout << "Cross Hx: " << cross << endl;
    cross = Cross(RefComp->GetData(), Data2.GetData().GetHy().GetData(), 0,
        length);
    cout << "Cross Hy: " << cross << endl;
    cross = Cross(RefComp->GetData(), Data2.GetData().GetEx().GetData(), 0,
        length);
    cout << "Cross Ex: " << cross << endl;
    cross = Cross(RefComp->GetData(), Data2.GetData().GetEy().GetData(), 0,
        length);
    cout << "Cross Ey: " << cross << endl;
  }

    catch( FatalException& fataException )
       {
           printf( "%s", fataException.what());
       }
       catch ( ... )
       {
           printf( "\nCaught unknown exception\n" );
       }

       cout << "End" << endl;
       system("pause");
       return 0;

}
