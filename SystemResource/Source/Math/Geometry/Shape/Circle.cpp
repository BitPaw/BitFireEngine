#include "Circle.h"

BF::Circle::Circle()
{
	Set(1);
}

BF::Circle::Circle(float radius)
{
	Set(radius);
}

BF::Circle::Circle(float midPointx, float midPointy, float cornerPointx, float cornerPointy)
{
	Set(midPointx, midPointy, cornerPointx, cornerPointy);
}

BF::Circle::Circle(Vector2<float> midPoint, Vector2<float> cornerPoint)
{
	Set(midPoint, cornerPoint);
}

float BF::Circle::Radius()
{
	return MiddlePoint.DistanceTo(CornerPoint);
}

float BF::Circle::Diameter()
{
	return Radius() * 2;
}

float BF::Circle::SurfaceArea()
{
	float radius = Radius();

	return PI * radius * radius;
}

float BF::Circle::Perimeter()
{
	return 2 * PI * Radius();
}

void BF::Circle::Set(float radius)
{
	MiddlePoint.Set(0, 0);
	CornerPoint.Set(radius, 0);
}

void BF::Circle::Set(float midPointx, float midPointy, float cornerPointx, float cornerPointy)
{
	MiddlePoint.Set(midPointx, midPointy);
	CornerPoint.Set(cornerPointx, cornerPointy);
}

void BF::Circle::Set(Vector2<float> midPoint, Vector2<float> cornerPoint)
{
	MiddlePoint.Set(midPoint);
	CornerPoint.Set(cornerPoint);
}