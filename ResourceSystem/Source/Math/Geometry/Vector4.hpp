#pragma once

namespace BF
{
	template<class NumberType>
	struct Vector4 
	{
		public:
		NumberType X;
		NumberType Y;
		NumberType Z;
		NumberType W;

		Vector4()
		{
			X = 0;
			Y = 0;
			Z = 0;
			W = 0;
		}

		Vector4(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		Vector4<NumberType> operator+(Vector4<NumberType> vector4)
		{
			Vector4<NumberType> resultVector(*this);

			resultVector.Add(vector4);

			return resultVector;
		}

		void Add(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			X += x;
			Y += y;
			Z += z;
			W += w;
		}

		void Add(Vector4<NumberType> vector4)
		{
			Add(vector4.X, vector4.Y, vector4.Z, vector4.W);
		}

		void Set(NumberType x, NumberType y, NumberType z, NumberType w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}
	};
}