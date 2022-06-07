#pragma once

#include "../IFontFormat.hpp"

namespace BF
{
	struct OTF : public IFontFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
	};
}