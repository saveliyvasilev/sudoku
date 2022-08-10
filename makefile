CC=g++
CPPFLAGS=-std=c++17

OBJ=Solver.o Sudoku.o Generator.o SudokuToLatex.o
DEPS=Sudoku.hpp Solver.hpp Generator.hpp SudokuToLatex.hpp

%.o: %.cpp $(DEPS)
	$(CC) -g -c -o $@ $< $(CPPFLAGS)

main: $(OBJ)
	$(CC) -g main.cpp -o $@ $^ $(CPPFLAGS)


.PHONY: clean

clean:
	rm -f ./*.o main

runeasy: main
	./main -s < 500.easy


runsol: main
	./main -s < 500.sol


runin: main
	./main -s < 500.in
