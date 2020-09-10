#pragma once

#include <math.h>

namespace BF
{
	struct Vector2
	{
	protected:
		virtual void CalculateX();
		virtual void CalculateY();

		virtual void CalculateMagnitude();
		virtual void CalculateAngle();

	public:

		// Lengh
		float Magnitude;

		// Degrees
		float Angle;

		float X;
		float Y;



		void operator*(float scalar);
		Vector2& operator*=(float scalar);

		void operator+(Vector2 vector);
		Vector2& operator+=(const Vector2& vector);

		void operator-(Vector2 vector);
		Vector2& operator-=(const Vector2& vector);



		Vector2();
		Vector2(const float x, const float y);

		float DotProduct(Vector2 vector);

		// a x b
		virtual Vector2 CrossProduct(Vector2 vector);

		virtual void FromPolarCoordinates(const float magnitute, const float direction);
		virtual void FromCartesianCoordinates(const float x, const float y);
	};
}