#pragma once

#include "IImage.h"

namespace BF
{
	class Image : public IImage
	{
		public:
		List<unsigned char> PixelData;
	};
}