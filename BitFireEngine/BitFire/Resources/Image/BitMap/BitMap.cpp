#include "BitMap.h"

BitMap::BitMap()
{
	Header = BitMapFileHeader();
	InformationHeaderType = BitMapInformationHeaderType::UnkownOrInvalid;
	InformationHeader = nullptr;
}

BitMap::~BitMap()
{
	if (InformationHeader != nullptr)
	{
		//delete InformationHeader;
	}
}

RGBEightBit* BitMap::GetPixel(unsigned int x, unsigned int y)
{
	unsigned int width = InformationHeader->Width;
	unsigned int height = InformationHeader->Height;
	unsigned int index;

	bool flipY = false; // flipüx
	bool flipX = false;

	if (flipX)
	{
		x = width - 1 - x;
	}

	if (flipY)
	{
		y = height - 1 - y;
	}

	index = x * width + y;

	//printf("%u | %u = %u\n", x,y, index);

	RGBEightBit* rgb = &Pixel.at(index);

	return rgb;
}