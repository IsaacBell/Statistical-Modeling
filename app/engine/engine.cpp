#include "engine.hpp"

namespace TPF {
  // mutex Engine::sendlock_;
  // std::unique_ptr<CMsgq> Engine::msgq_send_;
  Engine::Engine() : state_(State::DISCONNECTED) {
    init();
  }
  Engine::~Engine() {}
  void Engine::init() {}
  void Engine::start() {}
  void Engine::stop() {
    state_ = State::STOPPED;
  }
}
