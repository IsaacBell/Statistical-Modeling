#include <iostream>
#include <string>
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

class Consumer : public RdKafka::ConsumeCb
{
public:
  std::string topic_str = "test";
  std::string group_id = "my_consumer_group_id";
  RdKafka::KafkaConsumer *consumer_;

  void init()
  {
    // Create Kafka consumer
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    if (conf->set("group.id", group_id, errstr) != RdKafka::Conf::CONF_OK)
    {
      BOOST_LOG_TRIVIAL(error) << errstr;
      exit(1);
    }
    if (conf->set("metadata.broker.list", brokers, errstr) != RdKafka::Conf::CONF_OK)
    {
      BOOST_LOG_TRIVIAL(error) << errstr;
      exit(1);
    }

    conf->set("consume_cb", *this, errstr); // todo - 2nd arg expects a reference
    RdKafka::KafkaConsumer *consumer = RdKafka::KafkaConsumer::create(conf, errstr);

    if (!consumer)
    {
      BOOST_LOG_TRIVIAL(error) << ("Failed to create consumer: " + errstr);
      exit(1);
    }

    // Subscribe to topic
    RdKafka::ErrorCode err = consumer->subscribe({topic_str});
    if (err)
    {
      BOOST_LOG_TRIVIAL(info) << ("Failed to subscribe to " + topic_str + ": " + RdKafka::err2str(err));
      exit(1);
    }
  }

  void consume_cb(RdKafka::Message &msg, void *opaque)
  {
    BOOST_LOG_TRIVIAL(info) << ("Consumed message with key " +
                                *(msg.key()) +
                                " at offset " +
                                msg.offset() +
                                "\n");
  }

private:
  std::string brokers = getenv("TPF_KAFKA_PORT") || "localhost:9092";
  std::string errstr;
};
