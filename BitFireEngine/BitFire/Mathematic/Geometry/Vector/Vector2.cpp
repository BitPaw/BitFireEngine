#include "Vector2.h"

// scalar is just the Magnitude

BF::Vector2::Vector2()
{
	FromCartesianCoordinates(0,0);
}

BF::Vector2::Vector2(const float x, const float y)
{
	FromCartesianCoordinates(x, y);
}

void BF::Vector2::CalculateX()
{
	X = Magnitude * cosf(Angle);
}

void BF::Vector2::CalculateY()
{
	Y = Magnitude * sinf(Angle);
}

void BF::Vector2::CalculateMagnitude()
{
	Magnitude = sqrtf(powf(X, 2) + pow(Y, 2));
}

void BF::Vector2::CalculateAngle()
{
	//Angle = atanf(Y / X);

	Angle = atanf(Y / X) * 180 / 3.14159265f;
}

BF::Vector2& BF::Vector2::operator+=(const Vector2& vector)
{	
	X += vector.X;
	Y += vector.Y;

	return *this;	
}

BF::Vector2& BF::Vector2::operator-=(const Vector2& vector)
{
	X -= vector.X;
	Y -= vector.Y;

	return *this;
}

BF::Vector2 BF::Vector2::operator*(float scalar)
{
	return Vector2(X * scalar, Y * scalar);
}

BF::Vector2& BF::Vector2::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;

	return *this;
}

BF::Vector2 BF::Vector2::operator+(Vector2 vector)
{
	return Vector2(X + vector.X, Y + vector.Y);
}

BF::Vector2 BF::Vector2::operator-(Vector2 vector)
{
	return Vector2(X - vector.X, Y - vector.Y);
}

float BF::Vector2::DotProduct(Vector2 vector)
{
	// a · b = ax × bx + ay × by
	return X * vector.X + Y * vector.Y;
}

BF::Vector2 BF::Vector2::CrossProduct(Vector2 vector)
{
	Vector2 crossProduct;
	float length = Magnitude * vector.Magnitude;
	float angle = Angle * vector.Angle;

	crossProduct.FromPolarCoordinates(1, 0);

	crossProduct *= Magnitude * vector.Magnitude * angle;
		
	return crossProduct;
}

void BF::Vector2::FromPolarCoordinates(const float magnitute, const float direction)
{
	Angle = direction;
	Magnitude = magnitute;

	CalculateX();
	CalculateY();
}

void BF::Vector2::FromCartesianCoordinates(const float x, const float y)
{
	X = x;
	Y = y;

	CalculateMagnitude();
	CalculateAngle();
}