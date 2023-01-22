#include <string>
#include <memory>
#include <boost/property_tree/json_parser.hpp>

#include "../producer.hpp"

using boost::property_tree::ptree;

class MyKafkaProducer : Producer
{
public:
  JsonProducer()
  {
    init("json", "localhost:9092");
  }

  void produce(ptree const &payload)
  {
    // Filter the payload
    if (filter(payload))
    {
      // Serialize the payload
      std::stringstream ss;
      write_json(ss, payload);
      std::string json_string = ss.str();

      // produce the message
      librdkafka::ErrorCode resp = producer_->produce(*topic_, librdkafka::RD_KAFKA_PARTITION_UA,
                                                      librdkafka::Producer::RK_MSG_COPY,
                                                      json_string.c_str(), json_string.size(),
                                                      nullptr, 0,
                                                      0, nullptr);
      if (resp != librdkafka::ERR_NO_ERROR)
      {
        std::cerr << "Error producing message: " << librdkafka::err2str(resp) << std::endl;
      }
      else
        producer_->poll(0);
    }
  }

private:
  bool filter(const ptree &payload)
  {
    // placeholder for filtering the payload
    return true;
  }
};
