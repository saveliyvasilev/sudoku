#include <iostream>
#include "./Solver.hpp"
#include "./Sudoku.hpp"

using namespace std;

int main(int argn, char **argv){
	Sudoku s = Sudoku(cin);
	cout << "Loaded sudoku:" << endl;
	cout << s << endl;
	try{
		Solver solver = Solver();
		if(solver.solve(s)){
			cout << "Solved sudoku:" << endl;
			cout << s << endl;	
		} else
			cout << "Could not solve it :/" << endl;
		
		cout << "Time elapsed " << solver.elapsed_time() << "s" << endl;
	} catch (int e) {
		cout << "Exception " << e << endl;
		cout << s << endl;
	}
}