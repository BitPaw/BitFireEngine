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

		Vector4<NumberType> operator+(Vector4<NumberType> vector4)
		{
			Vector4<NumberType> resultVector(*this);

			resultVector.Add(vector4);

			return resultVector;
		}

		void Add(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			Date[0] += x;
			Date[1] += y;
			Date[2] += z;
			Date[3] += w;
		}


		void Add(Vector4<NumberType>& vector4)
		{
			Add(vector4.Date[0], vector4.Date[1], vector4.Date[2], vector4.Date[3]);
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