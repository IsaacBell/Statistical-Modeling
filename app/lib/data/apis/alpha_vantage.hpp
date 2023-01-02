#ifndef _TPF_LIB_DATA_APIS_ALPHA_VANTAGE_HPP_
#define _TPF_LIB_DATA_APIS_ALPHA_VANTAGE_HPP_

#include <cpr>

#include "../request_data.hpp"

namespace TPF
{
  struct AlphaVantageAPI
  {
  public:
    AlphaVantageAPI::AlphaVantageAPI(APIRequestData &data);

    bool GetHistoricalData();

  private:
    const std::string url() const;
    const std::string api_key() const;

    bool Get(std::string_view url = "", cpr::Parameters params = nullptr);
    bool Post(std::string_view url = "", cpr::Parameters params = nullptr);
  };
}

#endif
