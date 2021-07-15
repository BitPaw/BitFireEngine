#pragma once

#include "Vector3.hpp"

namespace BF
{
	template<class NumberType>
	struct Vector4 
	{
		public:
		NumberType Date[4];

		Vector4()
		{
			Date[0] = 0;
			Date[1] = 0;
			Date[2] = 0;
			Date[3] = 0;
		}

		Vector4(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			Date[0] = x;
			Date[1] = y;
			Date[2] = z;
			Date[3] = w;
		}

		void Set(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			Date[0] = x;
			Date[1] = y;
			Date[2] = z;
			Date[3] = w;
		}
	};
}