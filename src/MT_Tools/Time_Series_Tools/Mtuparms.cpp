#include "TimeSeriesData.h"
#include <iostream>
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

int main( int argc, char *argv[] )
  {
    string infilename;
    TimeSeriesData TsData;

    try
    {
        if(argc != 2)
        {
            cout << "Filename: ";
            cin >> infilename;
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

                        }
                        free(buffer);      // 释放json内存
        }

    TsData.GetData(infilename);
    cout << "Number of points: " << TsData.GetData().GetEx().GetData().size()
        << endl;

    }

    catch( FatalException& fataException )
        {
            printf( "%s", fataException.what());
        }
        catch ( ... )
        {
            printf( "\nCaught unknown exception\n" );
        }
  }
