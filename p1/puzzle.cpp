//author Huajun Chai, 998584845
#include "puzzle.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <iomanip>

using namespace std;

bool Puzzle::isRelated(int row, int col)
{
	if((row / 9 )== (col / 9 ))
		return true;
	if(((row - col) % 9) == 0)
		return true;
	if((((row % 9)/3) == ((col % 9)/3))&&(((row/27) == (col/27))))
		return true;
	else
		return false;
}//check row, column and the same block to eliminate some infeasible numbers

/*void Puzzle::writeToGrid(vector<int> input, char grid[][9])
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			grid[i][j] = input[i*9+j] + 48;
		}
}*/

void Puzzle::solve(vector<int> input) 
{
    vector<int>::iterator index = find(input.begin(), input.end(), 0);
    if ( index == input.end())//there is no entry that is still empty 
	{
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
				cout << input[i * 9 + j] << ' ';
			cout << endl;
		}
        return;
    }
    int i = (int)(index - input.begin());

    set<int> num_conflict;
    for ( int j = 0; j < 81; j++) 
	{
        if (isRelated(i,j)) 
		{
            num_conflict.insert(input[j]);
        }
    }
    for ( int m = 1; m <= 9; m++) 
	{
        set<int>::iterator index2 = num_conflict.find(m);
        if ( index2 == num_conflict.end()) 
		{
            input[i] = m;
            solve(input);
        }
    }
}

Puzzle::Puzzle(const char grid[][9])
{

}
