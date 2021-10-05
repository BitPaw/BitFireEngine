#pragma once

#include "../IImageFormat.h"

namespace BF
{
	struct TIFF : public IImageFormat
	{
		public:
		TIFF();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);

		ResourceLoadingResult ConvertTo(Image& image);
		ResourceLoadingResult ConvertFrom(Image& image);
	};
}