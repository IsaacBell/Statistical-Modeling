#include <atomic>
#include <memory>

#include "../common/constants.hpp"

namespace TPF {
  enum class State {
    DISCONNECTED,               // initial
    CONNECTING,
    CONNECT_ACK,                // ctp: front end is  connected; tap:  logged in
    AUTHENTICATING,
    AUTHENTICATE_ACK,           // ctp: trade authencated
    LOGINING,
    LOGIN_ACK,                  // ctp: logged in, t:ap api ready
    LOGOUTING,
    STOPPED
  };

  // Interface class: base engine for td and md engine
  class Engine {
  public:
    // static mutex sendlock_;  // msg send lock_
    // static std::unique_ptr<CMsgq> msgq_send_;  //for md and td messenge to client, all engine share same msgq, usually publish mode
    // std::unique_ptr<CMsgq> msgq_recv_;  //each engine has its own msgq, usually subscribe mode
    std::atomic<State> state_;
    std::unique_ptr<Messenger> messenger_;

    Engine();
    virtual ~Engine();

    virtual void init();
    virtual void start();
    virtual void stop();
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
  };
};
