#pragma once

#include "AngleDegree.hpp"

namespace BF
{
	template<class NumberType>
	struct AngleRadians
	{
		public:
		NumberType Value;

		AngleRadians(AngleDegree<NumberType> degree)
		{
			const NumberType conversionFactor = 3.1415926535897932384626433832 / 180.0;

			Value = degree * conversionFactor;
		}
	};
}