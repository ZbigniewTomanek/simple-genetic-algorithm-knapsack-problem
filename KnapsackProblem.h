//
// Created by zbigi on 26.11.2018.
//

#ifndef ZMPO4_KNAPSACKPROBLEM_H
#define ZMPO4_KNAPSACKPROBLEM_H

#include "Problem.h"

class KnapsackProblem : public Problem {
private:
    int problem_size;
    double* values;
    double* weights;
    double knapsack_limit;

public:
    KnapsackProblem(int problem_size, double knapsack_limit, double*& v_values, double*& v_weights, bool& result);
    KnapsackProblem() = default;
    ~KnapsackProblem();

    virtual double calculate_value(int*& solution);
    double optimal_solution(double precision);
    virtual int get_problem_size()  { return problem_size; };
};

#endif //ZMPO4_KNAPSACKPROBLEM_H
