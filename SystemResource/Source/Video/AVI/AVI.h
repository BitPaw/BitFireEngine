#pragma once

#include "../../ResourceLoadingResult.hpp"
#include "AVIHeader.h"

namespace BF
{
	struct AVI
	{
		AVIHeader Header;

		public:
		ResourceLoadingResult Load(const char* filePath);
		ResourceLoadingResult Save(const char* filePath);
	};
}