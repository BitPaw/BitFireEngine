#pragma once

namespace BF
{
	template<class NumberType>
	struct AngleDegree
	{
		public:
		NumberType Value;

		void operator=(float value)
		{
			Value = value;
		}
		void operator=(double value)
		{
			Value = value;
		}
	};
}