//
// Created by zbigi on 26.11.2018.
//

#include "GeneticAlgorithm.h"
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(int i_population_size, int i_max_iterations, double i_mutation_chance,
                                   double i_crossing_chance, Problem& p) : problem(p), generator(), distribution(){

    generator = new std::mt19937(time(0));
    distribution = new std::uniform_real_distribution<double>(0, 1.0);

    max_adaptation = -1;
    iterations = 0;
    population_size = i_population_size;
    crossing_chance = i_crossing_chance;
    mutation_chance = i_mutation_chance;
    max_iterations = i_max_iterations;
    problem_size = p.get_problem_size();


    population = new Individual*[population_size];
    for (int i = 0; i < population_size; ++i)
        population[i] = new Individual(p, *generator, *distribution);

    adaptations = new double [population_size];
    for (int i = 0; i < population_size; ++i)
        adaptations[i] = -1;

}

GeneticAlgorithm::~GeneticAlgorithm() {
    for (int i = 0; i < population_size; ++i)
        delete population[i];

    delete generator;
    delete distribution;
    delete [] best_solution;
    delete [] population;
    delete [] adaptations;
}

int GeneticAlgorithm::find_parent() {

    std::uniform_real_distribution<double> dist = *distribution;
    std::mt19937 mt = *generator;

    int index1 = (int)(dist(mt) * population_size);
    int index2 = (int)(dist(mt) * population_size);
    int parent_index;

    if (adaptations[index1] == -1)
        adaptations[index1] = population[index1] -> adaptation();
    if (adaptations[index2] == -1)
         adaptations[index2] = population[index2] -> adaptation();

    if (adaptations[index1] > adaptations[index2])
        parent_index = index1;
    else
        parent_index = index2;

    return parent_index;
}

void GeneticAlgorithm::make_new_population() {
    int pop_index = 0;
    Individual** new_population = new Individual*[population_size];

    while (pop_index != population_size) {
        int parent1 = find_parent();
        int parent2 = find_parent();

        Individual** children = cross(parent1, parent2);

        if (population_size - pop_index == 1) {
            new_population[pop_index++] = children[0];
            delete children[1];
        }
        else {
            new_population[pop_index++] = children[0];
            new_population[pop_index++] = children[1];
        }
        delete [] children;
    }

    for (int i = 0; i < population_size; ++i)
        delete population[i];

    delete [] population;
    population = new_population;
}

void GeneticAlgorithm::mutate() {
    for (int i = 0; i < population_size; ++i)
        population[i] -> mutate(mutation_chance);
}

void GeneticAlgorithm::check_adaptation() {
        for (int i = 0; i < population_size; ++i) {
            if (adaptations[i] == -1) {
                adaptations[i] = population[i] -> adaptation();
            }


            if (adaptations[i] > max_adaptation) {
                max_adaptation = adaptations[i];
                delete [] best_solution;
                best_solution = population[i] -> get_genotype();
            }
        }
}

void GeneticAlgorithm::run() {
    while (iterations < max_iterations) {
        check_adaptation();
        make_new_population();
        mutate();
        iterations++;
    }
}

Individual**& GeneticAlgorithm::cross(int parent1_index, int parent2_index) {
    Individual** individuals;
    std::uniform_real_distribution<double> dist = *distribution;
    std::mt19937 mt = *generator;

    if (dist(mt) < crossing_chance) {
        adaptations[parent1_index] = -1;
        adaptations[parent2_index] = -1;
        individuals = population[parent1_index] -> cross(*population[parent2_index]);
    }
    else {
        individuals =  new Individual*[2];
        individuals[0] = new Individual(*population[parent1_index]);
        individuals[1] = new Individual(*population[parent2_index]);
    }


    Individual**& res = individuals;
    return res;
}

int*& GeneticAlgorithm::get_best_solution() {
    int* copy = new int[problem_size];
    for (int i = 0; i < problem_size; ++i)
        copy[i] = best_solution[i];
    int*& res = copy;
    return res;
}

double GeneticAlgorithm::get_max_adaptation() {
    return max_adaptation;
}