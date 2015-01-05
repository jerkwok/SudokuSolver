#include <vector>
#include <iostream>

using namespace std;

class Sudoku{
public:
	Sudoku();
	bool Solve();
	void display();
private:
	bool Row_Valid(int row);
	bool Col_Valid(int col);
	bool Box_Valid(int startrow, int startcol);
	bool My_Solve(int row, int col);
	vector <vector <char>> Grid;
};
