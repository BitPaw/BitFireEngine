#pragma once

#include "Font.h"
#include "FontFormat.h"

#include "../ErrorCode.h"

namespace BF
{
	class FontLoader
	{
		public:
		static ErrorCode LoadFontFromFile(AsciiString& filePath, Font& font);

		static FontFormat ParseFontFormat(AsciiString& fileExtension);
		static bool IsFontFile(AsciiString& fileExtension);
	};
}