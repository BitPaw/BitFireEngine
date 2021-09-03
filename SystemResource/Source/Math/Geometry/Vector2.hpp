#pragma once

#include <math.h>
#include "../Math.h"

namespace BF
{
	template<class NumberType>
	struct Vector2
	{
		protected:
		virtual void CalculateX()
		{
			this->X = Magnitude * Math::Cosinus(Angle);
		}

		virtual void CalculateY()
		{
			this->Y = Magnitude * Math::Sinus(Angle);
		}

		virtual void CalculateMagnitude()
		{
			Magnitude = Math::Pythagoras(this->X, this->Y);
		}
		virtual void CalculateAngle()
		{
			//Angle = atanf(Y / X);

			Angle = atanf(this->Y / this->X) * 180 / PI;
		}

		public:

		NumberType X;
		NumberType Y;

		// Lengh
		NumberType Magnitude;

		// Degrees
		NumberType Angle;

		//---------------------------------------------------------------------
		// Addition //
		Vector2 operator+(Vector2 vector)
		{
			return Vector2(this->X + vector.X, this->Y + vector.Y);
		}
		Vector2& operator+=(const Vector2& vector)
		{
			this->X += vector.X;
			this->Y += vector.Y;

			return *this;
		}

		// Substraction //
		Vector2 operator-(Vector2 vector)
		{
			return Vector2(this->X - vector.X, this->Y - vector.Y);
		}
		Vector2& operator-=(const Vector2& vector)
		{
			this->X -= vector.X;
			this->Y -= vector.Y;

			return *this;
		}

		// Multiplication //
		Vector2 operator*(NumberType scalar)
		{
			return Vector2(this->X * scalar, this->Y * scalar);
		}
		Vector2& operator*=(NumberType scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;

			return *this;
		}
		//---------------------------------------------------------------------

		Vector2()
		{
			FromCartesianCoordinates(0, 0);
		}

		Vector2(NumberType x, NumberType y)
		{
			FromCartesianCoordinates(x, y);
		}

		void Set(Vector2<NumberType> vector)
		{
			Set(vector.X, vector.Y);
		}

		void Set(NumberType x, NumberType y)
		{
			X = x;
			Y = y;
		}







		void Add(NumberType x, NumberType y)
		{
			X += x;
			Y += y;
		}

		void Add(Vector2<NumberType> point)
		{
			Add(point.X, point.Y);
		}

		void Substract(NumberType x, NumberType y)
		{
			X -= x;
			Y -= y;
		}

		void Substract(Vector2<NumberType> point)
		{
			Substract(point.X, point.Y);
		}

		void Multiply(NumberType x, NumberType y)
		{
			X *= x;
			Y *= y;
		}

		void Multiply(Vector2<NumberType> point)
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

		void Divide(Vector2<NumberType> point)
		{
			Divide(point.X, point.Y);
		}

		void Rotate(Vector2<NumberType> rotate)
		{

		}











		/// <summary>
	/// The point between pojnt a and b.
	/// </summary>
	/// <param name="point">Point in 2D Space</param>
	/// <returns>DotProduct of a and b</returns>
		NumberType DotProduct(Vector2<NumberType> point)
		{
			// a � b = ax � bx + ay � by
			return X * point.X + Y * point.Y;
		}

		NumberType DistanceTo(Vector2<NumberType> point)
		{
			// d = Root((x2?x1)^2 + (y2?y1)^2)
			return Math::SquareRoot(Math::PowerOfTwo(point.X - X) + Math::PowerOfTwo(point.Y - Y));
		}

		// a x b
		Vector2 CrossProduct(Vector2 vector)
		{
			Vector2 crossProduct;
			float length = Magnitude * vector.Magnitude;
			float angle = Angle * vector.Angle;

			crossProduct.FromPolarCoordinates(1, 0);

			crossProduct *= Magnitude * vector.Magnitude * angle;

			return crossProduct;
		}

		void FromPolarCoordinates(NumberType magnitute, NumberType direction)
		{
			Angle = direction;
			Magnitude = magnitute;

			CalculateX();
			CalculateY();
		}
		void FromCartesianCoordinates(NumberType x, NumberType y)
		{
			this->X = x;
			this->Y = y;

			CalculateMagnitude();
			CalculateAngle();
		}
	};
}