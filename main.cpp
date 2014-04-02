#include <iostream>
#include <cstdlib>
#include "maze.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Cell cell;
	Maze maze(3,4);
	maze.generate();
	cout << "==============" << endl;
	cout << maze << endl;
	return 0;
}
