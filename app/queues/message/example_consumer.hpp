#include <iostream>
#include <string>
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

class ExampleConsumer : public RdKafka::ConsumeCb
{
public:
  void consume_cb(RdKafka::Message &msg, void *opaque)
  {
    BOOST_LOG_TRIVIAL(info) << ("Consumed message with key " +
                                *(msg.key()) +
                                " at offset " +
                                msg.offset() +
                                "\n");
  }
};

int main(int argc, char **argv)
{
  std::string brokers = getenv("TPF_KAFKA_PORT") || "localhost:9092";
  std::string errstr;
  std::string topic_str = "test";
  std::string group_id = "my_consumer_group_id";

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

  ExampleConsumeCb ex_consume_cb;
  conf->set("consume_cb", &ex_consume_cb, errstr);
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

  // Poll for messages
  while (true)
  {
    RdKafka::Message *msg = consumer->consume(1000);
    switch (msg->err())
    {
    case RdKafka::ERR__TIMED_OUT:
      // No messages received within timeout
      continue;
    case RdKafka::ERR_NO_ERROR:
      // Message consumed successfully
      ex_consume_cb.consume_cb(*msg, NULL);
      delete msg;
      break;
    default:
      BOOST_LOG_TRIVIAL(error) << ("Error consuming message: " + msg->errstr());
      delete msg;
      break;
    }
  }

  // Clean up
  consumer->close();
  delete consumer;
  delete conf;

  return 0;
}
