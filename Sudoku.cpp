#include "./Sudoku.hpp"
#include <bitset>
#include <set>
#include <tuple>

Sudoku::Sudoku(){
	throw -123;
}

Sudoku::Sudoku(std::istream &is){
	unset_count = 81;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			is >> m[i][j];
			unset_count--;
		}
}

std::ostream& operator<<(std::ostream& os, const Sudoku& s){
	os << std::endl;
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++)
			os << s.m[i][j] << ' ';
		os << std::endl;
	}
	return os;
}


void Sudoku::set(int i, int j, int num){
	if(m[i][j] != 0 && num == 0)
		unset_count++;
	else if(m[i][j] == 0 && num != 0)
		unset_count--;
	m[i][j] = num;
}

void Sudoku::unset(int i, int j){
	this->set(i, j, 0);
}

void Sudoku::unset(std::set<std::tuple<int, int> >& ijs){
	for(auto ij : ijs)
		this->unset(std::get<0>(ij), std::get<1>(ij));
}

void Sudoku::branch_pos(int &i, int &j){
	this->refresh_candidates();
	int min = 10;
	for(int k = 0; k < 9; k++)
		for(int l = 0; l < 9; l++)
			if(m[k][l] == 0 && min > canmatrix[k][l].size()){
				min = canmatrix[k][l].size();
				i = k;
				j = l;
			}
}

void Sudoku::refresh_candidates(){
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++){
			canmatrix[i][j].clear();
			this->candidates(i, j, canmatrix[i][j]);
		}
}

bool Sudoku::sq_solved(int sq_i, int sq_j){
	std::bitset<10> slots;
	static std::bitset<10> target(0b1111111110);
	for(int i = sq_i * 3; i < sq_i * 3 + 3; i++)
		for(int j = sq_j * 3; j < sq_j * 3 + 3; j++)
			slots.set(m[i][j]);
	return target == slots;
}

bool Sudoku::row_solved(int i){
	std::bitset<10> slots;
	static std::bitset<10> target(0b1111111110);
	for(int j = 0; j < 9; j++)
		slots.set(m[i][j]);
	return target == slots;
}

bool Sudoku::col_solved(int j){
	std::bitset<10> slots;
	static std::bitset<10> target(0b1111111110);
	for(int i = 0; i < 9; i++)
		slots.set(m[i][j]);
	return target == slots;
}

bool Sudoku::solved(){
	if(unset_count > 0)
		return false;
	for(int i = 0; i < 9; i++)
		if(!row_solved(i))
			return false;
	for(int j = 0; j < 9; j++)
		if(!col_solved(j))
			return false;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(!sq_solved(i, j))
				return false;
	return true;
}

void Sudoku::reset_row_non_candidates(int i, std::bitset<10> &cs){
	for(int j = 0; j < 9; j++)
		cs.reset(m[i][j]);
}

void Sudoku::reset_col_non_candidates(int j, std::bitset<10> &cs){
	for(int i = 0; i < 9; i++)
		cs.reset(m[i][j]);
}

void Sudoku::reset_sq_non_candidates(int sq_i, int sq_j, std::bitset<10> &cs){
	for(int i = sq_i * 3; i < sq_i * 3 + 3; i++)
		for(int j = sq_j * 3; j < sq_j * 3 + 3; j++)
			cs.reset(m[i][j]);
}

void Sudoku::candidates(int i, int j, std::set<int> &candidates){
	if(m[i][j] != 0){
		candidates.clear();
		return;
	}
	std::bitset<10> cs = std::bitset<10>().set();
	reset_row_non_candidates(i, cs);
	reset_col_non_candidates(j, cs);
	reset_sq_non_candidates(i/3, j/3, cs);

	for(int k = 1; k < 10; k++){
		if(cs.test(k)){
			candidates.insert(k);
		}
	}
	return;
}