#include "IndexPosition.h"

IndexPosition::IndexPosition() : IndexPosition(0,0,0)
{
}

IndexPosition::IndexPosition(unsigned int x, unsigned int y, unsigned int z) : IndexPoint(x,y)
{
	Z = z;
}
