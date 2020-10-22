#pragma once

#include "Shape.h"
#include "../Point.h"

namespace BF
{
	class Triangle : public Shape
	{
		public:
		Point A;
		Point B;
		Point C;

		Triangle();
		Triangle(Point a, Point b, Point c);
	};
}