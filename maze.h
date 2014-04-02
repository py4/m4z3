#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include "cell.h"
#include "SDL/SDL.h"
#include "resource.h"
#include "graphic.h"

using namespace std;
#define DIR_COUNT 4

class Maze {
public:
	static int passed;
	//Maze(int, int);
	bool init(int,int);
	bool init_screen();
	
	Cell** cells;
	Cell* current_cell;
	Cell* final_cell;
	
	int row_count;
	int column_count;
	
	bool generate();
	bool go_strictly(char);

	Resource resources;
	SDL_Surface* screen;

	void free_everything();
	void dump_on_screen();
	void clear_screen();
	bool handle_key(char);
};

ostream& operator<<(ostream&, const Maze&);

#endif


