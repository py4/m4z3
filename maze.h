#include <iostream>
#include "cell.h"
using namespace std;

class Maze {
public:
	Maze(int, int);
	Cell** cells;
	int row_count;
	int column_count;
};


