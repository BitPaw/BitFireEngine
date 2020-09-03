#pragma once

#include "Point.h"

class Position : public Point
{
public:
	float Z;

	Position();
	Position(const float x, const float y);
	Position(const float x, const float y, const float z);
};

