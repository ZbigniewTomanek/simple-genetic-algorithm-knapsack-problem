//
// Created by zbigi on 26.11.2018.
//

#include "KnapsackProblem.h"
#include <iostream>
using namespace std;

KnapsackProblem::KnapsackProblem(int i_problem_size, double i_knapsack_limit, double*& v_values, double*& v_weights, bool& result) : Problem() {
    if (i_knapsack_limit <= 0 || i_problem_size <= 0) {
        result = false;
        return;
    }

    problem_size = i_problem_size;
    knapsack_limit = i_knapsack_limit;

    values = new double[problem_size];
    weights = new double[problem_size];

    for (int i = 0; i < problem_size; ++i)
        values[i] = v_values[i];
    for (int i = 0; i < problem_size; ++i)
        weights[i] = v_weights[i];

    result = true;
}

KnapsackProblem::~KnapsackProblem() {
    delete[] values;
    delete[] weights;
}

double KnapsackProblem::calculate_value(int*& solution) {
    double value = 0;
    double weight = 0;

    for (int i = 0; i < problem_size; ++i) {
        if (solution[i] == 1) {
            value += values[i];
            weight += weights[i];
        }
    }

    if (weight <= knapsack_limit)
        return value;
    else
        return  0;
}

double KnapsackProblem::optimal_solution(double precision) {
    int reps = (int)(knapsack_limit / precision);

    double** results = new double* [problem_size + 1];
    for (int i = 0; i < problem_size + 1; ++i)
        results[i] = new double[reps + 1];

    for (int k = 0; k < reps; ++k)
        results[0][k] = 0;
    for (int k = 0; k < problem_size; ++k)
        results[k][0] = 0;

    for (int i = 1; i <= problem_size; i++) {
        for (int j = 1; j <= reps; j++) {
            int shift = (int) (weights[i - 1] / precision);
            if (j * precision > weights[i - 1] && results[i - 1][j] < results[i][j - shift] + values[i - 1])
                results[i][j] = results[i][j - shift] + values[i - 1];
            else
                results[i][j] = results[i - 1][j];
        }
    }

    double res = results[problem_size][reps];

    for (int i = 0; i < problem_size+1; ++i)
        delete [] results[i];
    delete [] results;

    return res;
}
