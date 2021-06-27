#pragma once

#include "../../Dependencies/include/glm/glm.hpp"
#include "Position.hpp"

namespace BF
{
	typedef glm::vec3 Vector3;

	/*
	struct Vector3 : glm::vec3
	{
		public:
		Vector3() : Vector3(0,0,0)
		{

		}

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3 operator*(float scalar)
		{
			float rx = x * scalar;
			float ry = y * scalar;
			float rz = z * scalar;

			return Vector3(rx, ry, rz);
		}
	};*/

	/*
	* 
	* #include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
	* 
	template<class NumberType>
	struct Vector3 : public Position<NumberType>
	{
		protected:
		virtual void CalculateMagnitude()
		{
			Magnitude = sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
		}

		public:
		Vector3()
		{
			FromCartesianCoordinates(0, 0, 0);
		}
		Vector3(NumberType x, NumberType y)
		{
			FromCartesianCoordinates(x, y, 0);
		}
		Vector3(NumberType x, NumberType y, NumberType z)
		{
			FromCartesianCoordinates(x, y, z);
		}

		//---------------------------------------------------------------------
		// Addition //
		Vector3 operator+(Vector3 vector)
		{
			return Vector3(X + vector.X, Y + vector.Y, Z + vector.Z);
		}
		Vector3& operator+=(const Vector3& vector)
		{
			X += vector.X;
			Y += vector.Y;
			Z += vector.Z;

			return *this;
		}

		// Substraction //
		Vector3 operator-(Vector3 vector)
		{
			return Vector3(X - vector.X, Y - vector.Y, Z - vector.Z);
		}
		Vector3& operator-=(const Vector3& vector)
		{
			X -= vector.X;
			Y -= vector.Y;
			Z -= vector.Z;

			return *this;
		}

		// Multiplication //
		Vector3 operator*(float scalar);
		Vector3& operator*=(float scalar);

		bool operator==(const Vector3 vector)
		{
			return X == vector.X && Y == vector.Y && Z == vector.Z;
		}
		//---------------------------------------------------------------------

		virtual void FromCartesianCoordinates(const float x, const float y, const float z)
		{
			X = x;
			Y = y;
			Z = z;

			CalculateMagnitude();
			Angle = atanf(Y / X);
		}
	};
	*/
}