#pragma once

#include <File/Format/PNG/PNG.h>
#include <File/FileActionResult.hpp>
#include <Media/Image/Image.h>

namespace BF
{
	class PNGX : public PNG
	{
		public:
		PNGX();
		~PNGX();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertFrom(Image& image);
		FileActionResult ConvertTo(Image& image);
	};
}