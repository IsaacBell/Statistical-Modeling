namespace TPF {
  // mutex Engine::sendlock_;
  // std::unique_ptr<CMsgq> Engine::msgq_send_;
  Engine::Engine()
    :state(State::DISCONNECTED) {
    init();
  }
  Engine::~Engine() {}
  void Engine::init() {}
  void Engine::start() {}
  void Engine::stopped() {
    state = State::STOPPED;
  }
}