#include"neuralNetwork.hpp"
#include<iostream>
#include<random>
#include<ctime>
using namespace std;

NeuralNetwork::NeuralNetwork() {
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<double> distribution(-1,1);
  weights.push_back( distribution(gen) );
  weights.push_back( distribution(gen) );
  weights.push_back( distribution(gen) );
}

double NeuralNetwork::think(vector<double>& neuron_inputs) {
  double _sum_of_weighted_inputs = this->sum_of_weighted_inputs(neuron_inputs);
  double neuron_output = this->sigmoid(_sum_of_weighted_inputs);
  return neuron_output;
}

void NeuralNetwork::train(vector<vector<double>>& input_training_set,
                          vector<double>& output_training_set,
                          int num_iters) {
  int iter = 0;
  while (iter < num_iters) {
    for (unsigned i=0; i<input_training_set.size(); ++i) {
      double predicted_output = this->think(input_training_set[i]);

      double error_in_output = output_training_set[i] - predicted_output;

      for (unsigned j=0; j<weights.size(); ++j) {
        double neuron_input = input_training_set[i][j];

        double adjust_weight = neuron_input * error_in_output * this->sigmoid_gradient(predicted_output);

        weights[j] += adjust_weight;
      }
    }
    iter++;
  }
}

void NeuralNetwork::_printWeights() {
  for (auto const& weight: weights)
    cout << weight << ", ";
  cout << endl;
}

double NeuralNetwork::sum_of_weighted_inputs(vector<double>& neuron_inputs) {
  double _sum_of_weighted_inputs = .0;
  for (unsigned i=0; i<neuron_inputs.size(); ++i)
    _sum_of_weighted_inputs += this->weights[i] * neuron_inputs[i];
  return _sum_of_weighted_inputs;
}
