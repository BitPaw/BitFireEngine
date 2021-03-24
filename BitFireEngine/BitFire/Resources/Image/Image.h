#pragma once

#include "IImage.h"

#include "ImageInformation.h"

#include "../../Color/RGBA.hpp"
#include "../Resource.h"

namespace BF
{
	class Image : public Resource, public IImage
	{
		public:
		ImageInformation Information;

		List<unsigned char> PixelData;
		RGBA<unsigned char> GetPixel(unsigned int x, unsigned int y);

		void FlipHorizontal();
		void PrintData();

		void Resize(unsigned int width, unsigned height);

		void FillRandome();
	};
}