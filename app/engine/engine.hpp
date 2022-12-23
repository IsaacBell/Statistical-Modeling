#include "../common/constants.hpp"

namespace TPF {
  class Engine {
    // Engine state
    enum State : TPF_UINT {
      DISCONNECTED = 0,           // initial state is disconnected
      CONNECTING,
      CONNECT_ACK,                // ctp: front end is  connected; tap:  logined
      AUTHENTICATING,
      AUTHENTICATE_ACK,           // ctp trade authencated
      LOGINING,
      LOGIN_ACK,                  // logined for ctp, for tap api is ready to do things
      LOGOUTING,
      STOP                        // for engine stop
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

  }
};