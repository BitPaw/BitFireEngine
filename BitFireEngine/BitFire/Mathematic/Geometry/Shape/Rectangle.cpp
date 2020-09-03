#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(Point(), Point(), Point(), Point())
{
	Reset();
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : Shape(4, 6)
{
	A = a;
	B = b;
	C = c;
	D = d;

	DrawOrder.push_back(0);
	DrawOrder.push_back(1);
	DrawOrder.push_back(2);
	DrawOrder.push_back(2);
	DrawOrder.push_back(3);
	DrawOrder.push_back(0);
}

void Rectangle::Reset()
{
	A = Point(-0.5f, 0.25f);
	B = Point(0.5f, 0.25f);
	C = Point(0.5f, -0.25f);
	D = Point(-0.5f, -0.25f);
}