#include <fstream>
#include <iostream>
#include <string>
#include <thread>

class TickReplayService
{
public:
  TickReplayService(const std::string &filetoreplay, int32_t tickinterval);

  void start();

private:
  void process_tick_data(const std::string &tick_data);

  std::string filetoreplay_; // File containing tick data to replay
  int32_t tickinterval_;     // Interval at which to replay tick data
  std::string tick_data_;    // Current tick data being processed
};
