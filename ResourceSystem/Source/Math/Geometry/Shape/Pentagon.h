#pragma once

#include "Shape.h"

#include "../Vector2.hpp"

namespace BF
{
	class Pentagon 
	{
		public:

		Pentagon();
		Pentagon(Vector2<float> a, Vector2<float> b, Vector2<float> c, Vector2<float> d, Vector2<float> e);
	};
}