#include<iostream>
#include"linearRegression.hpp"
using namespace std;

void LinearRegression::trainAlgorithm(int num_iters, double a_init, double b_init) {

  int iter = 0;
  slope = a_init;
  intercept = b_init;

  while (!isConverged() && iter < num_iters) {
    // Update the gradient
    double step = 2 / double(iter + 2);
    double a_grad = 0;
    double b_grad = 0;

    // Compute the gradient of error wrt to a
    for (int i = 0; i < no_of_elms; ++i) {
      a_grad += x_values[i] * ((slope * x_values[i] + intercept) - y_values[i]);
    }
    a_grad = (2 * a_grad) / no_of_elms;

    // Compute the gradient of error wrt to b
    for (int j = 0; j < no_of_elms; ++j) {
      b_grad += ((slope * x_values[j] + intercept) - y_values[j]);
    }
    b_grad = (2 * b_grad) / no_of_elms;

    // take a step
    slope = slope - (step * a_grad);
    intercept = intercept - (step * b_grad);

    cout << "slope:\t" << slope << ", intercept:\t" << intercept << "\n";
    cout << "a_grad:\t" << a_grad << ", b_grad:\t" << b_grad << "\n";
    iter++;
  }
}

bool LinearRegression::isConverged() {
  double error = 0;
  double thresh = 0.01;
  for (int i = 0; i < no_of_elms; ++i) {
    error += ((slope * x_values[i] + intercept) - y_values[i]) * ((slope * x_values[i] + intercept) - y_values[i]);
  }
  error /= no_of_elms;
  cout << "Error: " << error << endl;
  bool res = (abs(error) > old_error - thresh && abs(error) < old_error + thresh) ? true : false;
  old_error = abs(error);
  return res;
}
