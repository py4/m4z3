#include "cell.h"
int Cell::get_mask_index(char direction)
{
	switch(direction)
	{
	case 'L':
		return 0;
	case 'U':
		return 1;
	case 'R':
		return 2;
	case 'D':
		return 3;
	}
}

void Cell::open(char direction)
{
	bitmask |= (1 << (3 - get_mask_index(direction)));
}

void Cell::close(char direction)
{
	bitmask &= (~(1 << (3 - get_mask_index(direction))));
}

bool Cell::can_go(char direction)
{
	return (1 << (3 - get_mask_index(direction))) & bitmask;
}

ostream& operator<<(ostream& out,Cell cell)
{
	out << "i,j : " << cell.i << " " << cell.j << endl;;
	out << "can go up: " << cell.can_go('U') << endl;
	out << "can go down:  " << cell.can_go('D') << endl;
	out << "can go left:  " << cell.can_go('L') << endl;
	out << "can go right:  " << cell.can_go('R') << endl;
	//out << "bitmask: " << cell.bitmask << endl;;
	return out;
}
