#ifndef APPLYFILTER_H_
#define APPLYFILTER_H_

#include "AdaptiveFilter.h"
#include "TimeSeriesComponent.h"
#include <boost/shared_ptr.hpp>
#include <vector>
#include "FatalException.h"
#include <boost/progress.hpp>

namespace gplib
  {
    /** \addtogroup sigproc Signal processing methods */
    /* @{ */

    //! Apply an adaptive filter to a time-series
    class ApplyFilter
      {
    private:
      bool showprogress;
      bool wanthistory;
      int shift;
      AdaptiveFilter &Filter;
      int weightsaveintervall;
      std::vector<gplib::rvec> WeightHistory;
      std::vector<TimeSeriesComponent*> InputChannels;
      std::vector<TimeSeriesComponent*> RefChannels;
      std::vector<boost::shared_ptr<TimeSeriesComponent> > OutChannels;
      std::vector<std::vector<double> > EpsValues;
    public:
      //! Do we want visual feedback of the progess on the screen, if yes draw a simple progress indicator in text mode
      void ShowProgress(const bool what)
        {
          showprogress = what;
        }
      //! Return a matrix with the values of the weights at iterations specified by weightsaveintervall
      gplib::rmat GetWeightHistory()
      {
        if (WeightHistory.empty())
          throw FatalException("Trying to access empty Weight History");
        const size_t xsize = WeightHistory.size();
        const size_t ysize = WeightHistory.front().size();
        gplib::rmat temp(xsize, ysize);
        for (size_t i = 0; i < xsize; ++i)
          for (size_t j = 0; j < ysize; ++j)
            temp(i, j) = WeightHistory.at(i)(j);
        return temp;
      }
      //! Set the distance between iterations at which the weights are saved
      void SetWeightSaveIntervall(const int intervall)
        {
          weightsaveintervall = intervall;
        }
      //! Return the vector of output channels
      const std::vector<boost::shared_ptr<TimeSeriesComponent> > &GetOutChannels()
        {
          return OutChannels;
        }
      //! Return the vector of channel approximation errors
      const std::vector<std::vector<double> > &GetEpsValues()
        {
          return EpsValues;
        }
      //! Set the shift between the input time series and the reference time series
      void SetShift(const int theshift)
        {
          shift = theshift;
        }
      //! Add an input channel to the filter
      void AddInputChannel(TimeSeriesComponent &Channel)
      {
        if (!InputChannels.empty() && Channel.GetData().size()
            != InputChannels.front()->GetData().size())
          throw FatalException(
              "Input channel has incompatible size to first channel");
        InputChannels.push_back(&Channel);
      }

      //! Add a reference channel to the filter, some AdaptiveFilter objects require only one reference
      void AddReferenceChannel(TimeSeriesComponent &Channel)
      {
        if (RefChannels.size() >= Filter.GetOutputLength()) // if we already have enough reference channels
          throw FatalException(
              "Trying to add more reference channels than  permitted by Adaptive Filter class");
        if (!RefChannels.empty() && Channel.GetData().size()
            != RefChannels.front()->GetData().size())
          throw FatalException(
              "Ref channel has incompatible size to first channel");
        RefChannels.push_back(&Channel);
      }

      //! Filter the input channels with the current settings
      void FilterData()
      {
        const int ninputchannels = InputChannels.size();
        const int datalength = InputChannels.front()->GetData().size();
        const int inputsize = Filter.GetInputLength();
        const int outputsize = Filter.GetOutputLength();
        const int pointsperchannel = inputsize / ninputchannels;

        gplib::rvec currentinput(inputsize), currdesired(outputsize), currout(
            outputsize);
        //std::vector<double> eps;
        //EpsValues.assign(outputsize,eps);

        if (!EpsValues.empty()) // if we have run this routine before
          {
            EpsValues.clear(); //clear errors
            OutChannels.clear(); // and output channels, but not weights
          }

        for (int i = 0; i < outputsize; ++i)
          {
            std::vector<double> temp;
            EpsValues.push_back(temp);
            OutChannels.push_back(boost::shared_ptr<TimeSeriesComponent>(
                new TimeSeriesComponent));
            OutChannels.at(i)->GetData().reserve(
                RefChannels.at(i)->GetData().size());
            EpsValues.at(i).reserve(RefChannels.at(i)->GetData().size());
            //if (shift > 2)
            OutChannels.at(i)->GetData().insert(
                OutChannels.at(i)->GetData().begin(), shift, 0.0);
            EpsValues.at(i).insert(EpsValues.at(i).begin(), shift, 0.0);
          }
        const int maxindex = datalength - pointsperchannel - shift;
        boost::progress_display *progressbar = NULL;
        if (showprogress) // the constructor already displays something, so we use a pointer and only construct when needed
          {
            progressbar = new boost::progress_display(maxindex); // init progress bar
          }
        for (int i = 0; i < maxindex; ++i)
          {

            for (int j = 0; j < ninputchannels; ++j)
              {
                copy(InputChannels.at(j)->GetData().begin() + i,
                    InputChannels.at(j)->GetData().begin() + pointsperchannel
                        + i, currentinput.begin() + j * pointsperchannel);
              }
            for (int j = 0; j < outputsize; ++j)
              currdesired(j) = RefChannels.at(j)->GetData().at(i + shift);

            Filter.CalcOutput(currentinput, currout);
            Filter.AdaptFilter(currentinput, currdesired);
            if (showprogress)
              {
                ++(*progressbar); // make sure progress bar progresses
              }
            for (int j = 0; j < outputsize; ++j)
              {
                OutChannels.at(j)->GetData().push_back(currout(j));
              }
            if (wanthistory && ((i - shift) % weightsaveintervall == 0))
              {
                WeightHistory.push_back(Filter.GetWeightsAsVector());
              }
            for (int j = 0; j < outputsize; ++j)
              {
                EpsValues.at(j).push_back(Filter.GetEpsilon()(j));
              }
          } // end of main loop
        for (int i = 0; i < outputsize; ++i)
          {
            OutChannels.at(i)->GetData().insert(
                OutChannels.at(i)->GetData().end(), pointsperchannel, 0.0);
            EpsValues.at(i).insert(EpsValues.at(i).end(), pointsperchannel, 0.0);
          }
        delete progressbar;
      }
      //! The constructor takes the AdaptiveFilter object that determines how the filtering is done, if keephistory is true we store the weights
      ApplyFilter(AdaptiveFilter &TheFilter, bool keephistory = false):
          showprogress(false), wanthistory(keephistory), shift(0),
              Filter(TheFilter), weightsaveintervall(TheFilter.GetOutputLength())
          {
          }
      virtual ~ApplyFilter();

      };
  /* @} */
  }
#endif /*APPLYFILTER_H_*/
