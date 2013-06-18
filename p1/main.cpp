#include <iostream>
#include "puzzle.h"
#include <fstream>
#include <stdlib.h>
#include "CPUTimer.h"
using namespace std;

void readGrid(const char *filename, char grid[][9])
{
	ifstream inf(filename);
    if(!inf) 
	{
		std::cout << "Fail to open the file.";
		exit ( 0 );
	}
	int row, col;

	for(row = 0; row < 9; row++)
	{
		for(col = 0; col < 9; col++)
			inf >> grid[row][col];
		inf.ignore(1); // eat \n
	} // for row
	inf.close();
} // readGrid()

void writeGrid(const char grid[][9])
{
	for(int row = 0; row < 9; row++)
	{
		for(int col = 0; col < 9; col++)
			cout << grid[row][col] << ' ';
		cout << endl;
	} // for row
} // writeGrid()
 
int main( /*int argc, char** argv*/) {
    char file[100]; 
	cin >> file;
	std::ifstream inFile(file);

	char grid[9][9];
	readGrid(file, grid);
	cout << "Original sudoku:" << endl;
	writeGrid(grid);
	cout << "The solution:" << endl;
	CPUTimer ct;
	ct.reset();
    	vector<int> input;
    	input.clear();
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			if(grid[i][j]=='*')
				input.push_back(0);
			else
				input.push_back(int(grid[i][j])-48);
		}

	Puzzle puzzle(grid);
        puzzle.solve(input);
	cout << "CPU time: " << ct.cur_CPUTime() << endl;
	//puzzle.writeToGrid(input,grid);
	//writeGrid(grid);
	return 0;
}
