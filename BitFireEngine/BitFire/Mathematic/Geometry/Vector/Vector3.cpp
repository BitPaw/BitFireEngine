#include "Vector3.h"

BF::Vector3::Vector3()
{
	FromCartesianCoordinates(0, 0, 0);
}

BF::Vector3::Vector3(const float x, const float y)
{
	FromCartesianCoordinates(x, y, 0);
}

BF::Vector3::Vector3(const float x, const float y, const float z)
{
	FromCartesianCoordinates(x, y, z);
}

BF::Vector3 BF::Vector3::CrossProduct(Vector3 vector)
{
	float x = Y * vector.Z - Z * vector.Y;
	float y = Z * vector.X - X * vector.Z;
	float z = X * vector.Y - Y * vector.X;
	
	Vector3 crossProduct(x, y, z);

	return crossProduct;
}

void BF::Vector3::CalculateMagnitude()
{
	Magnitude = sqrtf(powf(X, 2) + powf(Y, 2) + powf(Z, 2));
}

void BF::Vector3::FromCartesianCoordinates(const float x, const float y, const float z)
{
	X = x;
	Y = y;
	Z = z;

	CalculateMagnitude();
	Angle = atanf(Y / X);
}