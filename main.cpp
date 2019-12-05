#include<iostream>
#include <ctime>
#include "src/Logger.h"
#include "src/Sudoku.h"
#include "src/SudokuGenerator.h"
#include "src/SimulatedAnnealing.h"
#include "src/GeneticAlgorithm.h"
#include "src/Backtrack.h"
using namespace std;

void testGeneticAlgorithm(int mat[9][9])
{
  GeneticAlgorithm Board(mat);

  // Parameters for Genetic algorithm
  int population_size=10; //size of Gene pool
  int stop=0; //number of generations to run until forced to stop; to go until completion set to 0
  //!!!PLEASE use steps of 10% when adjusting the parameters below to avoid segmentation faults!!!
  int elitism=10; //best percentage of candidates go to new gen unchanged; elitism=10 -> best 10%
  int eligible=50; //best percentage of candidates get to mate for new gen; eligible=50 -> best 50%
  float mutation=0.4; //chance of random gene for offspring instead of parents'; mutation=0.1 -> 10% chance

  Board.compute(population_size, elitism, eligible, mutation, stop);
}

void testSimulatedAnnealing()
{
  int index = 1;
  int trial = 1;
  int size = 9;
  Logger successLogger;
  successLogger.open("./logs/successLogger.txt");
  for(int num_empty = 2; num_empty  < 40; num_empty += 10){
    Sudoku a = SudokuGenerator::generateGuarantee(size, index, num_empty);
    SimulatedAnnealing b = SimulatedAnnealing(a);
    b.alpha = 0.9995;
    b.T = 4;
    //b.numIterations = 10;
    //b.Tmin = 2.0;
	  time_t start_time = time(NULL);
    bool result = b.run(num_empty);
	  time_t end_time = time(NULL);
    cout << trial << " : Result: "<<to_string(result)<<endl;
    vector<double> logRow;
    logRow.push_back(trial);
    logRow.push_back(end_time-start_time);
    logRow.push_back(size);
    logRow.push_back(index);
    logRow.push_back(num_empty);
    logRow.push_back(result);
    successLogger.log(logRow);
    trial += 1;
  }
  successLogger.close();
}
void testBacktrack()
{
  Sudoku a = SudokuGenerator::generateGuarantee(16, 1, 10);
  int result = Backtrack::run(a.size, a.board);
  cout << "RESULT: " << result << endl;
}

int main()
{

  int mat[9][9] =
    {
      {0, -1, -1, -1, -1, -1, -1, -1, 1},
      {-1, -1, 7, -1, -1, 8, -1, 2, 6},
      {6, -1, -1, 4, 2, -1, -1, 7, -1},
      {-1, 7, -1, -1, 6, 2, -1, 4, 3},
      {-1, -1, 5, 3, -1, 1, 6, -1, -1},
      {8, 6, -1, 7, 4, -1, -1, 0, -1},
      {-1, 0, -1, -1, 7, 6, -1, -1, 8},
      {2, 3, -1, 5, -1, -1, 7, -1, -1},
      {7, -1, -1, -1, -1, -1, -1, -1, 0}
    };
  
  //Sudoku::test();
  //testGeneticAlgorithm(mat);
  //testSimulatedAnnealing();
  //testBacktrack();
  return 0;
}