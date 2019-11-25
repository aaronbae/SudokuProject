main : main.o SudokuManager.o
	g++ -Wall -g -o main main.o SudokuManager.o

main.o : main.cpp SudokuManager.h
	g++ -Wall -g -c main.cpp

SudokuManager.o : SudokuManager.cpp SudokuManager.h
	g++ -Wall -g -c SudokuManager.cpp

clean :
	rm -f main.o SudokuManager.o *.out