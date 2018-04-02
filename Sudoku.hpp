#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <set>
#include <tuple>

class Sudoku{
private:
	int m[9][9];
	std::set<int> canmatrix[9][9];
	int unset_count;
	bool row_solved(int i);
	bool col_solved(int j);
	bool sq_solved(int sq_i, int sq_j); // squares range from (0,0) to (2,2)

	void reset_row_non_candidates(int i, std::bitset<10> &cs);
	void reset_col_non_candidates(int j, std::bitset<10> &cs);
	void reset_sq_non_candidates(int sq_i, int sq_j, std::bitset<10> &cs);
	void refresh_candidates();
public:
	Sudoku();
	Sudoku(std::istream&);
	
	void branch_pos(int &i, int &j);
	void set(int i, int j, int num);
	void unset(int i, int j);
	void unset(std::set<std::tuple<int, int> > &);
	bool solved();
	void candidates(int i, int j, std::set<int>&);

	friend std::ostream& operator<<(std::ostream& stream, const Sudoku& sudoku);
};

#endif