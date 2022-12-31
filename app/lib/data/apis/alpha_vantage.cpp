#include <string>
#include "alpha_vantage.hpp"

using TPF::AlphaVantageQuery;

const std::string AlphaVantageQuery::url() const
{
  return "https://www.alphavantage.co/query";
}

const std::string AlphaVantageQuery::api_key() const
{
  return getenv("TPF_ALPHAVANTAGE_API_KEY") || "";
}

bool AlphaVantageQuery::get_historical_data()
{
  return Get(
      url(),
      cpr::Parameters{{"function", "TIME_SERIES_DAILY_ADJUSTED"},
                      {"symbol", symbol_},
                      {"start_date", start_date_},
                      {"end_date", end_date_},
                      {"apikey", auth_token_ || api_key()}});
}
