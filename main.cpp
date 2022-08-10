#include "./Generator.hpp"
#include "./Solver.hpp"
#include "./Sudoku.hpp"
#include "./SudokuToLatex.hpp"
#include <iostream>

using namespace std;

static void show_usage(std::string name) {
  std::cerr << "Usage: " << name << " <option>[argument]"
            << "Options:\n"
            << "\t-g <complexity> \tSpecify a Sudoku complexity \n"
            << "\t-s \tRun solver on input stream \n"
            << "\t--pdf <npages> <complexity> \tGenerates a pdf with npages "
               "pages with 6 sudokus each, with specified complexity"
            << std::endl;
}

void generator(double complexity) {
  Generator g;
  auto [generated, solved, actual_complexity] = g.generate(complexity);
}

void solver() {
  Sudoku s = Sudoku(cin);
  cout << "Loaded Sudoku:" << endl;
  cout << s << endl;
  try {
    Solver solver = Solver();
    auto [result, found_solutions] = solver.solve(s, 1);
    if (found_solutions > 0) {
      cout << "Solved sudoku:" << endl;
      cout << result << endl;
      cout << "Attempts: " << solver.get_attempts() << endl;
      cout << "Complexity: " << solver.get_complexity() << endl;
    } else
      cout << "Could not solve it :/" << endl;

    cout << "Time elapsed " << solver.elapsed_time() << "s" << endl;
  } catch (int e) {
    cout << "Exception " << e << endl;
    cout << s << endl;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    show_usage(argv[0]);
    return 1;
  }
  std::string opt = argv[1];
  if (opt == "-s") {
    solver();
    return 0;
  }
  if (opt == "-g") {
    if (argc == 2) {
      show_usage(argv[0]);
      return 1;
    }
    generator(atof(argv[2]));
  }
  if (opt == "--pdf") {
    if (argc == 2) {
      show_usage(argv[0]);
      return 1;
    }
    SudokuToLatex stl =
        SudokuToLatex("./output.tex", atoi(argv[2]), atof(argv[3]));
    stl.execute();
  }
}