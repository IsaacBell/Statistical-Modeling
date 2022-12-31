#include <iostream>
#include <string>

#include "api.hpp"

namespace TPF
{
  API::API(APIRequestData &data) : data_(data) {}

  bool Get(std::string_view url = "", cpr::Parameters params = nullptr)
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
} // namespace TPF
