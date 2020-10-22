#include "Rectangle.h"

BF::Rectangle::Rectangle() : Rectangle(Point(), Point(), Point(), Point())
{
	const float x = 0.5f;
	const float y = 0.25f;

	A = Point(-x, -y);
	B = Point(x, -y);
	C = Point(x, y);
	D = Point(-x, y);
}

BF::Rectangle::Rectangle(Point a, Point b, Point c, Point d) : Shape(4)
{
	A = a;
	B = b;
	C = c;
	D = d;
}