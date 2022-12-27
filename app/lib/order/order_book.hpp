#include <unordered_map>
#include <algorithm>

namespace TPF
{
  using order_accessor = tbb::concurrent_hash_map<const std::string_view, Order>::accessor;

  class OrderBook
  {
  public:
    void add_order(int price, int volume);
    void cancel_order(int price, int volume);

    std::pair<int, int> get_best_bid() const;
    std::pair<int, int> get_best_ask() const;

  private:
    tbb::concurrent_hash_map<int, int> orders_; // map of price to volume
  };
}
