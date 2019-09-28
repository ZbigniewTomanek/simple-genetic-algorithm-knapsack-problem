//
// Created by zbigi on 26.11.2018.
//

#ifndef ZMPO4_GENETICALGORITHM_H
#define ZMPO4_GENETICALGORITHM_H

#include "Problem.h"
#include <random>
#include <time.h>

class Individual {
private:
    int genotype_size;
    int* genotype;
    Problem& problem;
    std::mt19937& generator;
    std::uniform_real_distribution<double>& distribution;

public:
    Individual(Problem& p, std::mt19937& generator, std::uniform_real_distribution<double>& distribution);
    Individual(int*& genotype, Problem& p, std::mt19937& generator, std::uniform_real_distribution<double>& distribution);
    Individual(Individual& other);
    ~Individual();

    void mutate(double mutation_chance);
    Individual**& cross(Individual& other);
    double adaptation();
    int*& get_genotype();
};

class GeneticAlgorithm {
private:
    int problem_size;

    Problem& problem;

    int iterations;
    int max_iterations;

    int* best_solution;
    double max_adaptation;

    double mutation_chance;
    double crossing_chance;

    int population_size;
    Individual** population;

    double* adaptations;

    std::mt19937* generator;
    std::uniform_real_distribution<double>* distribution;

private:
    int find_parent();
    Individual**& cross(int parent1_index, int parent2_index);
    void make_new_population();
    void check_adaptation();
    void mutate();

public:
    GeneticAlgorithm(int i_population_size,  int i_max_iterations,
            double i_mutation_chance, double i_crossing_chance, Problem& p);
    ~GeneticAlgorithm();

    int*& get_best_solution();
    double get_max_adaptation();
    void run();




};

#endif //ZMPO4_GENETICALGORITHM_H
