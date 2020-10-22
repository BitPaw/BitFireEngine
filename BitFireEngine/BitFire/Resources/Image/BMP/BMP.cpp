#include "BMP.h"

BF::BMP::BMP()
{
	Header = BMPFileHeader();
	InformationHeaderType = BMPInformationHeaderType::UnkownOrInvalid;
	InformationHeader = nullptr;
}

BF::BMP::~BMP()
{
	if (InformationHeader != nullptr)
	{
		//delete InformationHeader;
	}
}

BF::RGB8Bit* BF::BMP::GetPixel(unsigned int x, unsigned int y)
{
	int width = InformationHeader->Width;
	int height = InformationHeader->Height;
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

	// printf("%u | %u = %u\n", x,y, index);

	RGB8Bit* rgb = &Pixel[index];

	return rgb;
}