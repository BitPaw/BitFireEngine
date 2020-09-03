#include "RGBEightBit.h"

RGBEightBit::RGBEightBit() : RGBEightBit('\xFF', '\xFF', '\xFF')
{
}

RGBEightBit::RGBEightBit(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	Red = red;
	Green = green;
	Blue = blue;
}
