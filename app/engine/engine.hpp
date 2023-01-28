#include <atomic>
#include <memory>

#include "../common/constants.hpp"
#include "../queues/message/producer.hpp"

namespace TPF
{
  // Interface class: base engine for td and md engine
  class Engine
  {
  public:
    enum class State : int16_t
    {
      DISCONNECTED = 0, // initial
      CONNECTING,
      CONNECT_ACK, // ctp: front end is  connected; tap: logged in
      AUTHENTICATING,
      AUTHENTICATE_ACK, // ctp: trade authencated
      LOGGING_IN,
      LOGIN_ACK, // ctp: logged in, tap: api ready
      LOGGING_OUT,
      STOPPED
    };

    std::atomic<State> state_;
    std::unique_ptr<Producer> producer_;

    Engine::Engine() : state_(State::DISCONNECTED)
    {
      init();
    }
    virtual ~Engine();

    virtual void init();
    virtual void start();
    virtual void stop();
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
  };
};
