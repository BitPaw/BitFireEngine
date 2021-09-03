#include "FNTCharacter.h"

BF::FNTCharacter::FNTCharacter()
{
	ID = -1;
	Position[0] = -1;
	Position[1] = -1;
	Size[0] = -1;
	Size[1] = -1;
	Offset[0] = -1;
	Offset[1] = -1;
	XAdvance = -1;
	Page = -1; 
	Chanal = -1;
}

BF::FNTCharacter::FNTCharacter(const unsigned char id, const float startPosition[2], const float size[2], const float offset[2], const unsigned char xAdvance)
{
	ID = id;
	Position[0] = startPosition[0];
	Position[1] = startPosition[1];
	Size[0] = size[0];
	Size[1] = size[1];
	Offset[0] = offset[0];
	Offset[1] = offset[1];
	XAdvance = xAdvance;
	Page = -1;
	Chanal = -1;
}