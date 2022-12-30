#include "engine.hpp"

namespace TPF
{
  Engine::Engine() : state_(State::DISCONNECTED)
  {
    init();
  }
  Engine::~Engine() {}
  void Engine::init() {}
  void Engine::start() {}
  void Engine::stop()
  {
    state_ = State::STOPPED;
  }
}
