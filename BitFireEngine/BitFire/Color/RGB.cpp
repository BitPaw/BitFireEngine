#include "RGB.h"

BF::RGB::RGB() : RGB(0,0,0)
{

}

BF::RGB::RGB(const float red, const float green, const float blue)
{
	SetColor(red, green, blue);
}

void BF::RGB::SetColor(const float red, const float green, const float blue)
{
	Red = red;
	Green = green;
	Blue = blue;
}
