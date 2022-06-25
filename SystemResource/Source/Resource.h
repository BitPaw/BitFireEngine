#pragma once

#include "File/FileActionResult.hpp"

#include <cstddef>

namespace BF
{
	struct Resource
	{
		public:
		virtual size_t FullSizeInMemory() = 0;
		//virtual FileActionResult Load(const char* filePath) = 0;
		virtual FileActionResult Load(const wchar_t* filePath) = 0;

		//virtual ~Resource() = 0;

		//FileActionResult Load(const char* filePath);
		//tatic FileActionResult Load(const wchar_t* filePath);

	};
}
