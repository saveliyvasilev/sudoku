#ifndef SOLVER_H
#define SOLVER_H
#include "./Sudoku.hpp"
#include <ctime>
#include <list>
#include <set>
#include <tuple>
#include <vector>

class Solver {
private:
  clock_t clock_begin, clock_end;
  unsigned long count = 0;
  std::list<size_t> min_branching_num;
  std::pair<Sudoku, int> brute(Sudoku &input, const int nsols_bound);
  void report(Sudoku &);

public:
  Solver();
  std::pair<Sudoku, int> solve(Sudoku &input, const int nsols_bound);
  double elapsed_time();
  unsigned long get_attempts();
  double get_complexity();
};

#endif