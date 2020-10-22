#include "Padding.h"

BF::Padding::Padding() : Padding(0, 0, 0, 0)
{
}

BF::Padding::Padding(const unsigned int all) : Padding(all, all, all, all)
{
}

BF::Padding::Padding(const unsigned int left, const unsigned int right) : Padding(left, 0, right, 0)
{
}

BF::Padding::Padding(const unsigned int left, const unsigned int top, const unsigned int right, const unsigned int bottom)
{
	Left = left;
	Top = top;
	Right = right;
	Bottom = bottom;
}
