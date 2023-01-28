#include <random>
#include <string>
#include <Eigen/Dense>

#include "data/euro_option_data.hpp"

namespace TPF
{
  class EuroOption
  {
  public:
    EuroOption::EuroOption(EuroOptionData &data) : data_(data) {}

    Eigen::MatrixXd EuroOption::MonteCarloSimulation()
    {
      double dt = data_.T_ / data_.n_steps_;
      Eigen::MatrixXd S(data_.n_steps_ + 1, data_.n_sims_);

      S.row(0) = Eigen::VectorXd::Constant(data_.n_sims_, data_.S0_);
      std::mt19937 generator(std::random_device{}());
      std::normal_distribution<double> distribution(0.0, 1.0);

      for (int t = 1; t <= data_.n_steps_; ++t)
      {
        for (int i = 0; i < data_.n_sims_; ++i)
        {
          double z = distribution(generator);
          S(t, i) = S(t - 1, i) * std::exp((data_.r_ - data_.sigma_ * data_.sigma_ / 2) * dt + data_.sigma_ * std::sqrt(dt) * z);
        }
      }

      return S;
    }

    double EuroOption::Price(int option_type) const
    {
      Eigen::MatrixXd S = MonteCarloSimulation();
      Eigen::VectorXd payoffs(data_.n_sims_);
      if (option_type == 1)
      {
        payoffs = (S.row(data_.n_steps_).array() - K_).max(0.0);
      }
      else if (option_type == 2)
      {
        payoffs = (K_ - S.row(data_.n_steps_).array()).max(0.0);
      }
      else
      {
        throw std::invalid_argument("Option type must be either 'call' or 'put'");
      }
      double mean_payoff = payoffs.mean();
      return mean_payoff * std::exp(-data_.r_ * data_.T_);
    }

    double EuroOption::Price(const std::string_view &option_type) const
    {
      return option_type == "call" ? Price(1) : Price(2);
    }

  private:
    EuroOptionData data_;
  };
}
