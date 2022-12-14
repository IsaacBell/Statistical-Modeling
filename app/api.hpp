#include <stdlib.h>
#include <iostream>
#include <jsoncpp/json/json.h>

#include "./constants.hpp"

namespace TPF {
  class API {
    std::string symbol = "AAPL";
    std::string startDate = "2013-01-01";
    std::string endDate = "2022-12-31";

    // Build the URL for the API call

    void setup() {
      if (!endpoint_code) return;

      query();
    }

    auto query() {
      std::string url = "https://www.alphavantage.co/query?";
      url += "function=TIME_SERIES_DAILY_ADJUSTED";
      url += "&symbol=" + symbol;
      url += "&start_date=" + startDate;
      url += "&end_date=" + endDate;
      url += "&apikey=" + api_key();

      return AlphaVantageQuery query(API_GET_ALPHAVANTAGE_HISTORICAL_DATA_CODE, url);
    }

    const std::string api_key() {
      return getenv("ALPHAVANTAGE_API_KEY");
    }
  }
}