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
		FileActionResult Save(const char* filePath);

		FileActionResult ConvertTo(Image& image);
		FileActionResult ConvertFrom(Image& image);
	};
}