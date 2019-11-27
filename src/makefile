allfiles = SimulatedAnnealing.o SudokuManager.o Sudoku.o

src : $(allfiles)
	g++ -Wall -g -o src $(allfiles)

SimulatedAnnealing.o : SimulatedAnnealing.h
SudokuManager.o : SudokuManager.h
Sudoku.o : Sudoku.h

clean :
	rm -f src $(allfiles)