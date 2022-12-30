#include <random>
#include <string>
#include <Eigen/Dense>

namespace TPF
{
  EuroOption : EuroOption(double S0, double K, double r, double sigma, double T, int n_sims, int n_steps)
      : S0_(S0), K_(K), r_(r), sigma_(sigma), T_(T), n_sims_(n_sims), n_steps_(n_steps) {}

  Eigen::MatrixXd EuroOption::MonteCarloSimulation()
  {
    double dt = T_ / n_steps_;
    Eigen::MatrixXd S(n_steps_ + 1, n_sims_);
    S.row(0) = Eigen::VectorXd::Constant(n_sims_, S0_);
    std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(0.0, 1.0);
    for (int t = 1; t <= n_steps_; ++t)
    {
      for (int i = 0; i < n_sims_; ++i)
      {
        double z = distribution(generator);
        S(t, i) = S(t - 1, i) * std::exp((r_ - sigma_ * sigma_ / 2) * dt + sigma_ * std::sqrt(dt) * z);
      }
    }
    return S;
  }

  double EuroOption::Price(const std::string_view &option_type)
  {
    Eigen::MatrixXd S = MonteCarloSimulation();
    Eigen::VectorXd payoffs(n_sims_);
    if (option_type == "call")
    {
      payoffs = (S.row(n_steps_).array() - K_).max(0.0);
    }
    else if (option_type == "put")
    {
      payoffs = (K_ - S.row(n_steps_).array()).max(0.0);
    }
    else
    {
      throw std::invalid_argument("Option type must be either 'call' or 'put'");
    }
    double mean_payoff = payoffs.mean();
    return mean_payoff * std::exp(-r_ * T_);
  }
}
