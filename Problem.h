//
// Created by zbigi on 27.11.2018.
//

#ifndef ZMPO4_PROBLEM_H
#define ZMPO4_PROBLEM_H

class Problem {
public:
    Problem() = default;
    virtual double calculate_value(int*& solution) = 0;
    virtual int get_problem_size() = 0;
};

#endif //ZMPO4_PROBLEM_H
