#pragma once

#include "Shape.h"
#include "../Point.h"

namespace BF
{
	class Rectangle : public Shape
	{
		public:
		Point A;
		Point B;
		Point C;
		Point D;

		Rectangle();
		Rectangle(Point a, Point b, Point c, Point d);

		void Reset();
	};
}