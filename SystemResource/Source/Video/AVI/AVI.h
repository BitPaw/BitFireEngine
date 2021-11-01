#pragma once

#include "AVIHeader.h"
#include "../IVideoFormat.hpp"

namespace BF
{
	struct AVI : public IVideoFormat
	{
		AVIHeader Header;

		public:
		FileActionResult Load(const char* filePath);
		FileActionResult Save(const char* filePath);
	};
}