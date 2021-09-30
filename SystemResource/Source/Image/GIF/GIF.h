#pragma once

#include "../Image.h"
#include "../../ResourceLoadingResult.hpp"

namespace BF
{
	struct GIF
	{
		public:
		GIF();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		void ConvertTo(Image& image);
	};
}