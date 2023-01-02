#include <string>

#include "../request_data.hpp"
#include "alpha_vantage.hpp"

namespace TPF
{
  AlphaVantageQuery::AlphaVantageQuery(APIRequestData &data) : data_(data) {}

  bool AlphaVantageQuery::GetHistoricalData()
  {
    return Get(
        url(),
        cpr::Parameters{{"function", "TIME_SERIES_DAILY_ADJUSTED"},
                        {"symbol", symbol_},
                        {"start_date", start_date_},
                        {"end_date", end_date_},
                        {"apikey", auth_token_ || api_key()}});
  }

  const std::string AlphaVantageQuery::url() const
  {
    return "https://www.alphavantage.co/query";
  }

  const std::string AlphaVantageQuery::api_key() const
  {
    return getenv("TPF_ALPHAVANTAGE_API_KEY") || "";
  }

  bool AlphaVantageQuery::Get(std::string_view url = "", cpr::Parameters params = nullptr)
  {
    response_ = cpr::Get(cpr::Url{url || url()},
                         params || cpr::Parameters{{"apikey", auth_token_ || api_key()}});

    return response_.status_code == 200;
  }

  bool AlphaVantageQuery::Post(std::string_view url = "", cpr::Parameters params = nullptr)
  {
    cpr::Header headers;
    headers.insert({"Authorization", "Bearer " + data.auth_token_});
    headers.insert({"Content-Type", "application/json"});

    response_ = cpr::Post(cpr::Url{api_url}, headers, cpr::Body{data_.data_ || ""});

    return response_.status_code == 200;
  }
} // namespace TPF
