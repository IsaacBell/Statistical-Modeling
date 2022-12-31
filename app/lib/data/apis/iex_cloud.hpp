#ifndef _TPF_LIB_DATA_APIS_IEX_CLOUD_HPP_
#define _TPF_LIB_DATA_APIS_IEX_CLOUD_HPP_

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

namespace TPF
{

  class IEXCloud : API
  {
  public:
    bool Book();
    bool Company();
    bool Dividends();
    // bool Earnings();
    // bool EffectiveSpread();
    bool Financials();
    bool LargestTrades();
    bool News();
    bool Price();
    bool Quote();
    bool Relevant();
    // bool Splits();
    // bool TimeSeries();
    // bool VolumeByVenue();

    RequestData data_;

  private:
    const std::string url();
    const std::string api_key();
    bool send_get_request(std::string key);
  };
} // namespace TPF

#endif
