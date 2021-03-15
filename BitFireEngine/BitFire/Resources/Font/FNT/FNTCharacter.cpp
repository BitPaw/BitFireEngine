#include "FNTCharacter.h"

BF::FNTCharacter::FNTCharacter() : FNTCharacter(-1, Point<float>(), Point<float>(), Point<float>(), -1)
{

}

BF::FNTCharacter::FNTCharacter(const unsigned char id, const Point<float> startPosition, const Point<float> size, const Point<float> offset, const unsigned char xAdvance)
{
	ID = id;
	Position = startPosition;
	Size = size;
	Offset = offset;
	XAdvance = xAdvance;
}