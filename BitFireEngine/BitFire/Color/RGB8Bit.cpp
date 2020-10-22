#include "RGB8Bit.h"

BF::RGB8Bit::RGB8Bit() : RGB8Bit('\xFF', '\xFF', '\xFF')
{
}

BF::RGB8Bit::RGB8Bit(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	Red = red;
	Green = green;
	Blue = blue;
}
