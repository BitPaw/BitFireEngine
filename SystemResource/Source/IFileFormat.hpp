#pragma once

#include "File/FileActionResult.hpp"

namespace BF
{
	struct IFileFormat
	{
		virtual FileActionResult Load(const char* filePath) = 0;
		virtual FileActionResult Save(const char* filePath) = 0;
	};
}