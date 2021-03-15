#pragma once

#include "Chunk/BMPFileHeader.h"
#include "Chunk/Header/BMPInfoHeader.h"
#include "Chunk/Header/IBMPInformationHeader.h"
#include "Chunk/Header/BMPInformationHeaderType.h"


#include "../IImage.h"
#include "../../../Utility/List.hpp"
#include "../../../Color/RGB.hpp"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP : public IImage
	{
	public:
		BMPFileHeader Header;
		BMPInformationHeaderType InformationHeaderType;
		IBMPInformationHeader* InformationHeader;

		List<RGB<unsigned char>> Pixel;

		BMP();
		~BMP();

		// Raw Pixel, Image is already fliped!
		RGB<unsigned char>* GetPixel(unsigned int x, unsigned int y);
	};
}