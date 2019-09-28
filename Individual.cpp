//
// Created by zbigi on 26.11.2018.
//

#include "GeneticAlgorithm.h"
#include <iostream>

static const int MAX_TRIES = 100;

Individual::Individual(Problem& p, std::mt19937& gen,
        std::uniform_real_distribution<double>& distrib) : problem(p), generator(gen), distribution(distrib) {
    distribution = distrib;
    generator = gen;
    problem = p;
    genotype_size = p.get_problem_size();
    genotype = new int[genotype_size];

    int tries = 0;
    while (p.calculate_value(genotype) <= 0) {
        for (int i = 0; i < genotype_size; ++i) {
            double number = distribution(generator);
            if (number < 0.5)
                genotype[i] = 0;
            else
                genotype[i] = 1;

        }
    }
}

Individual::Individual(int *& i_genotype, Problem& p, std::mt19937& gen,
                       std::uniform_real_distribution<double>& distrib) : problem(p), generator(gen), distribution(distrib){
    genotype_size = p.get_problem_size();
    problem = p;

    distribution = distrib;
    generator = gen;

    genotype = new int[genotype_size];
    for (int i = 0; i < genotype_size; ++i)
        genotype[i] = i_genotype[i];
}

Individual::Individual(Individual& other) : problem(other.problem), generator(other.generator), distribution(other.distribution) {
    genotype_size = other.genotype_size;
    genotype = new int[genotype_size];

    for (int i = 0; i < genotype_size; ++i)
        genotype[i] = other.genotype[i];

    problem = other.problem;
}

Individual::~Individual() {
    delete [] genotype;
}

double Individual::adaptation() {
    return problem.calculate_value(genotype);
}

void Individual::mutate(double mutation_chance) {
    for (int i = 0; i < 0; ++i) {
        if (distribution(generator) < mutation_chance) //
            genotype[i] = !(genotype[i]);
    }
}

Individual**& Individual::cross(Individual& other) {

    int cross_point = int(distribution(generator) * (genotype_size - 1)) + 1;
    int* first_child = new int [genotype_size];
    int* second_child = new int [genotype_size];

    for (int i = 0; i < cross_point; ++i) {
        first_child[i] = genotype[i];
        second_child[i] = other.genotype[i];
    }

    for (int i = cross_point; i < genotype_size; ++i) {
        first_child[i] = other.genotype[i];
        second_child[i] = genotype[i];
    }

    Individual** children = new Individual*[2];
    children[0] = new Individual(first_child, problem, generator, distribution);
    children[1] = new Individual(second_child, problem, generator, distribution);

    delete [] first_child;
    delete [] second_child;
    Individual**& res = children;

    return res;
}

int*& Individual::get_genotype() {
    int* gen = new int[genotype_size];
    for (int i = 0; i < genotype_size; ++i)
        gen[i] = genotype[i];

    int*& res = gen;
    return res;
}