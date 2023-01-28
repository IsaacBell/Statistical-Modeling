#include <iostream>
#include <string>
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

namespace TPF
{
  class Consumer : public RdKafka::ConsumeCb
  {
  public:
    Consumer::Consumer(std::string topic_str = "test", std::string group_id_ = "my_consumer_group_id")
        : topic_str_(topic_str),
          group_id_(group_id),
          conf_(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL)){};

    void Consumer::init()
    {
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
      *consumer_ = RdKafka::KafkaConsumer::create(conf, errstr);

      if (!consumer_)
      {
        BOOST_LOG_TRIVIAL(error) << ("Failed to create consumer: " + errstr);
        exit(1);
      }

      // Subscribe to topic
      RdKafka::ErrorCode err = consumer_->subscribe({topic_str});
      if (err)
      {
        BOOST_LOG_TRIVIAL(info) << ("Failed to subscribe to " + topic_str + ": " + RdKafka::err2str(err));
        exit(1);
      }
    }

    void cleanup()
    {
      // Clean up
      consumer_->close();
      delete consumer_;
      delete conf;
    }

    // callback after consumption
    static void Consumer::consume_cb(RdKafka::Message &msg, void *opaque)
    {
      BOOST_LOG_TRIVIAL(info) << ("Consumed message with key " +
                                  *(msg.key()) +
                                  " at offset " +
                                  msg.offset() +
                                  "\n");
    }

    void run()
    {
      // Poll for messages
      while (true)
      {
        RdKafka::Message *msg = consumer_->consume(1000);
        switch (msg->err())
        {
        case RdKafka::ERR__TIMED_OUT:
          // No messages received within timeout
          continue;
        case RdKafka::ERR_NO_ERROR:
          // Message consumed successfully
          ex_consume_cb.consume_cb(*msg, NULL);
          Consumer::consume_cb(msg, NULL);
          delete msg;
          break;
        default:
          BOOST_LOG_TRIVIAL(error) << ("Error consuming message: " + msg->errstr());
          delete msg;
          break;
        }
      }
    }

    void consume() { run(); }

  private:
    std::string errstr;
    std::string topic_str_ = "test";
    std::string group_id_ = "my_consumer_group_id";
    RdKafka::Conf *conf_; // config
    RdKafka::KafkaConsumer *consumer_;
    std::string brokers = getenv("TPF_KAFKA_PORT") || "localhost:9092";
  };
}
