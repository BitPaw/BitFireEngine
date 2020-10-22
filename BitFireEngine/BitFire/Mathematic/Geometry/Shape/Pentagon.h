#pragma once

#include "Shape.h"
#include "../Point.h"

namespace BF
{
	class Pentagon : public Shape
	{
		public:
		Point A;
		Point B;
		Point C;
		Point D;
		Point E;

		Pentagon();
		Pentagon(Point a, Point b, Point c, Point d, Point e);
	};
}