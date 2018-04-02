CC=g++
CPPFLAGS=-std=c++1z

OBJ=Solver.o Sudoku.o
DEPS=Sudoku.hpp Solver.hpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

main: $(OBJ)
	$(CC) main.cpp -o $@ $^ $(CPPFLAGS)


.PHONY: clean

clean:
	rm -f ./*.o main

runeasy: main
	./main < 500.easy


runsol: main
	./main < 500.sol


runin: main
	./main < 500.in