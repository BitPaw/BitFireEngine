#pragma once

#include <math.h>

#include "Point.hpp"
#include "../Math.h"

namespace BF
{
	// [X|Y|Z] Position in 3D-WorldSpace. 
	template <class NumberType>
	struct Position : public Point<NumberType>
	{
		public:
		NumberType Z;

		bool operator==(Position<NumberType> position)
		{
			return IsEqual(position);;
		}

		Position<NumberType> operator=(Position<NumberType> position)
		{
			Set(position);

			return *this;
		}

		Position operator+(Position<NumberType>& position)
		{
			position.Add(*this);

			return position;
		}

		Position<NumberType> operator+=(Position<NumberType> position)
		{
			Add(position);

			return *this;
		}

		Position<NumberType> operator-(Position<NumberType> position)
		{
			Substract(position);

			return *this;
		}

		Position<NumberType> operator-=(Position<NumberType> position)
		{
			Substract(position);

			return *this;
		}

		Position<NumberType> operator*(Position<NumberType> position)
		{
			position.Multiply(*this);

			return position;
		}

		Position<NumberType> operator*=(Position<NumberType> position)
		{
			Multiply(position);

			return *this;
		}

		Position<NumberType> operator/(Position<NumberType> position)
		{
			position.Divide(*this);

			return position;
		}

		Position<NumberType> operator/=(Position<NumberType> position)
		{
			Divide(position);

			return *this;
		}

		Position()
		{
			Set(0, 0, 0);
		}

		Position(Point<NumberType> point)
		{
			Set(point.X, point.Y, 0);
		}

		Position(NumberType x, NumberType y)
		{
			Set(x, y, 0);
		}

		Position(NumberType x, NumberType y, NumberType z)
		{
			Set(x, y, z);
		}

		void Add(NumberType x, NumberType y, NumberType z)
		{
			this->X += x;
			this->Y += y;
			Z += z;
		}

		void Add(Position<NumberType> position)
		{
			Add(position.X, position.Y, position.Z);
		}

		void Substract(NumberType x, NumberType y, NumberType z)
		{
			this->X -= x;
			this->Y -= y;
			Z -= z;
		}

		void Substract(Position<NumberType> position)
		{
			Substract(position.X, position.Y, position.Z);
		}

		void Multiply(NumberType x, NumberType y, NumberType z)
		{
			this->X *= x;
			this->Y *= y;
			Z *= z;
		}

		void Multiply(Position<NumberType> position)
		{
			Multiply(position.X, position.Y, position.Z);
		}

		void Divide(NumberType x, NumberType y, NumberType z)
		{
			if (x == 0 || y == 0 || z == 0)
			{
				throw "Divide by Zero";
			}

			this->X /= x;
			this->Y /= y;
			Z /= z;
		}

		void Divide(Position<NumberType> position)
		{
			Divide(position.X, position.Y, position.Z);
		}

		bool IsEqual(Position<NumberType> position)
		{
			return this->X == position.X && this->Y == position.Y && Z == position.Z;
		}

		void Rotate(Position<NumberType> rotation)
		{			
			float x = this->X;
			float y = this->Y;
			float z = this->Z;

			float tempX = 0; 
			float tempY = 0;
			float tempZ = 0;

			float angleSin;
			float angleCos;			

			//--[Z-Axis rotation]-----------------------------------
			angleSin = Math::Sinus(rotation.Z);
			angleCos = Math::Cosinus(rotation.Z);

			tempX = angleCos * x - angleSin * y;
			tempY = angleSin * x + angleCos * y;

			x = tempX;
			y = tempY;
			//------------------------------------------------------

			//--[Y-Axis rotation]-----------------------------------
			angleSin = Math::Sinus(rotation.Y);
			angleCos = Math::Cosinus(rotation.Y);

			tempX = angleCos * x + angleSin * z;
			tempZ = -angleSin * x + angleCos * z;

			x = tempX;
			z = tempZ;
			//------------------------------------------------------

			//--[X-Axis rotation]-----------------------------------
			angleSin = Math::Sinus(rotation.X);
			angleCos = Math::Cosinus(rotation.X);

			tempY = angleCos * y - angleSin * z;
			tempZ = angleSin * y + angleCos * z;

			y = tempY;
			z = tempZ;
			//------------------------------------------------------

			Set(x, y, z);
		}

		Position<NumberType> CrossProduct(Position<NumberType> position)
		{
			return Position<NumberType>
			(
				(this->Y * position.Z - this->Z * position.Y),
				(this->Z * position.X - this->X * position.Z),
				(this->X * position.Y - this->Y * position.X)
			);
		}

		void Set(Point<NumberType> point)
		{
			this->X = point.X;
			this->Y = point.Y;
		}

		void Set(Position<NumberType> position)
		{
			this->X = position.X;
			this->Y = position.Y;
			Z = position.Z;
		}

		void Set(NumberType x, NumberType y)
		{
			this->X = x;
			this->Y = y;
		}

		void Set(NumberType x, NumberType y, NumberType z)
		{
			this->X = x;
			this->Y = y;
			Z = z;
		}
	};
}