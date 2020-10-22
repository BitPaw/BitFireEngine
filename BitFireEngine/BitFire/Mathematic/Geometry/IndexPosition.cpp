#include "IndexPosition.h"

BF::IndexPosition::IndexPosition() : IndexPosition(0,0,0)
{
}

BF::IndexPosition::IndexPosition(unsigned int x, unsigned int y, unsigned int z) : IndexPoint(x,y)
{
	Z = z;
}
