#include "RGB.h"

RGB::RGB() : RGB(0,0,0)
{

}

RGB::RGB(const float red, const float green, const float blue)
{
	SetColor(red, green, blue);
}

void RGB::SetColor(const float red, const float green, const float blue)
{
	Red = red;
	Green = green;
	Blue = blue;
}
