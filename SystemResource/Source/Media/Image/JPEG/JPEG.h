#pragma once

#include "JPEGFileInfo.h"
#include "JPEGScanStart.h"
#include "JPEGHuffmanTable.h"

#include "../IImageFormat.h"

namespace BF
{
	struct JPEG : public IImageFormat
	{
		public:
		JPEGFileInfo FileInfo;
		size_t HuffmanTableSize;
		JPEGHuffmanTable* HuffmanTable;
		JPEGScanStart ScanStart;

		size_t CompressedImageDataSize;
		unsigned char* CompressedImageData;

		JPEG();	
		~JPEG();

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* fileData, const size_t fileDataSize);

		FileActionResult Save(const wchar_t* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}