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

# Risk Profile Consumer

```
#include <iostream>
#include <string>
#include <unordered_map>
#include <librdkafka/rdkafkacpp.h>
#include <boost/log/trivial.hpp>

class RiskProfileKafka {
 public:
  RiskProfileKafka(const std::string &broker, const std::string &topic)
      : broker_(broker), topic_(topic) {
    // Create Kafka consumer
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("metadata.broker.list", broker, errstr);
    conf->set("group.id", "example-consumer-group", errstr);
    conf->set("auto.offset.reset", "earliest", errstr);
    conf->set("enable.partition.eof", "true", errstr);
    conf->set("statistics.interval.ms", "30000", errstr);
    conf->set("default_topic_conf", conf, errstr);
    consumer_ = RdKafka::KafkaConsumer::create(conf, errstr);
    if (!consumer_) {
      BOOST_LOG_TRIVIAL(error) << "Failed to create consumer: " << errstr;
      exit(1);
    }

    // Subscribe to topic
    std::vector<std::string> topics = {topic};
    RdKafka::ErrorCode resp = consumer_->subscribe(topics);
    if (resp != RdKafka::ERR_NO_ERROR) {
      BOOST_LOG_TRIVIAL(error) << "Failed to subscribe: "
                               << RdKafka::err2str(resp);
      exit(1);
    }
  }

  // Update the risk profile with new data from Kafka
  void update() {
    RdKafka::Message *msg = consumer_->consume(1000);
    if (msg->err() != RdKafka::ERR_NO_ERROR) {
      BOOST_LOG_TRIVIAL(error) << "Consume error: " << msg->errstr();
      delete msg;
      return;
    }
    std::string data(reinterpret_cast<char *>(msg->payload()), msg->len());
    std::vector<std::string> parts = split(data, ',');
    std::string security = parts[0];
    int volume = std::stoi(parts[1]);
    int price = std::stoi(parts[2]);
    int margin = std::stoi(parts[3]);
    addPosition(security, volume, price);
    setMarginRequirement(security, margin);
    delete msg;
  }

  // Add a position to the risk profile
  void add_position(const std::string &security, int volume, int price) {
    positions_[security] += volume;
    exposures_[security] += volume * price;
  }

  // Update the risk profile with new data from Kafka
  void update() {
    RdKafka::Message *msg = consumer_->consume(1000);
    if (msg->err() != RdKafka::ERR_NO_ERROR) {
      BOOST_LOG_TRIVIAL(error) << "Consume error: " << msg->errstr();
      delete msg;
      return;
    }
    std::string data(reinterpret_cast<char *>(msg->payload()), msg->len());
    std::vector<std::string> parts = split(data, ',');
    std::string security = parts[0];
    int volume = std::stoi(parts[1]);
    int price = std::stoi(parts[2]);
    int margin = std::stoi(parts[3]);
    set_margin_requirement(security, margin);
    delete msg;
  }

  // Set the margin requirement for a security
  void set_margin_requirement(const std::string &security, int margin) {
    margin_requirements_[security] = margin;
  }

  // Get the current position size for a security
  int get_position_size(const std::string &security) const {
    return positions_.at(security);
  }

  // Get the current exposure for a security
  int get_exposure(const std::string &security) const {
    return exposures_.at(security);
  }

  // Get the margin requirement for a security
  int get_margin_requirement(const std::string &security) const {
    return margin_requirements_.at(security);
  }

  // Get the total position size
  int get_total_position_size() const {
    int total = 0;
    for (const auto &p : positions_) {
      total += p.second;
    }
    return total;
  }

  // Get the total exposure
  int get_total_exposure() const {
    int total = 0;
    for (const auto &e : exposures_) {
      total += e.second;
    }
    return total;
  }

  // Get the total margin requirement
  int get_total_margin_requirement() const {
    int total = 0;
    for (const auto &m : margin_requirements_) {
      total += m.second;
    }
    return total;
  }

 private:
  std::unordered_map<std::string, int> positions_;       // map of security to position size
  std::unordered_map<std::string, int> exposures_;       // map of security to exposure
  std::unordered_map<std::string, int> margin_requirements_;  // map of security to margin requirement

```

