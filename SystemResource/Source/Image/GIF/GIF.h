#pragma once

#include "../IImageFormat.h"

namespace BF
{
	struct GIF : public IImageFormat
	{
		public:
		GIF();

		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}