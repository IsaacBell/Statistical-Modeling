#include <unordered_map>
#include <limits>
#include <string>
#include "tbb/concurrent_hash_map.h" // For concurrent hash map.

namespace TPF
{
  struct RiskProfile
  {
  public:
    struct Position
    {
      std::string security;
      int size_ = -1;
      int num_exposures_ = -1;
      int margin_requirements_ = -1;
    };

    tbb::concurrent_hash_map<const std::string_view, Position> portfolio_;
    typedef tbb::concurrent_hash_map<const std::string_view, Position>::accessor position_accessor;

    void add_position(const std::string_view &security, int volume, int price);
    void remove_position(const std::string &security, int volume, int price);

    int get_total_exposure() const;
    int get_total_position_size() const;
    int get_total_margin_requirement() const;
  };
} // namespace TPF
