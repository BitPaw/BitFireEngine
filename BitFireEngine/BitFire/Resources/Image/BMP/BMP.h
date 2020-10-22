#pragma once

#include "Chunk/BMPFileHeader.h"
#include "Chunk/Header/BMPInfoHeader.h"
#include "Chunk/Header/IBMPInformationHeader.h"
#include "Chunk/Header/BMPInformationHeaderType.h"


#include "../IImage.h"
#include "../../../Color/RGB8Bit.h"
#include "../../../Utility/List.hpp"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP : public IImage
	{
	public:
		BMPFileHeader Header;
		BMPInformationHeaderType InformationHeaderType;
		IBMPInformationHeader* InformationHeader;

		List<RGB8Bit> Pixel;

		BMP();
		~BMP();

		// Raw Pixel, Image is already fliped!
		RGB8Bit* GetPixel(unsigned int x, unsigned int y);
	};
}