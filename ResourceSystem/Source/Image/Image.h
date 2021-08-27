#pragma once

#include "ImageFormat.h"
#include "ImageFilter.h"
#include "ImageLayout.h"
#include "ImageWrap.h"
#include "ImageFileExtension.h"

#include "../Resource.h"
#include "../ResourceLoadingResult.hpp"

#include "../Container/AsciiString.h"
#include "../Math/Geometry/Vector4.hpp"
#include "ImageType.h"

namespace BF
{
	class Image : public Resource
	{
		public:
		unsigned int Width;
		unsigned int Height;

		ImageType Type;
		ImageFormat Format;
		ImageFilter Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;
		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		unsigned int PixelDataSize;
		unsigned char* PixelData;


		Vector4<unsigned char> GetPixel(unsigned int x, unsigned int y);

		Image();

		void RemoveColor(unsigned char red, unsigned char green, unsigned char blue);

		void FlipHorizontal();
		void PrintData();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();

		void FormatChange(ImageFormat imageFormat);

		static ImageFileExtension CheckFileExtension(AsciiString& fileExtension);
		ResourceLoadingResult Load(const char* filePath);
	};
}