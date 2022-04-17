#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	// MPEG audio layer 3 file 
	struct MP3 : public ISoundFormat
	{
		public:
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}