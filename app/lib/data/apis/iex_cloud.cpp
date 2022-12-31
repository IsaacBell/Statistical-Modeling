#pragma once
#include <thread>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <ctype.h>  /* isalpha */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* getenv */
#include <string>   /* to_string */
#include <locale>   /* std::tolower, std::locale */

#include "api.hpp"
#include "request_data.hpp"

namespace TPF
{
  inline bool IEXCloud::Book()
  {
    return send_get_request("Book");
  }

  inline bool IEXCloud::Company()
  {
    return send_get_request("Company");
  }

  inline bool IEXCloud::Dividends()
  {
    return send_get_request("Dividends");
  }

  // inline bool IEXCloud::Earnings()
  // {
  //   return send_get_request("Earnings", "earnings/5y");
  // }

  // inline bool IEXCloud::EffectiveSpread()
  // {
  //   return send_get_request("EffectiveSpread", "/effective-spread");
  // }

  inline bool IEXCloud::Financials()
  {
    return send_get_request("Financials");
  }

  inline bool IEXCloud::Price()
  {
    return send_get_request("Price");
  }

  inline bool IEXCloud::Quote()
  {
    return send_get_request("Quote");
  }

  inline bool IEXCloud::Relevant()
  {
    return send_get_request("Relevant");
  }

  // inline bool IEXCloud::Splits()
  // {
  //   return send_get_request("Splits", "splits/5y");
  // }

  // inline bool IEXCloud::TimeSeries()
  // {
  //   return send_get_request("TimeSeries", "time-series");
  // }

  // inline bool IEXCloud::VolumeByVenue()
  // {
  //   return send_get_request("VolumeByVenue", "/volume-by-venue");
  // }

  inline bool IEXCloud::send_get_request(std::string_view key)
  {
    return send_get_request(key);
  }

  const std::string IEXCloud::url() const
  {
    return "https://sandbox.iexapis.com/stable/stock/market/batch";
  }

  const std::string IEXCloud::api_key() const
  {
    // getenv("IEX_API_PUB_KEY");
    return getenv("IEX_API_SANDBOX_PUB_KEY") || "";
  }

  bool IEXCloud::send_get_request(std::string key)
  {
    return Get(
        url(),
        cpr::Parameters{
            {"symbols" : data_.symbol_ || ""},
            {"types" : key},
            {"token" : api_key()}});
  }
} // namespace TPF
