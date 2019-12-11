#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(Sudoku inputBoard)
{
  int inputPopSize = 10;
  int inputMutChance = 0.2;
  int max_generation = 100000;
  *this = GeneticAlgorithm(inputPopSize, inputMutChance, max_generation, inputBoard);
}
GeneticAlgorithm::GeneticAlgorithm(int inputPopSize, int inputMutChance, int maxGen, Sudoku inputBoard)
{
  generation_count = 0;
  population_size = inputPopSize;
  mutation_chance = inputMutChance;
  max_generation = maxGen;
  
  size = inputBoard.size;
  initial = inputBoard.copy();
  freePoints.clear();
  
  // Init freePoints
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      int val = initial.board[i][j];
      if(val == -1)
      {
        freePoints.push_back(pair<int, int>(i,j));
      }
    }
  }
  // initialize population
  for(int _ = 0; _ < population_size; _++)
  { 
    // new individual
    Sudoku individual = initial.copy();
    population.push_back(individual);
  }
}
void GeneticAlgorithm::fill_empty_cells_in_population()
{
  int* countMissing;
  for(int i = 0; i < population_size; i++)
  {
    cout << "======================="<< endl;
    Sudoku individual = population[i];
    vector<pair<int, int>> individual_freePoints;
    // init an array of numbers missing
    countMissing = new int(size);
    for (int i = 0; i < size; i++)
    {
      countMissing[i] = size; 
    }
    cout << "SHIT" << endl;
    // Init canChagne matrix and gather countMissing data
    for (int i = 0; i < size; i++)
    {
      for (int j = 0; j < size; j++)
      {
        int val = individual.board[i][j];
        cout << i << " , " << j << " : "<< val;
        if(val == -1)
        {
          individual_freePoints.push_back(pair<int, int>(i,j));
          cout << endl;
        } else 
        {
          cout << " - " << countMissing[val];
          countMissing[val] -= 1;
          cout << ", " << countMissing[val] << endl;
        }
      }
    }
    cout << "SHIT" << endl;
    
    // assign 'count' many 'val' values
    for(int val = 0; val < size; val++)
    {
      int count = countMissing[val];
      while(count > 0)
      {
        int k = Utils::randomGenerator(individual_freePoints.size());
        pair<int, int> p = individual_freePoints[k];
        int i = p.first;
        int j = p.second;
        // assign only if we haven't yet
        if(individual.board[i][j] == -1)
        {
          individual.board[i][j] = val;
          count -= 1;
        }
      }
    }
    cout << "SHIT" << endl;
  }
}
void GeneticAlgorithm::update_selection_order()
{
  fitness_map.clear();
  // initialize fitness_map
  for(int i = 0; i < population_size; i++)
  {
    int fit = Utils::fitness(population[i]);
    fitness_map.push_back(pair<int, int>(fit, i));
  }
  sort(fitness_map.begin(), fitness_map.end());
}
pair<int, int> GeneticAlgorithm::select()
{
  // probability curve 
  int i = min(population_size, int(exp(population_size * (0.23 - Utils::random())) + 0.9)) % population_size;
  int j = min(population_size, int(exp(population_size * (0.23 - Utils::random())) + 0.9)) % population_size;
  return pair<int, int>(i, j); 
}
Sudoku GeneticAlgorithm::mate(int i, int j)
{
  Sudoku child = population[i].copy();
  Sudoku parent_j = population[j];
  /*
  // cell grab
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < size; j++)
    {
      double chance = Utils::random();
      if(chance < 0.5)
      {
        child.board[i][j] = parent_j.board[i][j];
      }
    }
  }
  */
  // row grab
  for(int i = 0; i < size; i++)
  {
    double chance = Utils::random();
    if(chance < 0.5)
    {
      for(int j = 0; j < size; j++)
      {
        child.board[i][j] = parent_j.board[i][j];
      }
    }
  }
  // mutation
  for(int k = 0; k < freePoints.size(); k++)
  {
    double chance = Utils::random();
    if(chance < 0.4)
    {
      pair<int, int> p = freePoints[k];
      int i = p.first;
      int j = p.second;
      child.board[i][j] = -1;
    }
  }
  // fill in the mutated/ empty
  fill_empty_cells_in_population(); 
  return child;
}
void GeneticAlgorithm::nextGeneration()
{
  vector<Sudoku> new_population;
  for(int i = 0; i < population_size; i++)
  {
    pair<int, int> p = select();
    //cout << p.first << " , " << p.second << endl;
    Sudoku child = mate(p.first, p.second);
    cout << "SHIT"<< endl;
    new_population.push_back(child);
  }
  cout << "SHIT"<< endl;
  destroy_population();
  population = new_population;
  fill_empty_cells_in_population(); // take care of mutation / -1's 
  update_selection_order();
  print_fitness_map();
}

// Helper FUnctions
void  GeneticAlgorithm::print_fitness_map()
{
  for(int i = 0; i < population_size; i++)
  {
    cout << fitness_map[i].first << ", ";
  }
  cout << endl;
}
Sudoku GeneticAlgorithm::solution()
{
  return population[0];
}
void GeneticAlgorithm::destroy()
{
  initial.destroy();
  destroy_population();
}
void GeneticAlgorithm::destroy_population()
{
  for(int i = 0; i < population_size; i++)
  {
    population[i].destroy();
  }
}

bool GeneticAlgorithm::run()
{
  generation_count = 0;
  while(generation_count < max_generation)
  {
    generation_count += 1;
    nextGeneration();
    cout << "ENDED!" << endl;
    if(fitness_map[0].first == 0)
    {
      return true;
    }
  }
  return false;
}