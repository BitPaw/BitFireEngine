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
		size_t Width;
		size_t Height;

		ImageType Type;
		ImageDataFormat Format;
		ImageFilter Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;
		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		size_t PixelDataSize;
		Byte* PixelData;

		Vector4<unsigned char> GetPixel(unsigned int x, unsigned int y);

		Image();
		~Image();

		void ImageWrapSet(ImageWrap wrap);
		void ImageWrapSet(ImageWrap wrapHeight, ImageWrap wrapWidth);

		void RemoveColor(unsigned char red, unsigned char green, unsigned char blue);

		void FlipHorizontal();
		void FlipVertical();

		void PrintData();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();

		void FormatChange(ImageDataFormat imageFormat);

		static ImageFileFormat FileFormatPeek(const wchar_t* filePath);

		FileActionResult Load();
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Save(const wchar_t* filePath, ImageFileFormat imageFileFormat);

		virtual size_t FullSizeInMemory() override;
	};
}