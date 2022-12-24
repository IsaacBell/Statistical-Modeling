#include "query.hpp";

namespace TPF {
  class AlphaVantageQuery : Query {
  public:
    void get_historical_data();
    const std::string AlphaVantageQuery::url() const;
  private:
    const std::string AlphaVantageQuery::api_key() const;
  };
}
