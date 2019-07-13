#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP
#include<cmath>
#include<vector>

class NeuralNetwork{

public:

  NeuralNetwork();

  double think(std::vector<double>& neuron_inputs);

  void train(std::vector<std::vector<double>>& input_training_set,
             std::vector<double>& output_training_set,
             int num_iters=10000);

  void _printWeights();

private:

  inline double sigmoid(double d) { return 1 / (1 + exp(-d)); }

  inline double sigmoid_gradient(double d) { return d * (1 - d); }

  double sum_of_weighted_inputs(std::vector<double>& neuron_inputs);

  std::vector<double> weights;
};

/**
 * vector<vector<double>> inputs{{0, 0, 1},
 *                               {1, 1, 1},
 *                               {1, 0, 1},
 *                               {0, 1, 1}};
 * vector<double> outputs = {0,
 *                           1,
 *                           1,
 *                           0};
 *
 * NeuralNetwork nn;
 *
 * nn._printWeights();
 * nn.train(inputs, outputs);
 * nn._printWeights();
 *
 * vector<double> new_situation{1, 0, 0};
 * cout << nn.think(new_situation) << endl;
 */

#endif//NEURALNETWORK_HPP
