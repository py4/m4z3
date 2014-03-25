#ifndef __CELL_H
#define __CELL_H

#include <iostream>
using namespace std;

class Cell {
public:
	
Cell() : i(0) , j(0) , bitmask(0) {}
Cell(int i, int j, int bitmask = 0) : i(i), j(j), bitmask(bitmask) {}
	int i;
	int j;
	int bitmask; // L U R D
	int get_mask_index(char direction);
	void open(char);
	void close(char);
	bool can_go(char);
};

ostream& operator<<(ostream&,Cell);

#endif