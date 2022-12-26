#include <iostream>
#include <string>
#include <librdkafka/rdkafkacpp.h>
#include <boost/log/trivial.hpp>

class TradingEngineProducer
{
public:
  TradingEngineProducer(const std::string &broker, const std::string &topic)
      : broker_(broker), topic_(topic)
  {
    // Create Kafka producer
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("metadata.broker.list", broker, errstr);
    conf->set("queue.buffering.max.messages", "1000000", errstr);
    conf->set("batch.num.messages", "1000", errstr);
    conf->set("message.send.max.retries", "10", errstr);
    conf->set("retry.backoff.ms", "500", errstr);
    conf->set("statistics.interval.ms", "30000", errstr);
    conf->set("default_topic_conf", conf, errstr);
    producer_ = RdKafka::Producer::create(conf, errstr);
    if (!producer_)
    {
      BOOST_LOG_TRIVIAL(error) << "Failed to create producer: " << errstr;
      exit(1);
    }
  }

  // Send a trade message to Kafka
  void send_trade(const std::string &security, int volume, int price)
  {
    std::string message = security + "," + std::to_string(volume) + "," + std::to_string(price);
    RdKafka::ErrorCode resp =
        producer_->produce(topic_, RdKafka::Topic::PARTITION_UA,
                           RdKafka::Producer::RK_MSG_COPY,
                           const_cast<char *>(message.c_str()), message.size(),
                           NULL, NULL);
    if (resp != RdKafka::ERR_NO_ERROR)
    {
      BOOST_LOG_TRIVIAL(error) << "Produce error: " << RdKafka::err2str(resp);
    }
    producer_->poll(0);
  }

private:
  std::string broker_;          // Kafka broker
  std::string topic_;           // Kafka topic
  std::string errstr_;          // Error string
  RdKafka::Producer *producer_; // Kafka producer
};
