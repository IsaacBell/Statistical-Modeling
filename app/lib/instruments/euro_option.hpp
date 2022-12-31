#include <random>
#include <string>
#include <Eigen/Dense>

#include "data/euro_option_data.hpp"

namespace TPF
{
  class EuroOption
  {
  public:
    EuroOption(EuroOptionData &data);

    Eigen::MatrixXd MonteCarloSimulation();

    double Price(const std::string_view &option_type) const;
    double Price(const std::string_view &option_type) const;

  private:
    EuroOptionData data_;
  };
}
