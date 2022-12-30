#include <random>
#include <string>
#include <Eigen/Dense>

namespace TPF
{
  class EuroOption
  {
  public:
    EuroOption(double S0, double K, double r, double sigma, double T, int n_sims, int n_steps)
        : S0_(S0), K_(K), r_(r), sigma_(sigma), T_(T), n_sims_(n_sims), n_steps_(n_steps) {}

    Eigen::MatrixXd MonteCarloSimulation();

    double Price(const std::string_view &option_type);

  private:
    double S0_;
    double K_;
    double r_;
    double sigma_;
    double T_;
    int n_sims_;
    int n_steps_;
  };
}
