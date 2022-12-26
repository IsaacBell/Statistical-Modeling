#include <fstream>
#include <iostream>
#include <string>
#include <thread>

namespace TPF
{
  class TickRecordingService
  {
  public:
    TickRecordingService(const std::string &file);

    void start();
    void stop();

  private:
    std::string get_tick_data();
    std::string file_; // File to record tick data to
  };
} // namespace TPF
