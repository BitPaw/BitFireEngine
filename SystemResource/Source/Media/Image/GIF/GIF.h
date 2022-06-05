#pragma once

#include "../IImageFormat.h"

namespace BF
{
	// Graphics Interchange Format
	struct GIF : public IImageFormat
	{
		public:
		unsigned short Width;
		unsigned short Height;

		unsigned char GlobalColorTableSize;
		bool IsSorted;
		unsigned char ColorResolution;
		bool IsGlobalColorTablePresent;

		unsigned char BackgroundColorIndex;
		unsigned char PixelAspectRatio;


		GIF();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}