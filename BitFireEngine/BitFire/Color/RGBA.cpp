#include "RGBA.h"

RGBA::RGBA() : RGBA(1, 1, 1, 1)
{

}

RGBA::RGBA(float red, float green, float blue) : RGBA(red, green, blue, 1)
{

}

RGBA::RGBA(float red, float green, float blue, float alpha)
{
	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;
}