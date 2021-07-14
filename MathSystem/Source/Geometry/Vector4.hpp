#pragma once

#include "Vector3.hpp"

namespace BF
{
	template<class NumberType>
	struct Vector4 
	{
		public:
		NumberType Date[4];

		Vector4(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			Date[0] = x;
			Date[1] = y;
			Date[2] = z;
			Date[3] = w;
		}
	};
}