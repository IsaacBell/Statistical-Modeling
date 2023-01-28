#include <unordered_map>
#include <limits>
#include <string>
#include "tbb/concurrent_hash_map.h" // For concurrent hash map.

namespace TPF
{
  struct Risk::Position
  {
    std::string security_;
    int size_ = -1;
    int num_exposures_ = -1;
    int margin_requirements_ = -1;
  };

  struct Risk::Profile
  {
    using order_accessor = tbb::concurrent_hash_map<const std::string_view, Order>::accessor;
    using portfolio = tbb::concurrent_hash_map<const std::string_view, Risk::Position>;

  public:
    portfolio portfolio_;

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
  };
} // namespace TPF
