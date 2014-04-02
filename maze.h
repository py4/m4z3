#include <iostream>
#include "cell.h"
using namespace std;
#define DIR_COUNT 4

class Maze {
public:
	static int passed;
	Maze(int, int);

	Cell** cells;
	Cell* current_cell;
	
	int row_count;
	int column_count;
	
	bool generate();
	bool go_strictly(char);
};

ostream& operator<<(ostream&, const Maze&);


