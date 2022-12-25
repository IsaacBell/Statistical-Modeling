#ifndef _TPF_Services_DataService_HPP_
#define _TPF_Services_DataService_HPP_

#include <memory>
// #include <Common/config.h>

namespace TPF
{
  // void MarketDataService(std::shared_ptr<marketdatafeed>, int32_t);
  void DataBoardService();
  void BarAggregatorService();
  void TickRecordingService();
  void TickReplayService(const std::string &filetoreplay, int32_t tickinterval = 0);
}

#endif