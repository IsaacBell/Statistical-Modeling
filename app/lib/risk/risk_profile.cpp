#include <unordered_map>
#include <limits>
#include <string>

#include "risk_profile.hpp"

namespace TPF
{
  void Risk::Profile::add_position(const std::string_view &security, int volume, int price)
  {
    position_accessor accessor;
    if (portfolio_.find(accessor, security))
      // log(accessor->first, accessor->second);
      return;

    Risk::Position pos;
    pos.security = security;
    pos.size_ = volume;
    pos.num_exposures_ = volume * price;

    portfolio_.insert(security, pos);
  }

  void Risk::Profile::remove_position(const std::string &security, int volume, int price)
  {
    position_accessor accessor;
    auto pos = portfolio_.find(accessor, security);
    // if (!pos) return;
    pos.size_ = std::max(pos.size_ - volume, 0);
    pos.num_exposures_ = std::max(pos.num_exposures_ - (volume * price), 0);
  }

  int Risk::Profile::get_total_position_size() const
  {
    int total = 0;
    for (const auto &p : portfolio_)
    {
      total += p.second;
    }
    return total;
  }

  int Risk::Profile::get_total_exposure() const
  {
    int total = 0;
    for (const auto &e : exposures_)
    {
      total += e.second;
    }
    return total;
  }

  int Risk::Profile::get_total_margin_requirement() const
  {
    int total = 0;
    for (const auto &m : margin_requirements_)
    {
      total += m.second;
    }
    return total;
  }
} // namespace TPF
