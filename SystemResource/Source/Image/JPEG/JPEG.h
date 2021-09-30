#pragma once

#include "../Image.h"
#include "../../ResourceLoadingResult.hpp"

namespace BF
{
	struct JPEG
	{
		public:
		JPEG();

		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
		void ConvertTo(Image& image);
	};
}