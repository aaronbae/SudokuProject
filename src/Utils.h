#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <random>
#include <string>
#include <cmath>
#include "Sudoku.h"
using namespace std;

class Utils
{
  public:
    static string GENES;
    const static int SRN = 3;
    const static int N = 9;
    
    // ranodom provider
    static void seed();
    static double random();
    static int randomGenerator(int num);
    static int random_num(int start, int end);

    // heuristics
    static char mutated_genes();
    static int fitness(Sudoku s);

};
#endif