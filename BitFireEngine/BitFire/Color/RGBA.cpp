#include "RGBA.h"

BF::RGBA::RGBA()
{
	SetColor(1, 1, 1, 1);
}

BF::RGBA::RGBA(const float red, const float green, const float blue)
{
	SetColor(red, green, blue, 1);
}

BF::RGBA::RGBA(const float red, const float green, const float blue, const float alpha)
{
	SetColor(red, green, blue, alpha);
}

void BF::RGBA::SetColor(const float red, const float green, const float blue)
{
	SetColor(red, green, blue, 1);
}

void BF::RGBA::SetColor(const float red, const float green, const float blue, const float alpha)
{
	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;	
}

BF::RGBA BF::RGBA::GetRandomeColor()
{
	float r = Math::RandomeNumber() % 255;
	float g = Math::RandomeNumber() % 255;
	float b = Math::RandomeNumber() % 255;

	r = Interpolate::Liniar(0, 1, 0, 255, r);
	g = Interpolate::Liniar(0, 1, 0, 255, g);
	b = Interpolate::Liniar(0, 1, 0, 255, b);

	return RGBA(r, g, b);
}
