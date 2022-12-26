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

// #include <Services/tradingengine.h>
// #include <Common/datastruct.h>
// #include <Common/config.h>
// #include <Common/util.h>
// #include <Common/logger.h>
// #include <Data/datamanager.h>
// #include <Engine/Engine.h>
// #include <Engine/CtpMDEngine.h>
// #include <Engine/CtpTDEngine.h>
// #include <Engine/TapMDEngine.h>
// #include <Engine/TapTDEngine.h>
// #include <Engine/PaperTDEngine.h>
// #include <Trade/ordermanager.h>
// #include <Trade/portfoliomanager.h>
// #include <Trade/riskmanager.h>
// #include <Services/Strategy/strategyservice.h>
// #include <Services/dataservice.h>

#include <pthread.h>
#include <signal.h>
#include <future>
#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <functional>

#include <boost/log/trivial.hpp>

#include "../"

namespace TPF
{
  void TradingEngineService::start_engine(shared_ptr<Engine> p_engine)
  {
    p_engine->start();
  }

  TradingEngineService::TradingEngineService()
  {
    // CConfig::instance();
    DataManager::instance();
    OrderManager::instance();
    PortfolioManager::instance();
    RiskManager::instance();

    // TODO
    // _broker = CConfig::instance()._broker;
    // mode = CConfig::instance()._mode;

    TradingEngineService::~TradingEngineService()
    {
      for (auto &e : p_engines_)
      {
        while ((e != nullptr) && (e->state_ != STOP))
        {
          e->stop();
          msleep(100);
        }
      }

      while (MICRO_SERVICE_NUMBER > 0)
        msleep(100);

      // if (CConfig::instance()._msgq == MSGQ::NANOMSG)
      //   nn_term();

      for (std::thread *t : threads_)
      {
        if (t->joinable())
        {
          t->join();
          delete t;
        }
        else
        {
          // pthread_cancel(t->native_handle());
          // delete t;
        }
      }
      BOOST_LOG_TRIVIAL(info) << "Exit trading engine";
    }

    int32_t TradingEngineService::cronjobs(bool force)
    {
      // set console handler
      signal(SIGINT, ConsoleControlHandler);
      signal(SIGPWR, ConsoleControlHandler);

      time_t timer;
      struct tm tm_info;

      // cronjobs:
      while (!g_shutdown)
      {
        msleep(1 * 1000);

        time(&timer);
        localtime_r(&timer, &tm_info);
        // at weekend do nothing
        // 0=sunday, 2=tuesday, 6=saturday
        if (!tm_info.tm_wday)
        {
          continue;
        }
        // send timer msg to all engine
        std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_TIMER);
        msg_relay_->send(pmsg);

        // flow count reset
        RiskManager::instance().resetflow();

        // auto reset at 2:35
        if (tm_info.tm_hour == 2 && tm_info.tm_min == 35 && tm_info.tm_sec == 0)
        {
          std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_ENGINE_RESET);
          msg_relay_->send(pmsg);
        }

        if (tm_info.tm_wday != 6)
        {
          // auto reset at 16:00
          if (tm_info.tm_hour == 16 && tm_info.tm_min == 0 && tm_info.tm_sec == 0)
          {
            std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_ENGINE_RESET);
            msg_relay_->send(pmsg);
          }

          // switch day, at 20:30 everyday,  reset td engine, needconfirmation
          if (tm_info.tm_hour == 20 && tm_info.tm_min == 30 && tm_info.tm_sec == 0)
          {
            std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_SWITCH_TRADING_DAY);
            msg_relay_->send(pmsg);
            RiskManager::instance().switchday();
          }

