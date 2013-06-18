#ifndef PUZZLE_H
#define PUZZLE_H
#include <vector>

using namespace std;

class Puzzle
{
 private:
	 //vector<int> input;
 public:
	 Puzzle(const char grid[][9]);
	 void solve(vector<int> input);
	 //void writeToGrid(vector<int> input, char grid[][9]);
	 bool isRelated(int row, int col);
}; // Puzzle class

#endif
