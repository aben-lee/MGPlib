#include "MtuFormat.h"
#include <iostream>
#include "Util.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;
using namespace gplib;

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Merge the electric field from one site with the magnetic field from another site. 
 */

int main(int argc, char *argv[])
  {
    string einfilename;
    string binfilename;
    string outfilename;

    MtuFormat ETsData, BTsData;

    try
    {
        if( argc != 2 )
        {

    einfilename = AskFilename("E Channel Filename: ");
    binfilename = AskFilename("B Channel Filename: ");
    outfilename = AskFilename("Output Filename: ");
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

                        assert(opt.HasMember("einfilename"));
                        assert(opt["einfilename"].IsString());
                        einfilename = opt["einfilename"].GetString();

                        assert(opt.HasMember("binfilename"));
                        assert(opt["binfilename"].IsString());
                        binfilename = opt["binfilename"].GetString();

                        assert(opt.HasMember("outfilename"));
                        assert(opt["outfilename"].IsString());
                        outfilename = opt["outfilename"].GetString();
                    }
                    free(buffer);      // 释放json内存
        }

    ETsData.GetData(einfilename.c_str());
    BTsData.GetData(binfilename.c_str());
    BTsData.GetEx() = ETsData.GetEx();
    BTsData.GetEy() = ETsData.GetEy();
    BTsData.WriteData(outfilename.c_str());
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
/*@}*/
