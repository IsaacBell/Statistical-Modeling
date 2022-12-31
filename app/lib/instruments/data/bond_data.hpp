#include <string>

namespace TPF
{
  struct BondData
  {
    double face_value_;
    double coupon_rate_;
    int maturity_years_;
    std::string_view rating_;
  };
} // namespace TPF
