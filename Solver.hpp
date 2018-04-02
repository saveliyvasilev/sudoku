#ifndef SOLVER_H
#define SOLVER_H
#include "./Sudoku.hpp"
#include <tuple>
#include <set>
#include <ctime>

class Solver{
private:
	clock_t clock_begin, clock_end;
	unsigned long count = 0;
	bool brute(Sudoku&);
	void report(Sudoku&);
public:
	Solver();
	bool solve(Sudoku&);
	double elapsed_time();
};

#endif