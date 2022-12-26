/*****************************************************************************
 * Copyright [2019]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#ifndef _TPF_SERVICES_TRADING_ENGINE_SERVICE_H_
#define _TPF_SERVICES_TRADING_ENGINE_SERVICE_H_

#if defined(_WIN32) || defined(_WIN64)
#ifdef DLL_EXPORT
#define DLL_EXPORT_IMPORT __declspec(dllexport) // export DLL information
#else
#define DLL_EXPORT_IMPORT __declspec(dllimport) // import DLL information
#endif
#else
#define DLL_EXPORT_IMPORT
#endif

// #include <Common/datastruct.h>
// #include <Engine/Engine.h>
#include <atomic>
#include <thread>
#include <memory>
#include <vector>

namespace TPF
{
  extern std::atomic<bool> g_shutdown;
  // extern Except_frame g_except_stack;

  extern std::atomic<uint64_t> MICRO_SERVICE_NUMBER;

  void start_engine(shared_ptr<Engine> p_engine)

      class DLL_EXPORT_IMPORT TradingEngineService
  {
    RUN_MODE mode = RUN_MODE::TRADE_MODE; // RUN_MODE::REPLAY_MODE;
    // BROKERS _broker = BROKERS::PAPER;
    std::vector<std::thread *> p_threads_;
    // std::vector<std::shared_ptr<Engine>> p_engines_;
    // std::unique_ptr<IMessenger> msg_relay_;
    // std::shared_ptr<SQLogger> logger;

  public:
    // std::atomic<bool>* setconsolecontrolhandler(void);
    // setconsolecontrolhandler(void)
    int32_t cronjobs(bool force = true);

    int32_t run();
    bool live() const;

    TradingEngineService();
    ~TradingEngineService();

    TradingEngineService(TradingEngineService &&) = delete;
    TradingEngineService(const TradingEngineService &) = delete;
    TradingEngineService &operator=(TradingEngineService &&) = delete;
    TradingEngineService &operator=(const TradingEngineService &) = delete;
  };
} // namespace TPF
#endif // _TPF_SERVICES_TRADING_ENGINE_SERVICE_H_
