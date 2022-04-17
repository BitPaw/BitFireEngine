#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	// Advanced Audio Coding
	struct AAC : public ISoundFormat
	{
		public:
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}