#include "Pentagon.h"

Pentagon::Pentagon() : Pentagon(Point(), Point(), Point(), Point(), Point())
{
	Reset();
}

Pentagon::Pentagon(Point a, Point b, Point c, Point d, Point e) : Shape(5, 6)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;

	std::vector<unsigned int> data = { 0, 1, 2, 2, 3, 0};
	DrawOrder.swap(data);
}

void Pentagon::Reset()
{
	
}
