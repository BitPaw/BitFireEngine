#include "Pentagon.h"

Pentagon::Pentagon() : Pentagon(Point(), Point(), Point(), Point(), Point())
{

}

Pentagon::Pentagon(Point a, Point b, Point c, Point d, Point e) : Shape(5)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
}