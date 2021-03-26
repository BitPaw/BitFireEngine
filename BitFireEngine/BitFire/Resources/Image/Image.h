#pragma once

#include "ImageFormat.h"
#include "ImageFilter.h"
#include "ImageLayout.h"
#include "ImageWrap.h"

#include "../../Color/RGBA.hpp"
#include "../Resource.h"

namespace BF
{
	class Image : public Resource
	{
		public:
		unsigned int Width;
		unsigned int Height;

		ImageFormat Format;
		ImageFilter Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;
		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		List<unsigned char> PixelData;
		RGBA<unsigned char> GetPixel(unsigned int x, unsigned int y);

		Image();

		void FlipHorizontal();
		void PrintData();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();
	};
}