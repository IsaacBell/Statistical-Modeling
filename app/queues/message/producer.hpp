#include <librdkafka/rdkafkacpp.h>

#include <iostream>
#include <string>
#include <cstring>

class Producer
{
public:
  Producer()
  {
    std::string broker_ = "localhost:9092";
    std::string topic_name_ = "test-topic";

    // Create Kafka producer config
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", broker_, errstr_);
    conf->set("acks", "all", errstr_);

    // Create Kafka producer
    producer_ = RdKafka::Producer::create(conf, errstr_);
    if (!producer_)
      BOOST_LOG_TRIVIAL(error) << "Failed to create producer: " << errstr_;

    // Create Kafka topic config
    RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    // Create Kafka topic
    topic_ = RdKafka::Topic::create(producer_, topic_name_, tconf, errstr_);
    if (!topic_)
    {
      BOOST_LOG_TRIVIAL(error) << ("Failed to create producer: " + errstr_);
      exit(1);
    }
  }

  ~Producer()
  {
    if (topic_)
      delete topic_;
    if (producer_)
      delete producer_;
  }

  void ProduceMessage(std::string message)
  {
    // Produce message
    RdKafka::ErrorCode resp =
        producer_->produce(topic_, RdKafka::Topic::PARTITION_UA,
                           RdKafka::Producer::RK_MSG_COPY,
                           const_cast<char *>(message.c_str()), message.size(),
                           NULL, NULL);
    if (resp != RdKafka::ERR_NO_ERROR)
    {
      std::cerr << "Produce failed: " << RdKafka::err2str(resp) << std::endl;
      BOOST_LOG_TRIVIAL(error) << ("Message production failed: " + RdKafka::err2str(resp));
    }
    else
      BOOST_LOG_TRIVIAL(info) << ("Produced message: " + message);

    // Poll to handle delivery reports
    producer_->poll(0);
  }

private:
  std::string errstr_;
  RdKafka::Producer *producer_;
  RdKafka::Topic *topic_;
};
