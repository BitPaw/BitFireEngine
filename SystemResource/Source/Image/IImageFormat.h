#pragma once

#include "Image.h"
#include "../ResourceLoadingResult.hpp"

namespace BF
{
	struct IImageFormat
	{
		virtual ResourceLoadingResult Load(const char* filePath) = 0;
		virtual ResourceLoadingResult Save(const char* filePath) = 0;

		virtual ResourceLoadingResult ConvertTo(Image& image) = 0;
		virtual ResourceLoadingResult ConvertFrom(Image& image) = 0;
	};
}