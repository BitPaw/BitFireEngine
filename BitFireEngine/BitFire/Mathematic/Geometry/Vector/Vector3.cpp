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

BF::Vector3 BF::Vector3::operator+(Vector3 vector)
{
	return Vector3(X + vector.X, Y + vector.Y, Z + vector.Z);
}

BF::Vector3& BF::Vector3::operator+=(const Vector3& vector)
{
	X += vector.X;
	Y += vector.Y;
	Z += vector.Z;

	return *this;
}

BF::Vector3 BF::Vector3::operator-(Vector3 vector)
{
	return Vector3(X - vector.X, Y - vector.Y, Z - vector.Z);
}

BF::Vector3& BF::Vector3::operator-=(const Vector3& vector)
{
	X -= vector.X;
	Y -= vector.Y;
	Z -= vector.Z;

	return *this;
}

BF::Vector3 BF::Vector3::operator*(float scalar)
{
	return Vector3();
}

BF::Vector3& BF::Vector3::operator*=(float scalar)
{
	return *this;
}

bool BF::Vector3::operator==(const Vector3 vector)
{
	return X == vector.X && Y == vector.Y && Z == vector.Z;
}

void BF::Vector3::Rotate(Vector3 vector)
{
	/*
	rotating around the Z-axis would be

	|cos Q   -sin Q   0| |x|   |x cos Q - y sin Q|   |x'|
	|sin Q    cos Q   0| |y| = |x sin Q + y cos Q| = |y'|
	|  0       0      1| |z|   |        z        |   |z'|

	around the Y-axis would be

	| cos Q    0   sin Q| |x|   | x cos Q + z sin Q|   |x'|
	|   0      1       0| |y| = |         y        | = |y'|
	|-sin Q    0   cos Q| |z|   |-x sin Q + z cos Q|   |z'|

	around the X-axis would be

	|1     0           Q| |x|   |        x        |   |x'|
	|0   cos Q    -sin Q| |y| = |y cos Q - z sin Q| = |y'|
	|0   sin Q     cos Q| |z|   |y sin Q + z cos Q|   |z'|

	Note 1: axis around which rotation is done has no sine or cosine elements in the matrix.
	*/

	float c;
	float XTemp = 0;
	float YTemp = 0;

	// Z Rotation
	XTemp = X;
	c = vector.Z;
	X = X * cos(c) - Y * sin(c);
	Y = XTemp * sin(c) + Y * cos(c);

	// Y Rotation
	XTemp = X;
	c = vector.Y;
	X = X * cos(c) + Z * sin(c);
	Z = -XTemp * sin(c) + Z * cos(c);

	// X Rotation
	YTemp = Y;
	c = vector.Z;
	Y = Y * cos(c) - Z * sin(c);
	Z = YTemp * sin(c) + Z * cos(c);
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