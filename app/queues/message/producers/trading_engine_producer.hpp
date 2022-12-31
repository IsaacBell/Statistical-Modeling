#include <iostream>
#include <string>
#include <librdkafka/rdkafkacpp.h>
#include <boost/log/trivial.hpp>

#include "../producer.hpp"

namespace TPF
{
  class TradingEngineProducer : Producer
  {
  public:
    TradingEngineProducer();
    ~TradingEngineProducer();

    // Send a trade message to Kafka
    void send_security(const std::string &security, int volume, int price);
    void send_message(const std::string &message);

  private:
    std::string broker_;          // Kafka broker
    std::string topic_;           // Kafka topic
    std::string errstr_;          // Error string
    RdKafka::Producer *producer_; // Kafka producer
  };
}
