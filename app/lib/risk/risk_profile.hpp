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

    void add_position(const std::string_view &security, int volume, int price);
    void remove_position(const std::string &security, int volume, int price);

    int get_total_exposure() const;
    int get_total_position_size() const;
    int get_total_margin_requirement() const;
  };
} // namespace TPF
