# Eagle-Granger Test

The Engle-Granger test is a statistical technique used to determine whether pairs of financial instruments are cointegrated, meaning that they have a long-term equilibrium relationship.

```
#include <iostream>
#include <Eigen/Dense>

// Define the terms and parameters of the analysis

Eigen::VectorXd x; // Historical prices of instrument 1
Eigen::VectorXd y; // Historical prices of instrument 2

// Use a linear regression model to fit a line to the data

Eigen::VectorXd z = Eigen::VectorXd::Ones(x.size());
Eigen::VectorXd data = (z, x, y);
Eigen::VectorXd coefs = data.colPivHouseholderQr().solve(x);

// Calculate the residuals of the regression model

Eigen::VectorXd residuals = x - data * coefs;

// Use an Augmented Dickey-Fuller (ADF) test to determine whether the residuals are stationary

double adfStatistic = adfTest(residuals);

// If the ADF statistic is less than the critical value, it indicates that the residuals are stationary
// and that the two instruments are cointegrated

if (adfStatistic < criticalValue) {
  return true;
} else {
  return false;
}
```

This code uses a linear regression model to fit a line to the historical prices of two financial instruments, and calculates the residuals of the model. It then uses an Augmented Dickey-Fuller (ADF) test to determine whether the residuals are stationary, which indicates that the instruments are cointegrated.
