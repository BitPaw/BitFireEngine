#include "Square.h"

BF::Square::Square()
{
	Set(1);
}

BF::Square::Square(float sideLength)
{
	Set(sideLength);
}

BF::Square::Square(Vector2<float> size)
{
	Set(size);
}

float BF::Square::SideLength()
{
	return MathAbsolute(PointA.X - PointB.X);
}

float BF::Square::SurfaceArea()
{
	return MathPowerOfTwo(SideLength());
}

float BF::Square::Perimeter()
{
	return SideLength() * 4;
}

void BF::Square::Set(float sideLength)
{
	PointA.Set(0, 0);
	PointB.Set(sideLength, sideLength);
}

void BF::Square::Set(Vector2<float> size)
{
	PointA.Set(0,0);
	PointB.Set(size);
}
