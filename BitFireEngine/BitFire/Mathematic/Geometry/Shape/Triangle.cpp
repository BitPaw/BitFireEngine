#include "Triangle.h"

Triangle::Triangle() : Triangle(Point(), Point(), Point())
{
	Reset();
}

Triangle::Triangle(Point a, Point b, Point c) : Shape(3, 3)
{
	A = a;
	B = b;
	C = c;

	std::vector<unsigned int> data = { 0, 1, 2 };
	DrawOrder.swap(data);
}

void Triangle::Reset()
{
	A = Point(-0.5f, -0.5f);
	B = Point(0.5f, -0.5f);
	C = Point(0.0f, 0.5f);	
}