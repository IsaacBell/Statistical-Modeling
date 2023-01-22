#include <iostream>
#include <string>
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

namespace TPF
{
  class Consumer : public RdKafka::ConsumeCb
  {
  public:
    std::string topic_str_ = "test";
    std::string group_id_ = "my_consumer_group_id";
    RdKafka::KafkaConsumer *consumer_;

    Consumer::Consumer(std::string topic_str = "test", std::string group_id_ = "my_consumer_group_id")
        : topic_str_(topic_str), group_id_(group_id){};

    void init();

    static void consume_cb(RdKafka::Message &msg, void *opaque);

  private:
    std::string brokers = getenv("TPF_KAFKA_PORT") || "localhost:9092";
    std::string errstr;
  };
}
