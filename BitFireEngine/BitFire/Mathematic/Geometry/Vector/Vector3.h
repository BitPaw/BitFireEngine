#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Vector2.h"

namespace BF
{
	struct Vector3 : public Vector2
	{
	protected:
		virtual void CalculateMagnitude();

	public:
		float Z;

		Vector3();
		Vector3(const float x, const float y);
		Vector3(const float x, const float y, const float z);

		//---------------------------------------------------------------------
		// Addition //
		Vector3 operator+(Vector3 vector);
		Vector3& operator+=(const Vector3& vector);

		// Substraction //
		Vector3 operator-(Vector3 vector);
		Vector3& operator-=(const Vector3& vector);

		// Multiplication //
		Vector3 operator*(float scalar);
		Vector3& operator*=(float scalar);

		bool operator==(const Vector3 vector);
		//---------------------------------------------------------------------

		void Rotate(Vector3 vector);

		virtual Vector3 CrossProduct(Vector3 vector);

		virtual void FromCartesianCoordinates(const float x, const float y, const float z);
	};
}