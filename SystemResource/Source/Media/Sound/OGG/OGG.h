#pragma once

#include "../ISoundFormat.hpp"

namespace BF
{
	struct OGG : public ISoundFormat
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