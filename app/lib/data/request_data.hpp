#include <string>

namespace TPF
{
  struct APIRequestData
  {
    std::string_view api_url_;
    std::string_view symbol_;
    std::string_view auth_token_;
    std::string_view start_date_;
    std::string_view end_date_;
    std::string_view data_; // std::string_view data = "{\"key\": \"value\"}";
  };
} // namespace TPF
