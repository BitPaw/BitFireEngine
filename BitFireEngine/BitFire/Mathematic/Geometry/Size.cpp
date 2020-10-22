#include "Size.h"

BF::Size::Size() : Size(0,0)
{
	
}

BF::Size::Size(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
}