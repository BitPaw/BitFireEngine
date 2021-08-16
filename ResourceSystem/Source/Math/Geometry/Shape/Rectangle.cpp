#include "Rectangle.h"

BF::Rectangle::Rectangle()
{
	Set(1, 1);
}

BF::Rectangle::Rectangle(float width, float height)
{
	Set(width, height);
}

BF::Rectangle::Rectangle(float x, float y, float width, float height)
{
	Set(x, y, width, height);
}

BF::Rectangle::Rectangle(Point<float> a, Point<float> b)
{
	Set(a, b);
}

BF::Rectangle::Rectangle(Point<float> a, Point<float> b, Point<float> c, Point<float> d)
{
	Set(a, b, c, d);
}

float BF::Rectangle::Width()
{
	return Math::Absolute(PointA.X + PointC.X);
}

float BF::Rectangle::Height()
{
	return Math::Absolute(PointA.Y + PointC.Y);
}

float BF::Rectangle::SurfaceArea()
{
	return Width() * Height();
}

float BF::Rectangle::Perimeter()
{
	return 0.0f;
}

bool BF::Rectangle::IsColliding(Rectangle* rectangle)
{
	//D C 
	//A B
	float r1X = PointA.X;
	float r1Y = PointA.Y;
	float r1Width = Width();
	float r1Height = Height();

	float r2X = rectangle->PointA.X;
	float r2Y = rectangle->PointA.Y;
	float r2Width = rectangle->Width();
	float r2Height = rectangle->Height();

	return	r1X < r2X + r2Width &&
			r1X + r1Width > r2X &&
			r1Y < r2Y + r2Height &&
			r1Y + r1Height > r2Y;
}

BF::Position<float> BF::Rectangle::NormalDirection()
{
	Position<float> u = PointB - PointA;
	Position<float> v = PointC - PointA;
	Position<float> normal = u.CrossProduct(v);

	u = PointC - PointB;
	v = PointD - PointB;
	normal *= u.CrossProduct(v);

	return normal;
}

void BF::Rectangle::Set(float width, float height)
{
	Set(0, 0, width, height);
}

void BF::Rectangle::Set(float x, float y, float width, float height)
{
	PointA.Set(x, y);
	PointB.Set(width, y);
	PointC.Set(width, height);
	PointD.Set(x, height);
}

void BF::Rectangle::Set(Point<float> a, Point<float> b)
{
	PointA.Set(a);
	PointB.Set(b.X, a.Y);
	PointC.Set(b);
	PointD.Set(a.X, b.Y);
}

void BF::Rectangle::Set(Point<float> a, Point<float> b, Point<float> c, Point<float> d)
{
	PointA.Set(a);
	PointB.Set(b);
	PointC.Set(c);
	PointD.Set(d);
}
