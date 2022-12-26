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

  void init();

  void consume_cb(RdKafka::Message &msg, void *opaque);

private:
  std::string brokers = getenv("TPF_KAFKA_PORT") || "localhost:9092";
  std::string errstr;
};
