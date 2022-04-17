#pragma once

#include "Video.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct IVideoFormat : public IFileFormat
	{
		virtual FileActionResult ConvertTo(Video& video) = 0;
		virtual FileActionResult ConvertFrom(Video& video) = 0;
	};
}