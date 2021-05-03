#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <set>
#include <tuple>
#include <vector>

class Sudoku{
private:
	std::vector<std::vector<int>> m;
	std::set<int> canmatrix[9][9];
	int unset_count;
	bool row_solved(int i) const;
	bool col_solved(int j) const;
	bool sq_solved(int sq_i, int sq_j) const; // squares range from (0,0) to (2,2)

	void reset_row_non_candidates(int i, std::bitset<10> &cs) const;
	void reset_col_non_candidates(int j, std::bitset<10> &cs) const;
	void reset_sq_non_candidates(int sq_i, int sq_j, std::bitset<10> &cs) const;
	void refresh_candidates();
public:
	Sudoku();
	Sudoku(std::istream&);
	Sudoku& operator=(const Sudoku &other);
	
	int get_value(int i, int j) const;
	std::pair<int, int> branch_pos();
	std::pair<int, int> completion_pos();
	void set(int i, int j, int num);
	void unset(int i, int j);
	void unset(std::set<std::tuple<int, int> > &);
	void clear();
	bool solved() const;
	std::set<int> candidates(int i, int j) const;

	friend std::ostream& operator<<(std::ostream& stream, const Sudoku& sudoku);
};

#endif