#include<iostream>
#include "SudokuManager.h"

using namespace std;

int main()
{
  SudokuManager::seed();
  SudokuManager a = SudokuManager::generateBoard(3, 50);
  a.print();
  a.save("output.txt");
  return 0;
}