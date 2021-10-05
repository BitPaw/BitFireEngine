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

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);

		ResourceLoadingResult ConvertFrom(Image& image);
		ResourceLoadingResult ConvertTo(Image& image);
	};
}