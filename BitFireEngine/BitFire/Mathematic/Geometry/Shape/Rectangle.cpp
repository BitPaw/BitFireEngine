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
	const float x = 0.5f;
	const float y = 0.25f;

	A = Point(-x, -y);
	B = Point(x, -y);
	C = Point(x, y);
	D = Point(-x, y);
}