          // auto connect at 8:45, 13:15, 20:45
          if (tm_info.tm_hour == 8 && tm_info.tm_min == 45 && tm_info.tm_sec == 0)
          {
            std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_ENGINE_CONNECT);
            msg_relay_->send(pmsg);
          }

          if (tm_info.tm_hour == 13 && tm_info.tm_min == 15 && tm_info.tm_sec == 0)
          {
            std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_ENGINE_CONNECT);
            msg_relay_->send(pmsg);
          }

          if (tm_info.tm_hour == 20 && tm_info.tm_min == 45 && tm_info.tm_sec == 0)
          {
            std::shared_ptr<MsgHeader> pmsg = make_shared<MsgHeader>(DESTINATION_ALL, "0", MSG_TYPE_ENGINE_CONNECT);
            msg_relay_->send(pmsg);
          }
        }
      }

      if (force) // ctrl-c
      {
        throw runtime_error("ctrl-c triggered shutdown");
      }
      return 0;
    }

    int32_t TradingEngineService::run()
    {
      if (g_shutdown)
        return 1;
      // sigsegv sig backtrace
      g_except_stack.flag = sigsetjmp(g_except_stack.env, 1);
      if (!g_except_stack.isDef())
      {
        signal(SIGSEGV, recvSignal);
        try
        {
          auto fu1 = async(launch::async, std::bind(&TradingEngineService::cronjobs, this, std::placeholders::_1), true);
          if (mode == RUN_MODE::RECORD_MODE)
          {
            BOOST_LOG_TRIVIAL(trace) << "RECORD_MODE";
            // threads_.push_back(new thread(TickRecordingService));
          }
          else if (mode == RUN_MODE::REPLAY_MODE)
          {
            BOOST_LOG_TRIVIAL(trace) << "REPLAY_MODE";
            // threads_.push_back(new thread(TickReplayService, CConfig::instance().filetoreplay,CConfig::instance()._tickinterval));
            // threads_.push_back(new thread(DataBoardService));
            // //threads_.push_back(new thread(StrategyManagerService));
          }
          else if (mode == RUN_MODE::TRADE_MODE)
          {
            BOOST_LOG_TRIVIAL(trace) << "TRADE_MODE";
            // threads_.push_back(new thread(TickRecordingService));
            for (auto iter = CConfig::instance()._gatewaymap.begin(); iter != CConfig::instance()._gatewaymap.end(); iter++)
            {
              switch (iter->second.api)
              {
              case "PAPER.TD":
                std::shared_ptr<Engine> papertdengine = make_shared<PaperTDEngine>();
                threads_.push_back(new std::thread(startengine, papertdengine));
                p_engines_.push_back(papertdengine);
              default:
                BOOST_LOG_TRIVIAL(error) << "API not supported";
                break;
              }
            }
          }
          else
          {
            BOOST_LOG_TRIVIAL(error) << "Mode doesn't exist.";
            return 1;
          }

          // set thread affinity
          // engine thread
          if (CConfig::instance().cpuaffinity)
          {
            int32_t num_cpus = std::thread::hardware_concurrency();
            for (int32_t i = 0; i < threads_.size(); i++)
            {
              cpu_set_t cpuset;
              CPU_ZERO(&cpuset);
              CPU_SET(i % num_cpus, &cpuset);
              int32_t rc = pthread_setaffinity_np(threads_[i]->native_handle(), sizeof(cpu_set_t), &cpuset);
              if (rc != 0)
              {
                BOOST_LOG_TRIVIAL(error) << "Error calling pthread_setaffinity_np: " << rc;
              }
            }

            // main thread
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(threads_.size() % num_cpus, &cpuset);
            int32_t rc = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0)
            {
              BOOST_LOG_TRIVIAL(error) << "Error calling pthread_setaffinity_np: " << rc;
            }
          }
          while (!g_shutdown)
          {
            msg_relay_->relay();
          }

          fu1.get();
        }
        catch (exception &e)
        {
          BOOST_LOG_TRIVIAL(error) << e.what();
        }
        catch (...)
        {
          BOOST_LOG_TRIVIAL(error) << "TPF terminated in error!";
        }
      }
      else
      {
        // g_except_stack.clear();
        signal(SIGSEGV, SIG_IGN);
        exit(0);
      }

      // for (const auto& e : p_engines_) {
      //     e->stop();
      // }
      return 0;
    }

    bool TradingEngineService::live() const
    {
      return g_shutdown == true;
    }

  } // namespace TPF