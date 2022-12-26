# OrderBook

Trivial example
```
#include <unordered_map>
#include <algorithm>

class OrderBook {
 public:
  // Add an order to the order book
  void addOrder(int price, int volume) {
    orders_[price] += volume;
  }

  // Cancel an order from the order book
  void cancelOrder(int price, int volume) {
    orders_[price] = std::max(orders_[price] - volume, 0);
  }

  // Get the best bid price and volume
  std::pair<int, int> getBestBid() const {
    if (orders_.empty()) {
      return {0, 0};
    }
    return {*orders_.crbegin(), orders_.crbegin()->second};
  }

  // Get the best ask price and volume
  std::pair<int, int> getBestAsk() const {
    if (orders_.empty()) {
      return {0, 0};
    }
    return {*orders_.cbegin(), orders_.cbegin()->second};
  }

 private:
  std::unordered_map<int, int> orders_;  // map of price to volume
};
```