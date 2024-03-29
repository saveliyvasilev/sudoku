#ifndef GENERATOR_H
#define GENERATOR_H
#include "./Solver.hpp"
#include "./Sudoku.hpp"

#include <ctime>
#include <set>
#include <tuple>

class Generator {
private:
  // clock_t clock_begin, clock_end;
  // void store();
  void extend(Sudoku &s);
  void complexify(Sudoku &s, const double &complexity);
  bool complexify_rec(Sudoku &s, const double &complexity,
                      unsigned long &visited_nodes);
  std::vector<std::pair<int, int>> get_nonzero_positions(Sudoku &s);

public:
  Generator();
  std::tuple<Sudoku, Sudoku, double> generate(const double complexity);
  // double elapsed_time();
};

#endif