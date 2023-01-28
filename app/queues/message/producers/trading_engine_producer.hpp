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
    TradingEngineProducer::TradingEngineProducer()
    {
      init("trade");
    }

    ~TradingEngineProducer();

    // Send a trade message to Kafka
    void TradingEngineProducer::send_security(const std::string &security, int volume, int price)
    {
      return send_message(security + "," +
                          std::to_string(volume) + "," +
                          std::to_string(price));
    }

    void TradingEngineProducer::send_message(const std::string &message)
    {
      RdKafka::ErrorCode resp =
          producer_->produce(topic_, RdKafka::Topic::PARTITION_UA,
                             RdKafka::Producer::RK_MSG_COPY,
                             const_cast<char *>(message.c_str()), message.size(),
                             NULL, NULL);
      if (resp != RdKafka::ERR_NO_ERROR)
        BOOST_LOG_TRIVIAL(error) << "Error producing message: " << RdKafka::err2str(resp);

      producer_->poll(0);
    }

  private:
    std::string broker_;          // Kafka broker
    std::string topic_;           // Kafka topic
    std::string errstr_;          // Error string
    RdKafka::Producer *producer_; // Kafka producer
  };
}
