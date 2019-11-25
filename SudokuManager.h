#ifndef SUDOKU_H
#define SUDOKU_H
#include<iostream>
#include <fstream>
#include <string>

#include <vector>
#include <sstream>
#include <regex>

#include <cmath>
#include <ctime>

class SudokuManager 
{
  private: 
    int** board;
    int size;
    bool isValidAssignment(int i, int j, int val);
    bool isValidCol(int j, int val);
    bool isValidRow(int i, int val);
    bool isValidBlock(int i, int j, int val);
    static int getRand(int max);
    static char file_names[8][20];
    
  public:
    SudokuManager();
    SudokuManager(int size);
    SudokuManager(std::string file_name);
    int** getBoard();
    void print();
    void save(std::string output_name);
    static SudokuManager benchmarkBoard(int index);
    static SudokuManager generateBoard(int size, int difficulty);
    static void seed();
};
#endif