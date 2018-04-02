#include "Solver.hpp"
#include <tuple>
#include <set>
#define PRINT_MOD 10000000
using namespace std;

Solver::Solver(){}

bool Solver::solve(Sudoku &s){
	clock_begin = std::clock();
	bool output = this->brute(s);
	clock_end = std::clock();
	cout << "Used " << this->count << " attempts." << endl;
	return output;
}

bool Solver::brute(Sudoku &s){
	report(s);
	if(s.solved())
		return true;
	else {
		int i, j;
		s.branch_pos(i, j);
		if(i < 0 || j < 0) // There is no more branching
			return false;
		set<int> candidates;
		s.candidates(i, j, candidates);
		for(auto c : candidates){
			s.set(i, j, c);
			if(this->brute(s))
				return true;
			else
				s.unset(i, j);
		}
		return false;
	}
}

double Solver::elapsed_time(){
	return double(clock_end - clock_begin) / CLOCKS_PER_SEC;
}

void Solver::report(Sudoku &s){
	this->count++;
	if(count % PRINT_MOD == 0){
		cout << s;
	}
}