#include <string>

#include "bond.hpp"

namespace TPF
{
  Bond::Bond(const BondData &data) : data_(data) {}

  double Bond::Price() const noexcept
  {
    double price = 0;
    for (int i = 0; i < data_.n_coupons_; i++)
      price += data_.face_value_ * data_.coupon_rate_ / data_.n_coupons_ / (1 + data_.market_rate_ / data_.n_coupons_);
    price += data_.face_value_ / (1 + data_.market_rate_ / data_.n_coupons_);
    return price;
  }

  double Bond::Yield(double market_price) const noexcept
  {
    double yield = 0;
    double yield_increment = 0.001;
    double max_yield = 1;
    double min_yield = 0;

    while (max_yield - min_yield > 0.00001)
    {
      double bondPrice = 0;
      yield = (max_yield + min_yield) / 2;

      for (int i = 0; i < data_.n_coupons_; i++)
        bondPrice += data_.face_value_ * data_.market_rate_ / data_.n_coupons_ / (1 + yield / data_.n_coupons_);
      bondPrice += data_.face_value_ / (1 + yield / data_.n_coupons_);

      if (bondPrice > data_.price_)
        max_yield = yield;
      else
        min_yield = yield;
    }
    return yield;
  }

  // Method to calculate the maturity date of the bond
  std::time_t Bond::MaturityDate() const
  {
    std::time_t current_time = std::time(nullptr);
    std::tm *current_tm = std::localtime(&current_time);
    current_tm->tm_year += data_.maturity_years_;
    return std::mktime(current_tm);
  }
} // namespace TPF
