#pragma once

#include "../../../Mathmatic/Geometry/Point.h"

class BitMapFontCharacter
{
public:
	unsigned char ID;

	Point StartPosition;
	Point Size;
	Point Offset;

	unsigned char XAdvance;


	BitMapFontCharacter();
	BitMapFontCharacter
	(
		const unsigned char id,	
		const Point startPosition,
		const Point size,
		const Point offset,
		const unsigned char xAdvance
	);
};