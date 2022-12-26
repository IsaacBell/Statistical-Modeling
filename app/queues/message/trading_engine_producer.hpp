#include <iostream>
#include <string>
#include <librdkafka/rdkafkacpp.h>
#include <boost/log/trivial.hpp>

namespace TPF
{
  class TradingEngineProducer
  {
  public:
    TradingEngineProducer(const std::string &broker, const std::string_view &topic)
        : broker_(broker), topic_(topic);

    // Send a trade message to Kafka
    void send_trade(const std::string_view &security, int volume, int price);

  private:
    std::string broker_;          // Kafka broker
    std::string topic_;           // Kafka topic
    std::string errstr_;          // Error string
    RdKafka::Producer *producer_; // Kafka producer
  };
}
