#pragma once

#include "ImageType.h"
#include "ImageFilter.h"
#include "ImageLayout.h"
#include "ImageWrap.h"

#include <File/Image.h>

namespace BF
{
	struct Texture
	{
		public:
		unsigned int ID;

		ImageType Type;
		ImageFilter Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;
		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		Image DataImage;

		Texture();

		void TextureWrap(ImageWrap wrap);
		void TextureWrap(ImageWrap wrapHeight, ImageWrap wrapWidth);
	};
}