#include <unordered_map>
#include <algorithm>

#include "order_book.hpp"

namespace TPF
{
  void OrderBook::add_order(int price, int volume)
  {
    order_accessor accessor;
    auto existing = orders_.find(accessor, price);
    if (existing)
      accessor->second += volume;
    else
      orders_.insert(accessor, volume);
  }

  void OrderBook::cancel_order(int price, int volume)
  {
    order_accessor accessor;
    auto existing = orders_.find(accessor, price);
    if (existing)
      accessor->second = std::max(accessor->second - volume, 0);
  }

  std::pair<int, int> OrderBook::get_best_bid() const
  {
    if (orders_.empty())
    {
      return {0, 0};
    }
    return {*orders_.crbegin(), orders_.crbegin()->second};
  }

  std::pair<int, int> OrderBook::get_best_ask() const
  {
    if (orders_.empty())
    {
      return {0, 0};
    }
    return {*orders_.cbegin(), orders_.cbegin()->second};
  }
}
