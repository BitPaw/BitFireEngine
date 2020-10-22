#include "FNTCharacter.h"

BF::FNTCharacter::FNTCharacter() : FNTCharacter(-1, Point(), Point(), Point(), -1)
{

}

BF::FNTCharacter::FNTCharacter(const unsigned char id, const Point startPosition, const Point size, const Point offset, const unsigned char xAdvance)
{
	ID = id;
	StartPosition = startPosition;
	Size = size;
	Offset = offset;
	XAdvance = xAdvance;
}