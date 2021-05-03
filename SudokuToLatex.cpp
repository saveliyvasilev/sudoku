#include "./SudokuToLatex.hpp"
#include <iostream>
#include <fstream>
#include <vector>

SudokuToLatex::SudokuToLatex(std::string file, unsigned int npages, double complexity){
	this->file = file;
	this->complexity = complexity;
	this->npages = npages;
}

void SudokuToLatex::file_header(std::string &s){
	s.append("\\documentclass{article} \n"
		"\\usepackage[a4paper,margin=.5in]{geometry}\n"
		"\\usepackage{tikz}\n"
		"\\usepackage{mathpazo}\n"
		// "\\pagestyle{empty}\n"
		"\\newcounter{row}\n"
		"\\newcounter{col}\n"
		"\\newcommand\\setrow[9]{\n"
		  "\\setcounter{col}{1}\n"
		  "\\foreach \\n in {#1, #2, #3, #4, #5, #6, #7, #8, #9} {\n"
		    "\\edef\\x{\\value{col} - 0.5}\n"
		    "\\edef\\y{9.5 - \\value{row}}\n"
		    "\\node[anchor=center] at (\\x, \\y) {\\n};\n"
		    "\\stepcounter{col}\n"
		  "}\n"
		  "\\stepcounter{row}\n"
		"}\n"
		"\\begin{document}\n"
		"\\begin{center}\n");
}

void SudokuToLatex::file_footer(std::string &s){
	s.append("\\end{center}\n"
			 "\\end{document}\n");
}


void SudokuToLatex::page_header(std::string &s){
	s.append("\\begin{tikzpicture}[scale=.84, font=\\Large]\n");
}

void SudokuToLatex::page_footer(std::string &s){
	s.append("\\end{tikzpicture}\n");
}

void SudokuToLatex::sudoku_header(std::string &s, unsigned int sudoku_i){
	std::string yshift;
	std::string xshift;
	if(sudoku_i % 2 == 0) xshift = "0cm";
	if(sudoku_i % 2 == 1) xshift = "11cm";
	if(sudoku_i / 2 == 0) yshift = "0cm";
	if(sudoku_i / 2 == 1) yshift = "-11cm";
	if(sudoku_i / 2 == 2) yshift = "-22cm";

	s.append("\\begin{scope}[xshift=" + xshift + ", yshift=" + yshift + "]");

	s.append("\\draw[gray] (0, 0) grid (9, 9);\n"
		     "\\draw[very thick, scale=3] (0, 0) grid (3, 3);\n"
		     "\\setcounter{row}{1}\n");
}

void SudokuToLatex::sudoku_footer(std::string &s, const std::string &legend){
	s.append("\\node[anchor=center] at (4.5, -0.5) {" + legend + "};\n"
    		 "\\end{scope}\n");
}

void SudokuToLatex::sudoku_body(std::string &s, const Sudoku &sudoku){
	for(int i = 0; i < 9; i++){
		s.append("\\setrow ");
		for(int j = 0; j < 9; j++){
			if(sudoku.get_value(i, j) != 0)
				s.append("{" + std::to_string(sudoku.get_value(i, j)) + "}");
			else
				s.append("{ }");
		}
		s.append("\n");
	}
}

void SudokuToLatex::execute(){
	std::vector<Sudoku> solutions;
	Solver s;
	Generator g;

	std::string out;

	file_header(out);
	for(unsigned int i = 0; i < npages; i++){
		page_header(out);
		for(unsigned int j = 0; j < 6; j++){
			sudoku_header(out, j);
			auto [gen, sol, actual_complexity] = g.generate(complexity);
			solutions.push_back(sol);
			sudoku_body(out, gen);
			sudoku_footer(out, std::to_string(1+j) + " - Complexity: " + std::to_string(actual_complexity));
		}
		page_footer(out);
	}
	for(unsigned int i = 0; i < npages; i++){
		page_header(out);
		for(unsigned int j = 0; j < 6; j++){
			sudoku_header(out, j);
			sudoku_body(out, solutions[6*i + j]);
			sudoku_footer(out, "Page " + std::to_string(1+i) + " - " + std::to_string(1+j));
		}
		page_footer(out);
	}
	file_footer(out);

	std::ofstream f;
	f.open (file);
	f << out;
	f.close();
}