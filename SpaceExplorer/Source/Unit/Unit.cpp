#include "Unit.h"

void Unit::setLocation(int nx, int ny)
{
	x = nx;
	y = ny;
}

void Unit::pathTo(int nx, int ny, World* world)
{
	if (nx == x && ny == y)
	{
		return;
	}
}

Unit::Unit()
{
}


Unit::~Unit()
{
}
