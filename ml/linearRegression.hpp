#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP
#include<cmath>
#include<tuple>
#include<limits>
#include<vector>
#include<numeric>

class LinearRegression{
public:

  LinearRegression(std::vector<double>& x_values,
                   std::vector<double>& y_values) :
    x_values(x_values), y_values(y_values),
    old_error(std::numeric_limits<double>::max()),
    no_of_elms(y_values.size()) {
  }
  ~LinearRegression() { }

  void trainAlgorithm(int num_iters, double a_init, double b_init);

  inline double regress(int x) { return slope*x + intercept; }

private:

  bool isConverged();

  std::vector<double> x_values;
  std::vector<double> y_values;

  double slope, intercept;
  double old_error, no_of_elms;
};

/**
 * vector<double> y({2.8, 2.9, 7.6, 9, 8.6});
 * vector<double> x({1, 2, 3, 4, 5});
 *
 * LinearRegression lr(x,y);
 * lr.trainAlgorithm(1000, 3, -10);
 *
 * cout << lr.regress(3) << endl;
 */

#endif//LINEARREGRESSION_HPP
