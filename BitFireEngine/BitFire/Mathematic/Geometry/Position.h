#pragma once

#include <math.h>

#include "Point.h"

namespace BF
{
	// [X|Y|Z] Position in 3D-WorldSpace. 
	struct Position : public Point
	{
		public:
		float Z;

		Position();
		Position(Point point);
		Position(const float x, const float y);
		Position(const float x, const float y, const float z);

		void Change(Position point);
		void Change(const float x, const float y, const float z);

	};
}