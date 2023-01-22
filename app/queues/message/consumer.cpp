#include <iostream>
#include <string>
#include <cstdlib>
#include <librdkafka/rdkafkacpp.h>

#include "consumer.hpp"

namespace TPF
{
  void Consumer::init()
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

  void cleanup()
  {
    // Clean up
    consumer_->close();
    delete consumer_;
    delete conf;
  }

  // void consume(RdKafka::ConsumeCb *cb)
  // {
  //   consumer_->consume_callback(cb);
  // }
} // namespace TPF
