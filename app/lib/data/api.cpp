#include <iostream>
#include <string>

#include "api.hpp"

namespace TPF
{
  API::API(const std::string_view &api_url, const std::string_view &auth_token, const std::string_view &data)
      : api_url(api_url), auth_token(auth_token), data(data) {}

  bool post()
  {
    // Set the request headers
    cpr::Header headers;
    headers.insert({"Authorization", "Bearer " + auth_token});
    headers.insert({"Content-Type", "application/json"});

    // Make the POST request
    auto response = cpr::Post(cpr::Url{api_url}, headers, cpr::Body{data});

    // Check the status code of the response
    if (response.status_code == 200)
    {
      return true;
    }
    else
    {
      std::cerr << "Error: " << response.status_code << "\n";
      return false;
    }
  }
} // namespace TPF
