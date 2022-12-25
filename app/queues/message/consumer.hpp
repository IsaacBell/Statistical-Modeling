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
