#pragma once

#include "Sound.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct ISoundFormat : public IFileFormat
	{
		virtual ActionResult ConvertTo(Sound& sound) = 0;
		virtual ActionResult ConvertFrom(Sound& sound) = 0;
	};
}