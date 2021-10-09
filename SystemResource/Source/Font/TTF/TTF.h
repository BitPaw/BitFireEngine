#pragma once

#include "../IFontFormat.hpp"

namespace BF
{
	struct TTF : public IFontFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Font& font);
		FileActionResult ConvertFrom(Font& font);
	};
}