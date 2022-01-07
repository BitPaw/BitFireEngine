#pragma once

#include "../IImageFormat.h"

namespace BF
{
	struct TIFF : public IImageFormat
	{
		public:
		TIFF();

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}