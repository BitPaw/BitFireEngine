#pragma once

#include "../../../../Dependencies/include/glm/glm.hpp"
#include "../Math.h"

namespace BF
{
	template <class NumberType>
	struct Vector3
	{
		public:
		NumberType X;
		NumberType Y;
		NumberType Z;

		Vector3()
		{
			X = 0;
			Y = 0;
			Z = 0;
		}

		Vector3(NumberType x, NumberType y, NumberType z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		void operator+=(NumberType scalar)
		{
			X += scalar;
			Y += scalar;
			Z += scalar;
		}

		void operator+=(Vector3<NumberType> vector3)
		{
			X += vector3.X;
			Y += vector3.Y;
			Z += vector3.Z;
		}

		Vector3 operator+(Vector3<NumberType> vector3)
		{
			NumberType rx = X + vector3.X;
			NumberType ry = Y + vector3.Y;
			NumberType rz = Z + vector3.Z;

			return Vector3<NumberType>(rx, ry, rz);
		}

		void operator-=(Vector3<NumberType> vector)
		{
			X -= vector.X;
			Y -= vector.Y;
			Z -= vector.Z;
		}

		void operator*=(Vector3<NumberType> vector3)
		{
			X *= vector3.X;
			Y *= vector3.Y;
			Z *= vector3.Z;
		}

		void operator*=(NumberType scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
		}

		Vector3<NumberType> operator*(NumberType scalar)
		{
			NumberType rx = X * scalar;
			NumberType ry = Y * scalar;
			NumberType rz = Z * scalar;

			return Vector3<NumberType>(rx, ry, rz);
		}

		Vector3<NumberType> operator*(Vector3<NumberType> vector3)
		{
			NumberType rx = X * vector3.X;
			NumberType ry = Y * vector3.Y;
			NumberType rz = Z * vector3.Z;

			return Vector3<NumberType>(rx, ry, rz);
		}

		Vector3<NumberType> operator/(NumberType scalar)
		{
			NumberType rx = X / scalar;
			NumberType ry = Y / scalar;
			NumberType rz = Z / scalar;

			return Vector3<NumberType>(rx, ry, rz);
		}

		void Add(NumberType x, NumberType y, NumberType z)
		{
			X += x;
			Y += y;
			Z += z;
		}

		void Add(Vector3<NumberType> vector)
		{
			X += vector.X;
			Y += vector.Y;
			Z += vector.Z;
		}

		void Multiply(NumberType x, NumberType y, NumberType z)
		{
			X *= x;
			Y *= y;
			Z *= z;
		}


		void Set(NumberType x, NumberType y, NumberType z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		void Normalize()
		{
			NumberType length = Length();

			if (length != 0)
			{
				X /= length;
				Y /= length;
				Z /= length;
			}			
		}

		static Vector3<NumberType> Normalize(Vector3 vector3)
		{
			Vector3<NumberType> newVector(vector3);

			newVector.Normalize();

			return newVector;
		}

		NumberType Length()
		{
			NumberType x = X;
			NumberType y = Y;
			NumberType z = Z;
			NumberType sum = x * x + y * y + z * z;

			return Math::SquareRoot(sum);
		}

		Vector3<NumberType> CrossProduct(Vector3 vector3)
		{
			NumberType resultX = Y * vector3.Z - Z * vector3.Y;
			NumberType resultY = Z * vector3.X - X * vector3.Z;
			NumberType resultZ = X * vector3.Y - Y * vector3.X;

			return Vector3<NumberType>(resultX, resultY, resultZ);
		}

		Vector3<NumberType> CrossProduct(NumberType x, NumberType y, NumberType z)
		{
			NumberType resultX = Y * z - Z * y;
			NumberType resultY = Z * x - X * z;
			NumberType resultZ = X * y - Y * x;

			return Vector3<NumberType>(resultX, resultY, resultZ);
		}

		void CrossProduct(Vector3<NumberType> vectorA, Vector3<NumberType> vectorB)
		{
			X = vectorA.Y * vectorB.Z - vectorA.Z * vectorB.Y;
			Y = vectorA.Z * vectorB.X - vectorA.X * vectorB.Z;
			Z = vectorA.X * vectorB.Y - vectorA.Y * vectorB.X;
		}

		void Rotate(Vector3<NumberType> rotation)
		{
			NumberType x = X;
			NumberType y = Y;
			NumberType z = Z;

			rotation.X = Math::DegreeToRadians(rotation.X);
			rotation.Y = Math::DegreeToRadians(rotation.Y);
			rotation.Z = Math::DegreeToRadians(rotation.Z);

			x = Math::DegreeToRadians(x);
			y = Math::DegreeToRadians(y);
			z = Math::DegreeToRadians(z);

			NumberType tempX = 0;
			NumberType tempY = 0;
			NumberType tempZ = 0;

			NumberType angleSin;
			NumberType angleCos;

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

			x = Math::RadiansToDegree(x);
			y = Math::RadiansToDegree(y);
			z = Math::RadiansToDegree(z);

			 X = x;
			 Y = y;
			 Z = z;
		}
	};
}