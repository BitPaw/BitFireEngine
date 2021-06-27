#pragma once

#include <math.h>


#include "../Point.hpp"
#include "../../Math.h"


// scalar is just the Magnitude

namespace BF
{
	template<class NumberType>
	struct Vector2 : public Point<NumberType>
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

			Angle = atanf(this->Y / this->X) * 180 / Math::PI;
		}

		public:

		// Lengh
		float Magnitude;

		// Degrees
		float Angle;

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


		// a x b
		virtual Vector2 CrossProduct(Vector2 vector)
		{
			Vector2 crossProduct;
			float length = Magnitude * vector.Magnitude;
			float angle = Angle * vector.Angle;

			crossProduct.FromPolarCoordinates(1, 0);

			crossProduct *= Magnitude * vector.Magnitude * angle;

			return crossProduct;
		}

		virtual void FromPolarCoordinates(NumberType magnitute, NumberType direction)
		{
			Angle = direction;
			Magnitude = magnitute;

			CalculateX();
			CalculateY();
		}
		virtual void FromCartesianCoordinates(NumberType x, NumberType y)
		{
			this->X = x;
			this->Y = y;

			CalculateMagnitude();
			CalculateAngle();
		}
	};
}