#pragma once

#include "../ISoundFormat.hpp"

#include <cstddef>

#define MP3Debug 1

namespace BF
{
	// MPEG audio file 
	struct MP3 : public ISoundFormat
	{


		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);
		FileActionResult ConvertTo(Sound& sound);
		FileActionResult ConvertFrom(Sound& sound);
	};
}