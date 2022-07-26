#pragma once

#include <Error/ActionResult.h>
#include <cstddef>

namespace BF
{
	struct Resource
	{
		public:
		virtual size_t FullSizeInMemory() = 0;
		//virtual ActionResult Load(const char* filePath) = 0;
		virtual ActionResult Load(const wchar_t* filePath) = 0;

		//virtual ~Resource() = 0;

		//ActionResult Load(const char* filePath);
		//tatic ActionResult Load(const wchar_t* filePath);

	};
}
