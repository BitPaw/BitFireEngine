#pragma once

#include <File/Format/BMP/BMP.h>

#include "../IImageFormat.h"

namespace BF
{
	// Image in BitMap-Format [.BMP]
	struct BMPP : public IImageFormat, public BMP
	{	
		public:
		BMPP();
		~BMPP();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertFrom(Image& image);
		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertTo(Image& image, BMP& alphaMap);
	};
}