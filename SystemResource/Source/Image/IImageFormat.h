#pragma once

#include "Image.h"
#include "../IFileFormat.hpp"

namespace BF
{
	struct IImageFormat : public IFileFormat
	{
		virtual FileActionResult ConvertTo(Image& image) = 0;
		virtual FileActionResult ConvertFrom(Image& image) = 0;
	};
}