#ifndef KMEANS_HPP
#define KMEANS_HPP
#include<cmath>
#include<vector>
#include<utility>
#include<valarray>

class KMeans{
public:
  KMeans(int k, std::vector<std::pair<double, double>>& data_);

  void clusterData(std::valarray<std::pair<double, double>>& init_means, int num_iters);

  void printClusters() const;

private:

  bool computeMeans();

  void assignLabels();

  int computeClosestCentroid(const std::pair<double, double>& point);

  int k;
  int features;
  std::valarray<std::pair<double, double> > means;
  std::valarray<std::vector<std::pair<double, double>>> data;

};

/**
 * vector<pair<double, double> > data =
 *   {{1.1, 1}, {1.4, 2}, {3.8,7}, {5.0, 8}, {4.3, 6},
 *    {8, 5.0}, {6, 8.5}, {3,2.0}, {9.1, 4}};
 *
 * KMeans km (2, data);
 *
 * valarray<pair<double, double>> init_means = {{1,1}, {3,4}};
 *
 * km.clusterData(init_means, 4);
 *
 *  km.printClusters();
 */

#endif//KMEANS_HPP
