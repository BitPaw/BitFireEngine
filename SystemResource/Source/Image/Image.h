#pragma once

#include "ImageDataFormat.h"
#include "ImageFileFormat.h"

#include "../Resource.h"
#include "../File/FileActionResult.hpp"

#include "../Container/AsciiString.h"
#include "../Math/Geometry/Vector4.hpp"

namespace BF
{
	class Image : public Resource
	{
		public:
		size_t Width;
		size_t Height;		

		ImageDataFormat Format;

		size_t PixelDataSize;
		unsigned char* PixelData;

		Vector4<unsigned char> GetPixel(unsigned int x, unsigned int y);

		Image();
		~Image();

		void RemoveColor(unsigned char red, unsigned char green, unsigned char blue);

		void FlipHorizontal();
		void FlipVertical();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();

		void FormatChange(ImageDataFormat imageFormat);

		static ImageFileFormat FileFormatPeek(const wchar_t* filePath);

		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath, ImageFileFormat imageFileFormat);

		virtual size_t FullSizeInMemory() override;
	};
}