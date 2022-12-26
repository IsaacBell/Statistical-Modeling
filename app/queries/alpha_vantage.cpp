#include <string>
#include "alpha_vantage.hpp"

using TPF::AlphaVantageQuery;

const std::string AlphaVantageQuery::url() const
{
  const auto out =
      "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY_ADJUSTED&symbol=" + symbol + "&start_date=" + start_date + "&end_date=" + end_date + "&apikey=" + api_key();

  return out;
}

const std::string AlphaVantageQuery::api_key() const
{
  return getenv("TPF_ALPHAVANTAGE_API_KEY");
}
