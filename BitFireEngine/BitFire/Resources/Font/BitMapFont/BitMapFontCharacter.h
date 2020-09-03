#pragma once

#include "../../../Mathematic/Geometry/Point.h"
#include "../../../IO/File/TextFile.h"
#include "../../../IO/File/FileLoader.h"

class BitMapFontCharacter
{
public:
	unsigned char ID;

	Point StartPosition;
	Point Size;
	Point Offset;

	unsigned char XAdvance;

	unsigned int Page;
	unsigned int Chanal;

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