cmake_minimum_required(VERSION 3.12)
project(ZMPO4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ZMPO4 main.cpp KnapsackProblem.h KnapsackProblem.cpp GeneticAlgorithm.h Individual.cpp GeneticAlgorithm.cpp Problem.h)