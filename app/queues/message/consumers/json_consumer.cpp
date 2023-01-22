#include <string>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>

#include "../consumer.hpp"

namespace TPF
{
  class JsonConsumer : public Consumer
  {
  public:
    static void consume_cb(RdKafka::Message &msg, void *opaque)
    {
      // Deserialize payload
      std::string json_string(static_cast<const char *>(msg.payload()), msg.len());
      std::stringstream ss;
      ss << json_string;
      ptree payload;
      read_json(ss, payload);

      // Handle the payload
      std::cout << payload.get<std::string>("name") << std::endl;

      BOOST_LOG_TRIVIAL(info) << ("Consumed message with key " +
                                  *(msg.key()) +
                                  " at offset " +
                                  msg.offset() +
                                  "\n");
    }
  };
} // namespace TPF
