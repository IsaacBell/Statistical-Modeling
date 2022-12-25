// #include <Common/config.h>
// #include <Common/util.h>
// #include <Common/timeutil.h>
// #include <Common/logger.h>
// #include <Common/Data/datatype.h>
// #include <Trade/ordermanager.h>
// #include <Data/datamanager.h>
// #include <Services/strategyservice.h>
// #include <Strategy/strategyFactory.h>
// #include <Strategy/smacross.h>
#include <atomic>

#ifdef _WIN32
#include <nanomsg/src/nn.h>
#include <nanomsg/src/pair.h>
#else
#include <nanomsg/nn.h>
#include <nanomsg/pair.h>
#endif

namespace TPF
{
  extern std::atomic<bool> gShutdown;

  void StrategyManagerService() {}
}
