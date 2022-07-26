#pragma once

#include "Image.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct IImageFormat : public IFileFormat
	{
		virtual ActionResult ConvertTo(Image& image) = 0;
		virtual ActionResult ConvertFrom(Image& image) = 0;
		//virtual ~IImageFormat() = 0;
	};
}