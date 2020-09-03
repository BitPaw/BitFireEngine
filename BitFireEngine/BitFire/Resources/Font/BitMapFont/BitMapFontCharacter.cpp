#include "BitMapFontCharacter.h"

BitMapFontCharacter::BitMapFontCharacter() : BitMapFontCharacter(-1, Point(), Point(), Point(), -1)
{

}

BitMapFontCharacter::BitMapFontCharacter(const unsigned char id, const Point startPosition, const Point size, const Point offset, const unsigned char xAdvance)
{
	ID = id;
	StartPosition = startPosition;
	Size = size;
	Offset = offset;
	XAdvance = xAdvance;
}