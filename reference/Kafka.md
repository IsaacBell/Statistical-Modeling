# Send Message

This example assumes that you have already installed the librdkafka library and included the necessary header files in your project.

The example takes four command-line arguments:

*broker:* the hostname and port of the Kafka broker to connect to, in the form hostname:port
*topic:* the name of the topic to send the message to
*partition:* the partition number to send the message to
*message:* the message to send

```
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <librdkafka/rdkafkacpp.h>
#include <boost/log/trivial.hpp>

int main(int argc, char** argv) {
  // Parse command line arguments
  if (argc != 5) {
    BOOST_LOG_TRIVIAL(error) << "Usage: " << argv[0]
                             << " <broker> <topic> <partition> <message>";
    exit(1);
  }
  std::string broker = argv[1];
  std::string topic = argv[2];
  int partition = std::stoi(argv[3]);
  std::string message = argv[4];

  // Create Kafka producer
  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  conf->set("metadata.broker.list", broker, errstr);
  conf->set("dr_cb", dr_cb, errstr);
  RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
  if (!producer) {
    BOOST_LOG_TRIVIAL(error) << "Failed to create producer: " << errstr;
    exit(1);
  }

  // Create topic handle
  RdKafka::Topic *topic_handle = RdKafka::Topic::create(producer, topic,
                                                         NULL, errstr);
  if (!topic_handle) {
    BOOST_LOG_TRIVIAL(error) << "Failed to create topic: " << errstr;
    exit(1);
  }

  // Send message
  RdKafka::ErrorCode resp =
      producer->produce(topic_handle, partition,
                        RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                        const_cast<char *>(message.c_str()), message.size(),
                        NULL, NULL);
  if (resp != RdKafka::ERR_NO_ERROR) {
    BOOST_LOG_TRIVIAL(error) << "Failed to produce to topic: "
                             << RdKafka::err2str(resp);
  } else {
    BOOST_LOG_TRIVIAL(info) << "Produced message to topic " << topic;
  }

  // Wait for message to be delivered
  producer->poll(0);

  // Clean up
  delete topic_handle;
  delete producer;

  return 0;
}
```
