/*
  int main()
  {
    JsonServer server(12345);
    server.start();
  }
*/

#include <boost/property_tree/json_parser.hpp>

#include "./server.hpp"

using boost::property_tree::ptree;

class JsonServer : public Server
{
public:
  JsonServer(int port) : Server(port) {}

  void save(ptree const &payload)
  {
    std::cout << payload.get<std::string>("name") << "\n";

    // Serialize the payload
    std::stringstream ss;
    write_json(ss, payload);
    std::string json_string = ss.str();

    // Publish the payload to the Kafka topic
    JsonProducer producer;
    producer.produce(json_string);
  }
};
