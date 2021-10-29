#pragma once

namespace BF
{
	template<typename NumberType>
	struct QuadTreePosition
	{
		public:
		NumberType X;
		NumberType Y;

		QuadTreePosition()
		{
			X = 0;
			Y = 0;
		}

		QuadTreePosition(NumberType x, NumberType y)
		{
			X = x;
			Y = y;
		}
	};
}