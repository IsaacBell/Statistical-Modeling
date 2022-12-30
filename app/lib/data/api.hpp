#include <iostream>
#include <string>
#include <cpr/cpr.h>

namespace TPF
{
  struct API
  {
    std::string_view api_url;
    std::string_view auth_token;
    std::string_view data; // std::string_view data = "{\"key\": \"value\"}";

    API(const std::string_view &api_url, const std::string_view &auth_token, const std::string_view &data);

    bool post();
  };
} // namespace TPF
