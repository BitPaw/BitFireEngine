#pragma once

namespace BF
{
	template<class NumberType>
	struct Padding
	{
		public:
		NumberType Left;
		NumberType Top;
		NumberType Right;
		NumberType Bottom;

		Padding()
		{
			Set(0);
		}

		Padding(NumberType all)
		{
			Set(all);
		}

		Padding(NumberType left, NumberType right)
		{
			Set(left, right);
		}

		Padding(NumberType left, NumberType top, NumberType right, NumberType bottom)
		{
			Set(left, top, right, bottom);
		}

		void Set(NumberType all)
		{
			Set(all, all, all, all);
		}

		void Set(NumberType left, NumberType right)
		{
			Set(left, 0, right, 0);
		}

		void Set(NumberType left, NumberType top, NumberType right, NumberType bottom)
		{
			Left = left;
			Top = top;
			Right = right; 
			Bottom = bottom;
		}
	};
}