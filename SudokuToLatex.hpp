#ifndef SUDOKUTOLATEX_H
#define SUDOKUTOLATEX_H

#include "./Generator.hpp"
#include "./Sudoku.hpp"
#include <string>

class SudokuToLatex {
private:
  std::string output;
  std::string file;
  double complexity;
  unsigned int npages;
  void file_header(std::string &s);
  void file_footer(std::string &s);
  void page_header(std::string &s);
  void page_footer(std::string &s);
  void sudoku_header(std::string &s, unsigned int sudoku_i);
  void sudoku_footer(std::string &s, const std::string &legend);
  void sudoku_body(std::string &s, const Sudoku &sudoku);

public:
  SudokuToLatex(std::string file, unsigned int npages, double complexity);
  void execute();
};

#endif