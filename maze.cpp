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
//  cerr << "I'm in i,j: " << current_cell->i << " " << current_cell->j << endl;
	for(int i = 0; i < DIR_COUNT; i++)
	{
		if(current_cell->can_go(directions[i]))
			continue;
		cerr << "current cell:  " << *current_cell << endl;
		current_cell->open(directions[i]);
		cerr << "wanna go " << directions[i] << "so I became:  " << *current_cell << endl;
		if(go_strictly(directions[i]))
		{
			cerr << "I succedded and now I'm: ";
			current_cell->open(get_opposite_dir(directions[i]));
			cerr << *current_cell << endl;
			if(!current_cell->seen)
			{
				if(generate())
					return true;
				else
				{
					passed--;
					current_cell->seen = false;
					char direction = get_opposite_dir(directions[i]);
					cerr << "no other choices and I go back to " << direction << endl;
					current_cell->close(direction);
					cerr << "I became it before going back:  " << *current_cell << endl;
					if(!go_strictly(direction))
						cerr << "[generate] >>>> bug <<<<" << endl;
					current_cell->close(get_opposite_dir(direction));
					cerr << "now I became:  " << *current_cell << endl;
				}
			}
			else
			{
				int index = i + pow(-1,i % 2);
				char direction = get_opposite_dir(directions[i]);
				cerr << "have seen this before and I'm going back to " << direction << endl;
				current_cell->close(direction);
				cerr << "I became it before going back:  " << *current_cell << endl;
				go_strictly(direction);
				current_cell->close(get_opposite_dir(direction));
				cerr << "now I became:  " << *current_cell << endl;
			}
		}
		else
		{
			cerr << "couldn't go so I became: ";
			current_cell->close(directions[i]);
			cerr << *current_cell << endl;
		}
	}
	return false;
}

ostream& operator<<(ostream& out, const Maze& maze)
{
	for(int i = 0; i < maze.row_count; i++)
	{
		for(int j = 0;j < maze.column_count; j++)
		{
/*			if(i == 0)
				cout << "--";
			if(!maze.cells[i][j].can_go('L'))
				cout << "|";
			if(!maze.cells[i][j].can_go('D'))
				cout << "__";
			if(j == maze.column_count - 1)
			cout << "|";*/
			cout << maze.cells[i][j] << endl;
		}
//		cout << endl;
	}
	return out;
}


