#include <iostream>
#include <string>
#include <numeric>
#include "TimeSeriesData.h"
#include "FatalException.h"
#include "statutils.h"
#include "Util.h"
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;
using namespace gplib;

string version = "$Id: rotts.cpp 1844 2010-04-12 11:34:25Z mmoorkamp $";

/*!
 * \addtogroup UtilProgs Utility Programs
 *@{
 * \file
 * Rotate a MT time-series so that the By component has a zero mean.
 */

int main(int argc, char *argv[])
  {
    string infilename;

    cout << "This is rotts: Rotate time series to a 0 mean By component"
        << endl << endl;
    cout << " Usage: rotts filename1" << endl;
    cout
        << " The output files will have the same name as the input files + .rot "
        << endl << endl;
    cout << " This is Version: " << version << endl << endl;

    try
    {

    if (argc == 2)
      {
        Document opt;
                char* buffer = argv[1];
                if(opt.Parse(buffer).HasParseError())
                {
                    FILE *fp = fopen(argv[1], "rb");
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
                    assert(opt.IsObject());

                    assert(opt.HasMember("infilename"));
                    assert(opt["infilename"].IsString());
                    infilename = opt["infilename"].GetString();

                }
                free(buffer);      // 释放json内存
      }
    else
      {
        infilename = AskFilename("Input Filename: ");

      }
    cout << "Rotating ... " << endl;
    TimeSeriesData Data1;
    try
      {
        Data1.GetData(infilename);

        double hymedian = Median(Data1.GetData().GetHy().GetData().begin(),
            Data1.GetData().GetHy().GetData().end());
        double hxmedian = Median(Data1.GetData().GetHx().GetData().begin(),
            Data1.GetData().GetHx().GetData().end());
        cout << "Hy Median before: " << hymedian << endl;

        double phi = hymedian / sqrt(std::pow(hxmedian, 2) + std::pow(hymedian, 2));
        cout << "Estimated angle: " << phi << endl;
        double newhx, newhy;
        double sinphi = sin(-phi);
        double cosphi = cos(-phi);
        const unsigned int ndata = Data1.GetData().GetHy().GetData().size();
        for (unsigned int i = 0; i < ndata; ++i)
          {
            newhx = cosphi * Data1.GetData().GetHx().GetData().at(i) + sinphi
                * Data1.GetData().GetHy().GetData().at(i);
            newhy = sinphi * Data1.GetData().GetHx().GetData().at(i) + cosphi
                * Data1.GetData().GetHy().GetData().at(i);
            Data1.GetData().GetHx().GetData().at(i) = newhx;
            Data1.GetData().GetHy().GetData().at(i) = newhy;
          }
        hymedian = Median(Data1.GetData().GetHy().GetData().begin(),
            Data1.GetData().GetHy().GetData().end());
        cout << "Hy Median after: " << hymedian << endl;
        Data1.WriteAsBirrp(infilename + ".rot");
      } catch (const FatalException &e)
      {
        cerr << e.what() << endl;
      }
    cout << "... done " << endl;
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

