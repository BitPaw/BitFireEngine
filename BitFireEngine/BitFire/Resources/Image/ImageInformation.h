#pragma once

#include "ImageFormatMode.h"
#include "ImageFilterMode.h"
#include "ImageLayout.h"
#include "ImageWrap.h"

namespace BF
{
	struct ImageInformation
	{
		public:
		ImageFormatMode Format;
		ImageFilterMode Filter;
		ImageLayout LayoutNear;
		ImageLayout LayoutFar;

		ImageWrap WrapHeight;
		ImageWrap WrapWidth;

		ImageInformation();
	};
}