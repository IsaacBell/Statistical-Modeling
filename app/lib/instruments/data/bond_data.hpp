#include <string>

namespace TPF
{
  struct BondData
  {
    double face_value;
    double coupon_rate;
    int maturity_years;
    std::string rating;
  };
} // namespace TPF
