// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "sudoku.h"
#include <fstream>

using namespace std;

Sudoku::Sudoku(){
	char c;
	
	ifstream inStream;

	inStream.open("sudoku.txt");
	//makes the grid to solve
	Grid.resize(9);
	for (int row = 0; row < 9; row++){
		for (int col = 0 ; col < 9; col++){
			if(!(inStream >> c)){
				cerr << "not enough digits \n";
				inStream.close();
				exit(1);
			}

			//check for invalid entries
			if ((c <= '9' && c >= '0') || c == '-'){
				Grid[row].push_back(c);
			}else{
				cerr << "entry at " << row << " " << col << " invalid \n";
				inStream.close();
				exit(1);
			}
		}
	}

	inStream.close();
	
}

void Sudoku::display(){

	for (int row = 0; row < Grid.size(); row++) {
		for (int col = 0; col < Grid[row].size(); col++){
			
			if (col != 0){
				cout << " ";
			}
			
			cout << Grid[row][col];

			if ((col == 2) || (col == 5)){
				cout << " ";
			}
		}

		cout << endl;
		if ((row == 2) || (row == 5)){
				cout << endl;
		}
	}
}

bool Sudoku::Row_Valid(int row){

	//temp vector tracks numbers encoutered in row
	vector <int> temp;
	temp.resize('10');
	
	//if digit has been seen already then return false
	//else flag digit as seen
	for (int col = 0; col < 9; col++){
		if (Grid[row][col] != '-'){
			if (temp[Grid[row][col]] == 1){
				return false;
			}else{
				temp[Grid[row][col]] = 1;
			}
		}
	}
	
	//if we've gotten this far then return true
	return true;
}

bool Sudoku::Col_Valid(int col){

	//temp vector tracks numbers encoutered in row
	vector <int> temp;
	temp.resize('10');

	//if digit has been seen already then return false
	//else flag digit as seen
	for (int row = 0; row < 9; row++){
		if (Grid[row][col] != '-'){
			if (temp[Grid[row][col]] == 1){
				return false;
			}else{
				temp[Grid[row][col]] = 1;
			}
		}
	}
	
	//if we've gotten this far then return true
	return true;
}

bool Sudoku::Box_Valid(int startrow, int startcol){
	//temp vector tracks numbers encoutered in row
	vector <int> temp;
	temp.resize('10');

	//if digit has been seen already then return false
	//else flag digit as seen
	for (int row = startrow; row < startrow + 3; row++){
		for (int col = startcol; col <startcol + 3; col++){
			if (Grid[row][col] != '-'){
				if (temp[Grid[row][col]] == 1){
					return false;
				}else{
					temp[Grid[row][col]] = 1;
				}
			}
		}
	}

	//if we've gotten this far then return true
	return true;
}

bool Sudoku::Solve(){
	return My_Solve(0, 0);
}

bool Sudoku::My_Solve(int row, int col){
	int i;

	//skip to empty spaces
	while (row < 9 && Grid[row][col] != '-'){
		col++;
		if (col == 9){
			row++;
			col = 0;
		}
	}

	//base case
	if (row == 9){
		return true;
	}

	for (i = '1'; i <= '9' ; i++){
		Grid[row][col] = i;
		if (Row_Valid(row) && Col_Valid(col) &&
			Box_Valid(row-(row%3), col-(col%3)) &&
			My_Solve(row,col)){
				return true;
		}
	}

	//non success
	Grid[row][col] = '-';
	return false;
}

int _tmain(int argc, _TCHAR* argv[]){

	Sudoku puzzle;

	if (!(puzzle.Solve())){
		cout << "puzzle unsolvable" << endl;
		return(0);
	}else{
		puzzle.display();
	}

	return 0;
}

