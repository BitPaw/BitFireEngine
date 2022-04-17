#pragma once

#include <Resource.h>

namespace BF
{
	class Video : public Resource
	{
		public:
		size_t FullSizeInMemory();
		FileActionResult Load(const wchar_t* filePath);
	};
}