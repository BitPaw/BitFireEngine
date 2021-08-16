#include "Triangle.h"

BF::Triangle::Triangle() 
{
	Set(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f);
}

BF::Triangle::Triangle(float xA, float yA, float xB, float yB, float xC, float yC) 
{
	Set(xA, yA, xB, yB, xC, yC);
}

BF::Triangle::Triangle(Point<float> a, Point<float> b, Point<float> c)
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

BF::Position<float> BF::Triangle::NormalDirection()
{
	Position<float> u = PointB - PointA;
	Position<float> v = PointC - PointA;
	Position<float> normal = u.CrossProduct(v);

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

void BF::Triangle::Set(Point<float> a, Point<float> b, Point<float> c)
{
	PointA.Set(a);
	PointB.Set(b);
	PointC.Set(c);
}