#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	// Advanced Audio Coding
	struct AAC : public ISoundFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}