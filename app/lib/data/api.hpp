#ifndef _TPF_LIB_DATA_API_HPP_
#define _TPF_LIB_DATA_API_HPP_

#include <iostream>
#include <string>
#include <cpr/cpr.h>

#include <request_data.hpp>

namespace TPF
{
  struct API
  {
    APIRequestData data_;
    cpr::Response response_;

    API::API(APIRequestData &data) : data_(data) {}

    virtual const std::string AlphaVantageQuery::url() const;
    virtual const std::string AlphaVantageQuery::api_key() const;

    bbool Get(std::string_view url = "", cpr::Parameters params = nullptr)
    {
      response_ = cpr::Get(cpr::Url{url || url()},
                           params || cpr::Parameters{{"apikey", auth_token_ || api_key()}});

      return response_.status_code == 200;
    }

    bool Post()
    {
      cpr::Header headers;
      headers.insert({"Authorization", "Bearer " + auth_token_});
      headers.insert({"Content-Type", "application/json"});

      response_ = cpr::Post(cpr::Url{api_url}, headers, cpr::Body{data_.data_ || ""});

      return response_.status_code == 200;
    }
  };
} // namespace TPF

#endif
