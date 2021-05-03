CC=g++
CPPFLAGS=-std=c++1z

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
	./main < 500.easy


runsol: main
	./main < 500.sol


runin: main
	./main < 500.in
