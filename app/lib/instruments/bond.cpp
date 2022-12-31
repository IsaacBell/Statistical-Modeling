#include <string>

#include "bond.hpp"

namespace TPF
{
  Bond::Bond(const BondData &data) : data_(data) {}

  double Bond::Price() const
  {
    return 0;
  }

  double Bond::Yield(double market_price) const
  {
    return 0;
  }

  // Method to calculate the maturity date of the bond
  std::time_t Bond::MaturityDate() const
  {
    std::time_t current_time = std::time(nullptr);
    std::tm *current_tm = std::localtime(&current_time);
    current_tm->tm_year += data_.maturity_years;
    return std::mktime(current_tm);
  }
} // namespace TPF
