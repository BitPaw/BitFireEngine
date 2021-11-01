#pragma once

#include "BMPType.h"
#include "BMPInfoHeader.h"
#include "BMPInfoHeaderType.h"

#include "../IImageFormat.h"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP : public IImageFormat
	{	
		public:
		BMPType Type;

		BMPInfoHeaderType InfoHeaderType;
		BMPInfoHeader InfoHeader;

		size_t PixelDataSize;
		unsigned char* PixelData;

		BMP();
		~BMP();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertFrom(Image& image);
		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertTo(Image& image, BMP& alphaMap);
	};
}