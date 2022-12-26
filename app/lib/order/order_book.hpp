#include <unordered_map>
#include <algorithm>

namespace TPF
{
  using order_accessor = tbb::concurrent_hash_map<const std::string_view, Order>::accessor;

  class OrderBook
  {
  public:
    void add_order(int price, int volume)
    {
      order_accessor accessor;
      auto existing = orders_.find(accessor, price);
      if (existing)
        accessor->second += volume;
      else
        orders_.insert(accessor, volume);
    }

    void cancel_order(int price, int volume)
    {
      order_accessor accessor;
      auto existing = orders_.find(accessor, price);
      if (existing)
        accessor->second = std::max(accessor->second - volume, 0);
    }

    std::pair<int, int> get_best_bid() const
    {
      if (orders_.empty())
      {
        return {0, 0};
      }
      return {*orders_.crbegin(), orders_.crbegin()->second};
    }

    std::pair<int, int> get_best_ask() const
    {
      if (orders_.empty())
      {
        return {0, 0};
      }
      return {*orders_.cbegin(), orders_.cbegin()->second};
    }

  private:
    tbb::concurrent_hash_map<int, int> orders_; // map of price to volume
  };
}
