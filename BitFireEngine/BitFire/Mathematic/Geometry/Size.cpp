#include "Size.h"

Size::Size(unsigned int xA, unsigned int yA, unsigned int xB, unsigned int yB) : Size(IndexPoint(xA, yA), IndexPoint(xB, yB))
{
}

Size::Size(IndexPoint a, IndexPoint b)
{
	A = a;
	B = b;
}
