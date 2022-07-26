#pragma once

#include <Error/ActionResult.h>

namespace BF
{
	struct IFileFormat
	{
		virtual ActionResult Load(const wchar_t* filePath) = 0;
		virtual ActionResult Save(const wchar_t* filePath) = 0;
		//virtual ~IFileFormat() = 0;
	};
}