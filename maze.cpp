#include "maze.h"
#include <algorithm>
#include <cmath>

int Maze::passed;

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
	passed = 0;
	current_cell = &(cells[0][0]);
}

bool Maze::go_strictly(char direction)
{
	int i = current_cell->i , j = current_cell->j;
	bool success = false;
	switch(direction)
	{

	case('U'):
		if(i >= 1)
		{	
			current_cell = &(cells[i-1][j]);
			return true;
		}
		break;

	case('D'):
		if((i + 1) < row_count)
		{
			current_cell = &(cells[i+1][j]);
			return true;
		}
		break;

	case('L'):
		if(j >= 1)
		{
			current_cell = &(cells[i][j-1]);
			return true;
		}
		break;

	case('R'):
		if((j + 1) < column_count)
		{
			current_cell = &(cells[i][j + 1]);
			return true;
		}
		break;
	}
	return false;
}

char get_opposite_dir(char dir)
{
	switch(dir)
	{
	case('U'):
		return 'D';
	case('D'):
		return 'U';
	case('L'):
		return 'R';
	case('R'):
		return 'L';
	}
}

bool Maze::generate()
{
	current_cell->seen = true;
	passed++;
	if(passed == row_count * column_count)
		return true;
	
	char directions[4] = {'U','D','L','R'};
	random_shuffle(directions,directions+4);
  cerr << "I'm in i,j: " << current_cell->i << " " << current_cell->j << endl;
	for(int i = 0; i < DIR_COUNT; i++)
	{
		if(go_strictly(directions[i]))
		{
			if(!current_cell->seen)
			{
				cerr << "I'm going " << directions[i] << " to i,j:  " << current_cell->i << " " << current_cell->j << endl;
				if(generate())
					return true;
				else
				{
					passed--;
					current_cell->seen = false;
					char direction = get_opposite_dir(directions[i]);
					if(!go_strictly(direction))
						cerr << "[generate] >>>> bug <<<<" << endl;
					cerr << "no other choice! I'm back to i,j:  " << current_cell->i << " " << current_cell->j << endl;
				}
			}
			else
			{
				int index = i + pow(-1,i % 2);
				char direction = get_opposite_dir(directions[i]);
				go_strictly(direction);
			}
		}
	}
	return false;
}


