#pragma once

#include "JPEGFileInfo.h"
#include "../IImageFormat.h"

namespace BF
{
	struct JPEG : public IImageFormat
	{
		public:
		JPEGFileInfo FileInfo;
		size_t CompressedDataLength;
		unsigned char* CompressedData;

		JPEG();	

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);

		ResourceLoadingResult ConvertTo(Image& image);
		ResourceLoadingResult ConvertFrom(Image& image);
	};
}