#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the fitness of a solution
double fitness(vector<double> x) {
  // Calculate the objective function value
  double f = x[0] * x[0] + x[1] * x[1];

  // Return the fitness value
  return f;
}

// Main function
int main() {
  // Define the problem parameters
  int n = 2; // Number of variables
  double lb = -5; // Lower bound of each variable
  double ub = 5; // Upper bound of each variable

  // Initialize the population
  vector<vector<double>> population(100, vector<double>(n));
  for (int i = 0; i < population.size(); i++) {
    for (int j = 0; j < n; j++) {
      population[i][j] = (lb + ub) * rand() / RAND_MAX;
    }
  }

  // Initialize the best solution
  vector<double> best = population[0];
  double best_fitness = fitness(best);

  // Iterate for a fixed number of iterations
  for (int i = 0; i < 100; i++) {
    // Teacher phase
    // Find the worst solution
    int worst_index = 0;
    for (int j = 1; j < population.size(); j++) {
      if (fitness(population[j]) > fitness(population[worst_index])) {
        worst_index = j;
      }
    }

    // Update the worst solution
    for (int j = 0; j < n; j++) {
      population[worst_index][j] = population[0][j];
    }

    // Learner phase
    // Find the best solution among the learners
    int best_learner_index = 0;
    for (int j = 1; j < population.size(); j++) {
      if (fitness(population[j]) < fitness(population[best_learner_index])) {
        best_learner_index = j;
      }
    }

    // Update the learners
    for (int j = 0; j < population.size(); j++) {
      for (int k = 0; k < n; k++) {
        population[j][k] = population[best_learner_index][k] +
                            rand() / RAND_MAX * (population[worst_index][k] -
                                                   population[best_learner_index][k]);
      }
    }

    // Update the best solution
    if (fitness(population[best_learner_index]) < best_fitness) {
      best = population[best_learner_index];
      best_fitness = fitness(best);
    }
  }

  // Print the best solution
  cout << "The best solution is: " << endl;
  for (int i = 0; i < n; i++) {
    cout << best[i] << " ";
  }
  cout << endl;

  // Print the fitness of the best solution
  cout << "The fitness of the best solution is: " << best_fitness << endl;

  return 0;
}


