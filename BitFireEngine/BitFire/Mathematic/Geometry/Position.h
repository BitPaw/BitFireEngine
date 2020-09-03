#pragma once

#include "Point.h"

// [X|Y|Z] Position in 3D-WorldSpace. 
class Position : public Point
{
public:
	float Z;

	Position();
	Position(Point point);
	Position(const float x, const float y);
	Position(const float x, const float y, const float z);
};
