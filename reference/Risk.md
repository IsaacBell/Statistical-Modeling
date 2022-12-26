# Risk Profile

Model the current risk profile of an HFT system, including metrics such as position sizes, exposures, and margin requirements

```
#include <unordered_map>
#include <limits>

class RiskProfile {
 public:
  // Add a position to the risk profile
  void addPosition(const std::string &security, int volume, int price) {
    positions_[security] += volume;
    exposures_[security] += volume * price;
  }

  // Remove a position from the risk profile
  void removePosition(const std::string &security, int volume, int price) {
    positions_[security] = std::max(positions_[security] - volume, 0);
    exposures_[security] -= volume * price;
  }

  // Set the margin requirement for a security
  void setMarginRequirement(const std::string &security, int margin) {
    margin_requirements_[security] = margin;
  }

  // Get the current position size for a security
  int getPositionSize(const std::string &security) const {
    return positions_.at(security);
  }

  // Get the current exposure for a security
  int getExposure(const std::string &security) const {
    return exposures_.at(security);
  }

  // Get the margin requirement for a security
  int getMarginRequirement(const std::string &security) const {
    return margin_requirements_.at(security);
  }

  // Get the total position size
  int getTotalPositionSize() const {
    int total = 0;
    for (const auto &p : positions_) {
      total += p.second;
    }
    return total;
  }

  // Get the total exposure
  int getTotalExposure() const {
    int total = 0;
    for (const auto &e : exposures_) {
      total += e.second;
    }
    return total;
  }

  // Get the total margin requirement
  int getTotalMarginRequirement() const {
    int total = 0;
    for (const auto &m : margin_requirements_) {
      total += m.second;
    }
    return total;
  }

 private:
  std::unordered_map<std::string, int> positions_;       // map of security to position size
  std::unordered_map<std::string, int> exposures_;       // map of security to exposure
  std::unordered_map<std::string, int> margin_requirements_;  // map of security to margin requirement
};
```