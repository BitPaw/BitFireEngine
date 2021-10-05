#pragma once

#include "ImageType.h"
#include "ImageDataFormat.h"
#include "ImageFilter.h"
#include "ImageLayout.h"
#include "ImageWrap.h"
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
		unsigned int Width;
		unsigned int Height;

		ImageType Type;
		ImageDataFormat Format;
		ImageFilter Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;
		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		size_t PixelDataSize;
		unsigned char* PixelData;


		Vector4<unsigned char> GetPixel(unsigned int x, unsigned int y);

		Image();
		~Image();

		void RemoveColor(unsigned char red, unsigned char green, unsigned char blue);

		void FlipHorizontal();
		void PrintData();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();

		void FormatChange(ImageDataFormat imageFormat);

		static ImageFileFormat FileFormatPeek(const char* filePath);
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath, ImageFileFormat imageFileFormat);
	};
}