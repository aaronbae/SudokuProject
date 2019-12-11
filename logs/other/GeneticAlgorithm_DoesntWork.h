#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <ctime>
#include "Utils.h"

using namespace std;

class GeneticAlgorithm
{
  private:    
    int size;
    Sudoku initial;
    
    // helper variables
    vector<pair<int, int>> freePoints;
    vector<Sudoku> population;
    vector<pair<int, int>> fitness_map;
    void destroy_population();

  public:
    int generation_count;
    int population_size;
    float mutation_chance;
    int max_generation;
    
    GeneticAlgorithm(Sudoku inputBoard);
    GeneticAlgorithm(int inputPopSize, int inputMutChance, int maxGen, Sudoku inputBoard);

    void fill_empty_cells_in_population();
    void update_selection_order();
    pair<int, int> select();
    Sudoku mate(int i, int j);
    void nextGeneration();

    void print_fitness_map();
    Sudoku solution();
    void destroy();

    bool run();
};

#endif