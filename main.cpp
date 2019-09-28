#include <iostream>
#include "vector"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"

using namespace std;

void printGenotype(int*& tab, int tab_size) {
    for (int i = 0; i < tab_size; ++i) {
        cout << tab[i] << " ";
    }
    delete [] tab;
    cout << endl;
}

int main() {
    bool result;
    int problem_size = 5;
    double* weights = new double [problem_size];
    double* values = new double [problem_size];

    srand(time(0));

    const int max_weight = 8;
    const int max_value = 16;


    for (int i = 0; i < problem_size; ++i) {
        weights[i] = rand() % max_weight;
        values[i] = rand() % max_value;
    }


    const double knapsack_limit = 1.5*problem_size;
    KnapsackProblem k(problem_size, knapsack_limit, values, weights, result);

    cout << "All objects(weight, value): " << endl;
    for (int i = 0; i < problem_size; ++i)
        cout << i << " -> (" << weights[i] << ", " << values[i] << ")\n";
    cout << "\nKnapsack limit: " << knapsack_limit << endl << endl;

    delete [] weights;
    delete [] values;

    if (result) {
        cout << "Dynamically calculated approximation of best solution: " << k.optimal_solution(0.1) << endl;
        const int pop_size = 100;
        const int reps = 100;
        const double mutation_chance = 0.9;
        const double crossing_chance = 0.5;

        cout << "Algorithm parameters:\n" << "Population size: " << pop_size << "\nNum of iterations: "
        << reps << "\nMutation chance: " << mutation_chance << "\nCrossing chance: " << crossing_chance;


        GeneticAlgorithm* g = new GeneticAlgorithm(pop_size, reps, mutation_chance, crossing_chance, k);
        g -> run();
        cout << endl << "\n\nAlgorithm result: " <<  g -> get_max_adaptation();

        cout << "\n Genotype of best solution: \n";
        int* genotype = g -> get_best_solution();
        for (int i = 0; i < problem_size; ++i)
            cout << genotype[i] << " ";

        delete g;
    } else cout << "Erorr";


    return 0;
}