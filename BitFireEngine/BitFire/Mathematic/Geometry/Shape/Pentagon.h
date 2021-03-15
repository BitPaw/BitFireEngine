#pragma once

#include "Shape.h"

#include "../Point.hpp"

namespace BF
{
	class Pentagon 
	{
		public:

		Pentagon();
		Pentagon(Point<float> a, Point<float> b, Point<float> c, Point<float> d, Point<float> e);
	};
}