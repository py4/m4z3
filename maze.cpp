#include "maze.h"
#include <algorithm>
#include <cmath>

int Maze::passed;

bool Maze::init(int r_count,int c_count)
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

	current_cell = &(cells[rand() % row_count][rand() % column_count]);
	final_cell = &(cells[rand() % row_count][rand() % column_count]);
	
	generate();

	if(init_screen())
		return true;
	return false;
	
}

bool Maze::init_screen()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cerr << "couldn't init" << endl;
		return false;
	}
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
	if(screen == NULL)
	{
		cerr << "set video mode failed" << endl;
		cerr << SDL_GetError() << endl;
		return false;
	}

	if(!resources.init())
	{
		cerr << "could not init resources" << endl;
		return false;
	}

	SDL_WM_SetCaption("M4Z3",NULL);
	clear_screen();

	return true;
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
	for(int i = 0; i < DIR_COUNT; i++)
	{
		if(current_cell->can_go(directions[i]))
			continue;
		current_cell->open(directions[i]);
		if(go_strictly(directions[i]))
		{
			current_cell->open(get_opposite_dir(directions[i]));
			if(!current_cell->seen)
			{
				if(generate())
					return true;
				else
				{
					passed--;
					current_cell->seen = false;
					char direction = get_opposite_dir(directions[i]);
					current_cell->close(direction);
					if(!go_strictly(direction))
						cerr << "[generate] >>>> bug <<<<" << endl;
					current_cell->close(get_opposite_dir(direction));
				}
			}
			else
			{
				int index = i + pow(-1,i % 2);
				char direction = get_opposite_dir(directions[i]);
				current_cell->close(direction);
				go_strictly(direction);
				current_cell->close(get_opposite_dir(direction));
			}
		}
		else
			current_cell->close(directions[i]);
	}
	return false;
}

void Maze::free_everything()
{
	SDL_FreeSurface(screen);
}

void Maze::clear_screen()
{
	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.h = 480;
	rect.w = 640;
	SDL_FillRect(screen,&rect,0xffffff);
	SDL_Flip(screen);
}

void Maze::dump_on_screen()
{
	clear_screen();
	for(int i = 0; i < row_count; i++)
		for(int j = 0; j < column_count; j++)
			cells[i][j].dump_on_screen(screen);

	cout << "current cell:  " << *current_cell << endl;
	cout << "final cell:  " << *final_cell << endl;

	SDL_Rect rect;
	rect.x = (current_cell->j * 25) + 12.5;
	rect.y = (current_cell->i * 25) + 12.5;
	rect.h = 10;
	rect.w = 10;
	SDL_FillRect(screen,&rect,0x00FF00);

	rect.x = (final_cell->j * 25) + 12.5;
	rect.y = (final_cell->i * 25) + 12.5;
	rect.h = 10;
	rect.w = 10;
	SDL_FillRect(screen,&rect,0xFF0000);
	
	SDL_Flip(screen);
}

bool Maze::handle_key(char direction)
{
	if(current_cell->can_go(direction))
		go_strictly(direction);
	
	if(current_cell == final_cell)
		return true;
	else
		return false;
}

ostream& operator<<(ostream& out, const Maze& maze)
{
	for(int i = 0; i < maze.row_count; i++)
		for(int j = 0;j < maze.column_count; j++)
			out << maze.cells[i][j] << endl;
	return out;
}


