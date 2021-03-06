#include "SudokuGenerator.h"

bool** SudokuGenerator::empty2DBool(int inputSize)
{
  bool** result = new bool*[inputSize];
  for(int temp = 0; temp < inputSize; temp++)
  {
    result[temp] = new bool[inputSize];
  }
  return result;
}
int** SudokuGenerator::empty2DInt(int inputSize)
{
  int** result = new int*[inputSize];
  for(int temp = 0; temp < inputSize; temp++)
  {
    result[temp] = new int[inputSize];
  }
  return result;
}

Sudoku SudokuGenerator::generateNoGuarantee(int inputSize, int numberOfSquaresFilled)
{  
  Utils::seed();
  Sudoku a = Sudoku(inputSize);
  int count = numberOfSquaresFilled;
  while(count > 0)
  {
    int randRow = Utils::randomGenerator(inputSize);
    int randColumn = Utils::randomGenerator(inputSize);
    int randAssignment = Utils::randomGenerator(inputSize);
    
    if( a.board[randRow][randColumn] == -1 && a.valid( randRow, randColumn, randAssignment))
    {
      // Debugging only
      //int valueID = difficulty - count + 1;
      //cout<<valueID<<" : ("<<randRow<<","<<randColumn<<") = "<< randAssignment<<endl;
      a.board[randRow][randColumn] = randAssignment;
      count -= 1;
    }
  }
  return a;
}
Sudoku SudokuGenerator::generateGuarantee(int inputSize, int index, int numberOfSquaresToErase)
{
  Utils::seed();
  string a = "./boards/"+to_string(inputSize)+"_fully_solved_"+to_string(index)+".txt";
  Sudoku b = Sudoku(a);
  for(int i=0; i < numberOfSquaresToErase; i++)
  {
    bool notDone = true;
    while(notDone)
    {
      int i = Utils::randomGenerator(inputSize);
      int j = Utils::randomGenerator(inputSize);
      if(b.board[i][j] != -1)
      {
        b.board[i][j] = -1;
        notDone = false;
      }
    }
  }
  return b;
}