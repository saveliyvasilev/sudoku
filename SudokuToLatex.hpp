#ifndef SUDOKUTOLATEX_H
#define SUDOKUTOLATEX_H

#include <string>
#include "./Sudoku.hpp"
#include "./Generator.hpp"

class SudokuToLatex{
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
	void sudoku_footer(std::string &s, const std::string &legent);
	void sudoku_body(std::string &s, Sudoku &sudoku);
public:
	SudokuToLatex(std::string file, unsigned int npages, double complexity);
	void execute();
};

#endif