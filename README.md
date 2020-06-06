# SudokuProject
An attempt to implement 3 different algorithms to solving the sudoku puzzle. The board size can be configured to be either 4x4, 9x9, or 25x25, however, at the 25x25 level, most of the algorithms have difficult time solving the puzzle. The 3 algorithms that were implemented are:
1. Local Search
2. Genetic Algorithm
3. and simple Backtracking
The most consistent and efficient algorithm was the simple backtracking algorithm. However, the limitations exist and the results are shown in our report here: 
https://github.com/aaronbae/SudokuProject/blob/master/project_report/project_report.pdf

## Findings
The overal results are explained in detail in the report link above, but here are some highlighted points:
![Simulated Annealing Results](https://github.com/aaronbae/SudokuProject/blob/master/project_report/simulated_annealing_results.png)
First observation we note is that the difficulty of the puzzle correlates with the number of empty cells that are emptied in the puzzle. This is understandable since the more empty spaces there are the bigger the search space becomees. 
Second observation is that the successful solve is not guaranteed. When the difficulty of the puzzle increases, the success-rate gradually decreases, rather than a sharp edged drop from 100% to 0%.
![Fitness Value over Iteration](https://github.com/aaronbae/SudokuProject/blob/master/project_report/16_100_iteration.png)
This plot shows the fitness score of simulated annealing algorithm over a run. Note the decrease in the fitness value, which means that there are less number of errors to fix on a given board.
![Backtracking Results](https://github.com/aaronbae/SudokuProject/blob/master/project_report/backtrack.png)
The performance of backtracking algorithm can be modeled as an exponential graph. Out of 625 cells in a 25x25 board, if you were to remove 160 cells (or designated to become empty), the algorithm can sometimes require over a million backtracks. This concludes that backtracking algorithm is not scalable to bigger sized boards like 36x36.

## Compiling
In the root directory, make sure you have (g++) installed. Currently, tested with Ubuntu 18.04.1 LTS. When you have g++ installed, go to the root directory and simply call the following command to compile:
```
make main
```
Then, to execute the program
```
./main
```
