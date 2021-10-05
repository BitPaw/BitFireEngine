#pragma once

#include "../IImageFormat.h"

namespace BF
{
	struct GIF : public IImageFormat
	{
		public:
		GIF();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);

		ResourceLoadingResult ConvertTo(Image& image);
		ResourceLoadingResult ConvertFrom(Image& image);
	};
}