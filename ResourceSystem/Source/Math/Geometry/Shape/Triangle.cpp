#include "Triangle.h"

BF::Triangle::Triangle() 
{
	Set(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f);
}

BF::Triangle::Triangle(float xA, float yA, float xB, float yB, float xC, float yC) 
{
	Set(xA, yA, xB, yB, xC, yC);
}

BF::Triangle::Triangle(Vector2<float> a, Vector2<float> b, Vector2<float> c)
{
	Set(a, b, c);
}

float BF::Triangle::Height()
{
	return Math::PythagorasReverse(LengthOfSideA(), Width());
}

float BF::Triangle::Width()
{
	return LengthOfSideC();
}

float BF::Triangle::LengthOfSideA()
{
	return PointB.DistanceTo(PointC);
}

float BF::Triangle::LengthOfSideB()
{
	return PointA.DistanceTo(PointC);
}

float BF::Triangle::LengthOfSideC()
{
	return PointA.DistanceTo(PointB);
}

BF::Vector3<float> BF::Triangle::NormalDirection()
{
	Vector2<float> u2 = PointB - PointA;
	Vector2<float> v2 = PointC - PointA;
	Vector3<float> u(u2.X, u2.Y, 0);
	Vector3<float> v(v2.X, v2.Y, 0);
	Vector3<float> normal = u.CrossProduct(v);

	return normal;
}

float BF::Triangle::DegreeAlpha()
{
	return asin(LengthOfSideA() / LengthOfSideC());
}

float BF::Triangle::DegreeBeta()
{
	return asin(LengthOfSideB() / LengthOfSideA());
}

float BF::Triangle::DegreeGamma()
{
	return asin(LengthOfSideC() / LengthOfSideB());
}

float BF::Triangle::SurfaceArea()
{
	return 0.5 * Width() * Height();
}

float BF::Triangle::Perimeter()
{
	return LengthOfSideA() + LengthOfSideB() + LengthOfSideC();
}

void BF::Triangle::Set(float xA, float yA, float xB, float yB, float xC, float yC)
{
	PointA.Set(xA, yA);
	PointB.Set(xB, yB);
	PointC.Set(xC, yC);
}

void BF::Triangle::Set(Vector2<float> a, Vector2<float> b, Vector2<float> c)
{
	PointA.Set(a);
	PointB.Set(b);
	PointC.Set(c);
}