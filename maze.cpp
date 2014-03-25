#include "maze.h"

Maze::Maze(int r_count, int c_count)
{
	cells = new Cell*[r_count];
	for(int i = 0; i < r_count; i++)
	{
		cells[i] = new Cell[c_count];
		for(int j = 0; j < c_count; j++)
		{
			cells[i][j].i = i;
			cells[i][j].j = j;
		}
	}
	row_count = r_count;
	column_count = c_count;
}


