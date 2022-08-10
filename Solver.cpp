#include "Solver.hpp"
#include <list>
#include <set>
#include <tuple>
#define PRINT_MOD 10000000
using namespace std;

Solver::Solver() {}

std::pair<Sudoku, int> Solver::solve(Sudoku &s, const int nsols_bound) {
  clock_begin = std::clock();
  count = 0;
  min_branching_num.clear();
  auto [result, found_solutions] = brute(s, nsols_bound);
  clock_end = std::clock();
  return std::make_pair(result, found_solutions);
}

std::pair<Sudoku, int> Solver::brute(Sudoku &s, const int nsols_bound) {
  int n_sols_in_children = 0, found_solutions_ijc;
  Sudoku result;

  report(s);
  if (s.solved())
    return std::make_pair(s, 1);
  else {
    auto [i, j] = s.branch_pos();
    if (i < 0 || j < 0) // There is no more branching
      return std::make_pair(s, 0);
    std::set<int> candidates = s.candidates(i, j);
    min_branching_num.push_back(candidates.size()); // For complexity estimation

    for (auto c : candidates) {
      s.set(i, j, c);
      std::tie(result, found_solutions_ijc) = brute(s, nsols_bound);
      n_sols_in_children += found_solutions_ijc;
      s.unset(i, j);
      if (n_sols_in_children >= nsols_bound)
        return std::make_pair(result, n_sols_in_children);
    }
    return std::make_pair(result, n_sols_in_children);
  }
}

double Solver::elapsed_time() {
  return double(clock_end - clock_begin) / CLOCKS_PER_SEC;
}

void Solver::report(Sudoku &s) {
  count++;
  if (count % PRINT_MOD == 0)
    cout << s;
}

unsigned long Solver::get_attempts() { return count; }

double Solver::get_complexity() {
  double accum = 0;
  unsigned int n = 0;
  for (auto el : min_branching_num) {
    if (el > 0) {
      accum += el;
      n++;
    }
  }
  if (n == 0)
    return 1;
  else
    return accum / n;
}