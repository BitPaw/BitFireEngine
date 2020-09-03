#pragma once

#include "Shape.h"
#include "../Point.h"

class Triangle : public Shape
{
public:
	Point A;
	Point B;
	Point C;

	Triangle();
	Triangle(Point a, Point b, Point c);

	void Reset() override;
};