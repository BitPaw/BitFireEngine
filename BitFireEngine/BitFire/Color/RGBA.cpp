#include "RGBA.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

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

RGBA RGBA::GetRandomeColor()
{
	srand(time(nullptr));

	//float r = rand() % 255;
	//float g = rand() % 255;
	//float b = rand() % 255;


	float r = std::rand() % 255;
	float g = std::rand() % 255;
	float b = std::rand() % 255;


	r = Interpolate::Liniar(0, 1, 0, 255, r);
	g = Interpolate::Liniar(0, 1, 0, 255, g);
	b = Interpolate::Liniar(0, 1, 0, 255, b);

	return RGBA(r, g, b);
}
