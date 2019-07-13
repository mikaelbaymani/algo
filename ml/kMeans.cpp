#include<iostream>
#include"kMeans.hpp"
using namespace std;

KMeans::KMeans(int k, vector<pair<double, double>>& data_) : k(k), means(k), data(k) {
  data[0] = data_;
}

void KMeans::clusterData(valarray<pair<double, double>>& init_means, int num_iters) {
  means = init_means;
  this->assignLabels();

  int i = 0;
  while (i < num_iters && !this->computeMeans()) {
    cout << "Running iteration: " << i << endl;
    this->assignLabels();
    i++;
  }
}

void KMeans::printClusters() const {
  for (int i = 0; i < k; ++i) {
    for (const auto & it : data[i]) {
      cout << "[" << get<0>(it) << ", " << get<1>(it) << "] ";
    }
    cout << endl;
  }
}

bool KMeans::computeMeans() {
  bool res = true;
  for (int i = 0; i < k; ++i) {
    pair<double, double> mean(0,0);
    int num_features_of_k = data[i].size();
    for (auto const & it : data[i]) {
      get<0>(mean) += get<0>(it);
      get<1>(mean) += get<1>(it);
    }
    get<0>(mean) /= num_features_of_k;
    get<1>(mean) /= num_features_of_k;
    res = (means[i] == mean && res == true) ? true : false;
    means[i] = mean;
    cout << "Cluster centroid " << i << ":\tx " << get<0>(mean)
         << ", y " << get<1>(mean) << "\t";
  }
  cout << endl;
  return res;
}

void KMeans::assignLabels() {
  valarray<vector<pair<double, double>>> new_data(k);
  for (auto const & clust : data) {
    for (auto const & feature : clust) {
      int closest_mean = this->computeClosestCentroid(feature);
      new_data[closest_mean].push_back(feature);
    }
  }
  data = new_data;
}

int KMeans::computeClosestCentroid(const pair<double, double>& point) {
  valarray<double> distances(k);
  for (int i = 0; i < k; ++i) {
    double del_x = get<0>(point) - get<0>(means[i]);
    double del_y = get<1>(point) - get<1>(means[i]);
    double dist = sqrt((del_x * del_x) + (del_y * del_y));
    distances[i] = dist;
  }
  auto closest_mean = distance(begin(distances), min_element(begin(distances), end(distances)));
  return closest_mean;
}

// eof
