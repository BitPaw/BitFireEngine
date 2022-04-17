#pragma once

#include "Sound.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct ISoundFormat : public IFileFormat
	{
		virtual FileActionResult ConvertTo(Sound& sound) = 0;
		virtual FileActionResult ConvertFrom(Sound& sound) = 0;
	};
}