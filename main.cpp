#include <iostream>
#include "maze.h"
using namespace std;

int main()
{
	Cell cell;
	Maze Maze(3,4);
	cout << Maze.cells[2][3] << endl;
	return 0;
}
