#pragma once

#include "Font.h"
#include <IFileFormat.hpp>

namespace BF
{
	struct IFontFormat : public IFileFormat
	{
		virtual ActionResult ConvertTo(Font& font) = 0;
		virtual ActionResult ConvertFrom(Font& font) = 0;
	};
}