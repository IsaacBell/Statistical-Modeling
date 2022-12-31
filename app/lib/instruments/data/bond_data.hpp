#include <string>

namespace TPF
{
  struct BondData
  {
    double price_; // for yield calcs
    double face_value_;
    double coupon_rate_;
    double market_rate_; // Market interest rate
    int maturity_years_;
    int n_coupons_;
    std::string_view rating_;
  };
} // namespace TPF
