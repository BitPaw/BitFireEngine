#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	// Windows Media Audio
	struct WMA : public ISoundFormat
	{
		public:
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}