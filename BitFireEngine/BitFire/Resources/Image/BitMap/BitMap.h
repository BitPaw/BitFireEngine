#pragma once

#include <vector>

#include "Chunk/BitMapFileHeader.h"
#include "Chunk/Header/BitMapInfoHeader.h"
#include "Chunk/Header/IBitMapInformationHeader.h"
#include "Chunk/Header/BitMapInformationHeaderType.h"

#include "../../../Color/RGBEightBit.h"

// Image in BitMap-Format [.BMP]
class BitMap
{
public:
	BitMapFileHeader Header;
	BitMapInformationHeaderType InformationHeaderType;
	IBitMapInformationHeader* InformationHeader;

	std::vector<RGBEightBit> Pixel;

	BitMap();
	~BitMap();
};