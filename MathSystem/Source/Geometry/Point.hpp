#pragma once

#include "../Math.h"

namespace BF
{
	// [X | Y] Position in 2D-WorldSpace.
	template<class NumberType>
	struct Point
	{
		public:
		NumberType X;
		NumberType Y;

		Point<NumberType> operator=(Point<NumberType> point)
		{
			Set(point);

			return *this;
		}

		Point<NumberType> operator+(Point<NumberType> point)
		{
			point.Add(*this);

			return point;
		}

		Point<NumberType> operator+=(Point<NumberType> point)
		{
			Add(point);

			return *this;
		}

		Point<NumberType> operator-(Point<NumberType> point)
		{
			point.Substract(*this);

			return point;
		}

		Point<NumberType> operator-=(Point<NumberType> point)
		{
			Substract(point);

			return *this;
		}

		Point<NumberType> operator*(Point<NumberType> point)
		{
			point.Multiply(*this);

			return point;
		}

		Point<NumberType> operator*=(Point<NumberType> point)
		{
			Multiply(point);

			return *this;
		}

		Point<NumberType> operator/(Point<NumberType> point)
		{
			point.Divide(*this);

			return point;
		}

		Point<NumberType> operator/=(Point<NumberType> point)
		{
			Divide(point);

			return *this;
		}

		Point()
		{
			Set(0, 0);
		}

		Point(NumberType x, NumberType y)
		{
			Set(x, y);
		}

		void Add(NumberType x, NumberType y)
		{
			X += x;
			Y += y;
		}

		void Add(Point<NumberType> point)
		{
			Add(point.X, point.Y);
		}

		void Substract(NumberType x, NumberType y)
		{
			X -= x;
			Y -= y;
		}

		void Substract(Point<NumberType> point)
		{
			Substract(point.X, point.Y);
		}

		void Multiply(NumberType x, NumberType y)
		{
			X *= x;
			Y *= y;
		}

		void Multiply(Point<NumberType> point)
		{
			Multiply(point.X, point.Y);
		}

		void Divide(NumberType x, NumberType y)
		{
			if (x == 0 || y == 0)
			{
				throw "Divide by Zero";
			}

			X /= x;
			Y /= y;
		}

		void Divide(Point<NumberType> point)
		{
			Divide(point.X, point.Y);
		}

		void Rotate(Point<NumberType> rotate)
		{

		}

		/// <summary>
		/// The point between pojnt a and b.
		/// </summary>
		/// <param name="point">Point in 2D Space</param>
		/// <returns>DotProduct of a and b</returns>
		NumberType DotProduct(Point<NumberType> point)
		{
			// a · b = ax × bx + ay × by
			return X * point.X + Y * point.Y;
		}

		NumberType DistanceTo(Point<NumberType> point)
		{
			// d = Root((x2?x1)^2 + (y2?y1)^2)
			return Math::SquareRoot(Math::PowerOfTwo(point.X - X) + Math::PowerOfTwo(point.Y - Y));
		}

		void Set(Point<NumberType> point)
		{
			Set(point.X, point.Y);
		}

		void Set(NumberType x, NumberType y)
		{
			X = x;
			Y = y;
		}
	};
}