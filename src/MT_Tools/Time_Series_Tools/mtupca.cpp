#include "PCA.h"
#include "statutils.h"
#include "VecMat.h"
#include "TimeSeriesData.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace gplib;

int main()
  {
    TimeSeriesData TsData;
    std::string mtuname;

    std::cout << "Data file name: ";
    std::cin >> mtuname;

    TsData.GetData(mtuname);

    const size_t nobs = TsData.GetData().Size();
    const size_t nchan = 4;
    gplib::rmat input(nchan, nobs);
    gplib::cmat evec(nchan, nchan);
    gplib::cvec eval(nchan);

    for (unsigned int i = 0; i < nobs; ++i)
      {
        input(0, i) = TsData.GetData().GetEx().GetData().at(i);
        input(1, i) = TsData.GetData().GetEy().GetData().at(i);
        input(2, i) = TsData.GetData().GetHx().GetData().at(i);
        input(3, i) = TsData.GetData().GetHy().GetData().at(i);
      }

    PCA(input, evec, eval);

    gplib::cmat wmat(WhiteMat(evec, eval));
    std::cout << "pca evec: " << evec << std::endl;
    std::cout << "pca eval: " << eval << std::endl;
    std::cout << "pca WhM: " << wmat << std::endl;
    std::cout << "pca DeWhM: " << DeWhiteMat(evec, eval) << std::endl;

    gplib::cmat output(nchan, nobs);
    noalias(output) = prec_prod(wmat, input);
    for (unsigned int i = 0; i < nobs; ++i)
      {
        TsData.GetData().GetEx().GetData().at(i) = output(0, i).real();
        TsData.GetData().GetEy().GetData().at(i) = output(1, i).real();
        TsData.GetData().GetHx().GetData().at(i) = output(2, i).real();
        TsData.GetData().GetHy().GetData().at(i) = output(3, i).real();
      }
    TsData.WriteAsBirrp(mtuname + ".pca");
  }
