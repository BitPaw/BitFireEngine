#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	// Free Lossless Audio Codec
	struct FLAC : public ISoundFormat
	{
		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}