#pragma once

#include "../IImageFormat.h"

namespace BF
{
	struct TIFF : public IImageFormat
	{
		public:
		TIFF();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}