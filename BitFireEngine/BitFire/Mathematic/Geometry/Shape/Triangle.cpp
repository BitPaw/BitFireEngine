#include "Triangle.h"

Triangle::Triangle() : Triangle(Point(), Point(), Point())
{
	A = Point(-0.5f, -0.5f);
	B = Point(0.5f, -0.5f);
	C = Point(0.0f, 0.5f);
}

Triangle::Triangle(Point a, Point b, Point c) : Shape(3)
{
	A = a;
	B = b;
	C = c;
}