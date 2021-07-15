#pragma once

#include "../../../Dependencies/include/glm/glm.hpp"
#include "Position.hpp"
#include "../Math.h"

namespace BF
{
	template <class NumberType>
	struct Vector3
	{
		public:
		NumberType Data[3];

		Vector3()
		{
			this->Data[0] = 0;
			this->Data[1] = 0;
			this->Data[2] = 0;
		}

		Vector3(NumberType x, NumberType y, NumberType z)
		{
			this->Data[0] = x;
			this->Data[1] = y;
			this->Data[2] = z;
		}

		void operator+=(Vector3<NumberType>& vector3)
		{
			this->Data[0] += vector3.Data[0];
			this->Data[1] += vector3.Data[1];
			this->Data[2] += vector3.Data[2];
		}

		Vector3 operator+(Vector3<NumberType> vector3)
		{
			NumberType rx = this->Data[0] + vector3.Data[0];
			NumberType ry = this->Data[1] + vector3.Data[1];
			NumberType rz = this->Data[2] + vector3.Data[2];

			return Vector3<NumberType>(rx, ry, rz);
		}

		void operator*=(Vector3<NumberType> vector3)
		{
			this->Data[0] *= vector3.Data[0];
			this->Data[1] *= vector3.Data[1];
			this->Data[2] *= vector3.Data[2];
		}

		void operator*=(NumberType scalar)
		{
			this->Data[0] *= scalar;
			this->Data[1] *= scalar;
			this->Data[2] *= scalar;
		}

		Vector3 operator*(NumberType scalar)
		{
			NumberType rx = this->Data[0] * scalar;
			NumberType ry = this->Data[1] * scalar;
			NumberType rz = this->Data[2] * scalar;

			return Vector3<NumberType>(rx, ry, rz);
		}

		Vector3 operator*(Vector3<NumberType> vector3)
		{
			NumberType rx = this->Data[0] * vector3.Data[0];
			NumberType ry = this->Data[1] * vector3.Data[1];
			NumberType rz = this->Data[2] * vector3.Data[2];

			return Vector3<NumberType>(rx, ry, rz);
		}


		void Set(NumberType x, NumberType y, NumberType z)
		{
			Data[0] = x;
			Data[1] = y;
			Data[2] = z;
		}

		void Normalize()
		{
			NumberType length = Length();

			Data[0] /= length;
			Data[1] /= length;
			Data[2] /= length;
		}

		NumberType Length()
		{
			NumberType x = Data[0];
			NumberType y = Data[1];
			NumberType z = Data[2];
			NumberType sum = x * x + y * y + z * z;

			return Math::SquareRoot(sum);
		}

		Vector3<NumberType> CrossProduct(Vector3 vector3)
		{
			NumberType resultX = this->Data[1] * vector3.Data[2] - this->Data[2] * vector3.Data[1];
			NumberType resultY = this->Data[2] * vector3.Data[0] - this->Data[0] * vector3.Data[2];
			NumberType resultZ = this->Data[0] * vector3.Data[1] - this->Data[1] * vector3.Data[0];

			return Vector3<NumberType>(resultX, resultY, resultZ);
		}

		Vector3<NumberType> CrossProduct(NumberType x, NumberType y, NumberType z)
		{
			NumberType resultX = this->Data[1] * z - this->Data[2] * y;
			NumberType resultY = this->Data[2] * x - this->Data[0] * z;
			NumberType resultZ = this->Data[0] * y - this->Data[1] * x;

			return Vector3<NumberType>(resultX, resultY, resultZ);
		}

		void CrossProduct(Vector3<NumberType> vectorA, Vector3<NumberType> vectorB)
		{
			this->Data[0] = vectorA.Data[1] * vectorB.Data[2] - vectorA.Data[2] * vectorB.Data[1];
			this->Data[1] = vectorA.Data[2] * vectorB.Data[0] - vectorA.Data[0] * vectorB.Data[2];
			this->Data[2] = vectorA.Data[0] * vectorB.Data[1] - vectorA.Data[1] * vectorB.Data[0];
		}
	};
}


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