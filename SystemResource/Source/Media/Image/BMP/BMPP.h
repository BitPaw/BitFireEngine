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

		ActionResult Load(const char* filePath);
		ActionResult Load(const wchar_t* filePath);
		ActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		ActionResult Save(const wchar_t* filePath);

		ActionResult ConvertFrom(Image& image);
		ActionResult ConvertTo(Image& image);
		ActionResult ConvertTo(Image& image, BMP& alphaMap);
	};
}