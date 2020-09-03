#include "RGBA.h"

RGBA::RGBA()
{
	SetColor(1, 1, 1, 1);
}

RGBA::RGBA(const float red, const float green, const float blue)
{
	SetColor(red, green, blue, 1);
}

RGBA::RGBA(const float red, const float green, const float blue, const float alpha)
{
	SetColor(red, green, blue, alpha);
}

void RGBA::SetColor(const float red, const float green, const float blue)
{
	SetColor(red, green, blue, 1);
}

void RGBA::SetColor(const float red, const float green, const float blue, const float alpha)
{
	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;	
}