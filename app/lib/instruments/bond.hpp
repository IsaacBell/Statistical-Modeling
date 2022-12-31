#include <string>

#include "data/bond_data.hpp"

namespace TPF
{
  class Bond
  {
  public:
    Bond(const BondData &data);

    double Price() const;

    double Yield(double market_price) const;

    std::time_t MaturityDate() const;

  private:
    BondData data_;
  };
} // namespace TPF
