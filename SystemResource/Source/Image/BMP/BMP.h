#pragma once

#include "BMPType.h"
#include "BMPInfoHeader.h"
#include "BMPInfoHeaderType.h"

#include "../Image.h"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMP
	{	
		public:
		BMPType Type;

		BMPInfoHeaderType InfoHeaderType;
		BMPInfoHeader InfoHeader;

		unsigned int PixelDataSize;
		unsigned char* PixelData;

		BMP();
		~BMP();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		ResourceLoadingResult ConvertFrom(Image& image);
		ResourceLoadingResult ConvertTo(Image& image);
	};
}