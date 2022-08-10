#include "./Generator.hpp"
#include "./Solver.hpp"
#include "./Sudoku.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include <tuple>
#include <vector>

#define POSSIBLE_RNODES                                                        \
  100 // Bound on how many recursive nodes to visit before giving up the
      // execution

using namespace std;

Generator::Generator() { srand(clock()); }

void Generator::extend(Sudoku &s) {
  auto [i, j] = s.completion_pos();
  std::set<int> candidates = s.candidates(i, j);

  int rnd = rand() % candidates.size();
  set<int>::const_iterator it(candidates.begin());
  advance(it, rnd);

  s.set(i, j, *it);
  return;
}

std::vector<std::pair<int, int>> Generator::get_nonzero_positions(Sudoku &s) {
  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (s.get_value(i, j) != 0)
        ans.push_back(make_pair(i, j));
    }
  }
  return ans;
}

bool Generator::complexify_rec(Sudoku &s, const double &complexity,
                               unsigned long &visited_nodes) {
  Solver solver;
  visited_nodes++;

  if (visited_nodes > POSSIBLE_RNODES)
    return false;

  auto [completed, found_solutions] = solver.solve(s, 2);
  if (found_solutions > 1 || found_solutions == 0)
    return false;
  std::tie(completed, found_solutions) = solver.solve(s, 1);
  if (solver.get_complexity() >= complexity)
    return true;

  auto nz_pos = get_nonzero_positions(s);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(nz_pos.begin(), nz_pos.end(), g);
  for (auto &[i, j] : nz_pos) {
    if (visited_nodes > POSSIBLE_RNODES)
      return false;
    auto cur = s.get_value(i, j);
    s.unset(i, j);
    if (complexify_rec(s, complexity, visited_nodes))
      return true;
    else
      s.set(i, j, cur);
  }
  return false;
}

void Generator::complexify(Sudoku &s, const double &complexity) {
  Solver solver;
  unsigned long visited_nodes;
  while (!complexify_rec(s, complexity, visited_nodes)) {
    visited_nodes = 0;
  }
  return;
}

std::tuple<Sudoku, Sudoku, double>
Generator::generate(const double complexity) {
  int cur;
  Solver solver;
  Sudoku generated;
  for (int k = 1; k < 9; k++)
    extend(generated);

  auto [solution, found_solutions] = solver.solve(generated, 1);

  generated = solution;
  complexify(generated, complexity);
  std::tie(solution, found_solutions) = solver.solve(generated, 1);

  std::cerr << "Actual attempts: " << solver.get_attempts() << endl;
  std::cerr << "Actual complexity: " << solver.get_complexity() << endl;
  std::cout << generated << std::endl;
  return std::make_tuple(generated, solution, solver.get_complexity());
}
