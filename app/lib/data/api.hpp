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

    API(APIRequestData &data);

    virtual const std::string AlphaVantageQuery::url() const;
    virtual const std::string AlphaVantageQuery::api_key() const;

    bool Get();
    bool Post();
  };
} // namespace TPF

#endif
