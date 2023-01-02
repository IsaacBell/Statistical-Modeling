#ifndef _TPF_LIB_DATA_APIS_ALPHA_VANTAGE_HPP_
#define _TPF_LIB_DATA_APIS_ALPHA_VANTAGE_HPP_

#include "../api.hpp";

namespace TPF
{
  struct AlphaVantageAPI : API
  {
  public:
    bool GetHistoricalData();

  private:
    const std::string url() const;
    const std::string api_key() const;
  };
}

#endif
