#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "tick_replay_service.hpp"

namespace TPF
{
  TickReplayService::TickReplayService(const std::string &filetoreplay, int32_t tickinterval)
      : filetoreplay_(filetoreplay), tickinterval_(tickinterval) {}

  // Start the replay service
  void TickReplayService::start()
  {
    // Open the tick data file for reading
    std::ifstream infile(filetoreplay_);
    if (!infile)
    {
      std::cerr << "Error: unable to open tick data file for reading\n";
      return;
    }

    // Read the tick data and replay it at the specified interval
    while (infile >> tick_data_)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(tickinterval_));
      process_tick_data(tick_data_);
    }

    // Close the tick data file
    infile.close();
  }

  void TickReplayService::process_tick_data(const std::string &tick_data)
  {
    // Do something with the tick data, such as sending it to a trading
    // system or storing it in a database
  }
} // namespace TPF
