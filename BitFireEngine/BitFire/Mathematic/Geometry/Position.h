#pragma once

#include "Point.h"
#include <math.h>

// [X|Y|Z] Position in 3D-WorldSpace. 
struct Position : public Point
{
public:
	float Z;

	Position();
	Position(Point point);
	Position(const float x, const float y);
	Position(const float x, const float y, const float z);

	void ChangeSize(Position point);
};
