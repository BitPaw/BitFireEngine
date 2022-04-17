#pragma once

#include "Font.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct IFontFormat : public IFileFormat
	{
		virtual FileActionResult ConvertTo(Font& font) = 0;
		virtual FileActionResult ConvertFrom(Font& font) = 0;
	};
}