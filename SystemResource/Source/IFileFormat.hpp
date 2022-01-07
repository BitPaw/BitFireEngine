#pragma once

#include "File/FileActionResult.hpp"

namespace BF
{
	struct IFileFormat
	{
		virtual FileActionResult Load(const wchar_t* filePath) = 0;
		virtual FileActionResult Save(const wchar_t* filePath) = 0;
	};
}