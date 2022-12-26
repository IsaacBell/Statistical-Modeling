# Risk Profile

Model the current risk profile, including metrics such as position sizes, exposures, and margin requirements

```
#include <unordered_map>
#include <limits>

class RiskProfile {
 public:
  // Add a position to the risk profile
  void addPosition(const std::string &security, int volume, int price) {
    positions_[security] += volume;
    exposures_[security] += volume * price;
  }

  // Remove a position from the risk profile
  void removePosition(const std::string &security, int volume, int price) {
    positions_[security] = std::max(positions_[security] - volume, 0);
    exposures_[security] -= volume * price;
  }

  // Set the margin requirement for a security
  void setMarginRequirement(const std::string &security, int margin) {
    margin_requirements_[security] = margin;
  }

  // Get the current position size for a security
  int getPositionSize(const std::string &security) const {
    return positions_.at(security);
  }

  // Get the current exposure for a security
  int getExposure(const std::string &security) const {
    return exposures_.at(security);
  }

  // Get the margin requirement for a security
  int getMarginRequirement(const std::string &security) const {
    return margin_requirements_.at(security);
  }

  // Get the total position size
  int getTotalPositionSize() const {
    int total = 0;
    for (const auto &p : positions_) {
      total += p.second;
    }
    return total;
  }

  // Get the total exposure
  int getTotalExposure() const {
    int total = 0;
    for (const auto &e : exposures_) {
      total += e.second;
    }
    return total;
  }

  // Get the total margin requirement
  int getTotalMarginRequirement() const {
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
};
```

# Risk Management Consumer

Example of a Kafka consumer in C++ that receives risk management variables from its producer:

```
#include <librdkafka/rdkafka.h>
#include <string>

// Callback function for message delivery
void msg_delivered(rd_kafka_t *rk,
                   const rd_kafka_message_t *rkmessage, void *opaque) {
  // Check for message delivery error
  if (rkmessage->err) {
    // Handle error
  } else {
    // Message was successfully delivered
  }
}

int main() {
  // Create Kafka consumer
  rd_kafka_t *consumer;

  // Subscribe to topic
  rd_kafka_topic_t *topic;

  // Initialize Kafka consumer and topic
  // ...

  // Poll for messages
  while (true) {
    rd_kafka_message_t *msg;
    msg = rd_kafka_consumer_poll(consumer, 1000);
    if (msg) {
      // Process message
      if (msg->err == RD_KAFKA_RESP_ERR_NO_ERROR) {
        // Get message payload
        std::string payload((char *)msg->payload, msg->len);

        // Parse message to extract risk management variables
        // ...

        // Update risk management system with new variables
        // ...
      }
      rd_kafka_message_destroy(msg);
    }
  }

  // Close consumer and topic
  // ...

  return 0;
}
```
