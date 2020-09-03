#pragma once

#include "IndexPoint.h"

class Size
{
public:
	IndexPoint A;
	IndexPoint B;

	Size(unsigned int xA, unsigned int yA, unsigned int xB, unsigned int yB);
	Size(IndexPoint a, IndexPoint b);
};