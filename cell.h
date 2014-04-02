#ifndef __CELL_H
#define __CELL_H

#include <iostream>
#include "graphic.h"
using namespace std;

class Cell {
public:
	
Cell() : i(0) , j(0) , bitmask(0), seen(false) {}
Cell(int i, int j, int bitmask = 0) : i(i), j(j), bitmask(bitmask), seen(false) {}
	int i;
	int j;
	int bitmask; // L U R D
	int get_mask_index(char direction);
	void open(char);
	void close(char);
	bool can_go(char);

	bool seen;

	void dump_on_screen(SDL_Surface*&);
};

ostream& operator<<(ostream&,Cell);

#endif
