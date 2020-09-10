#pragma once

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

		virtual Vector3 CrossProduct(Vector3 vector);

		virtual void FromCartesianCoordinates(const float x, const float y, const float z);
	};
}