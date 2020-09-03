#pragma once

#include "IndexPoint.h"

class IndexPosition : public IndexPoint
{
public:
	unsigned int Z;

	IndexPosition(unsigned int x, unsigned int y, unsigned int z);
};