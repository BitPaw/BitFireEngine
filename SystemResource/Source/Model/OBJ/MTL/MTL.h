#pragma once

#include <cstddef>
#include "MTLMaterial.h"

#include "../../../File/FileActionResult.hpp"

namespace BF
{	
	// [.MTL]
	class MTL
	{
		public:
		size_t MaterialListSize;
		MTLMaterial* MaterialList;

		MTL();
		~MTL();

		FileActionResult Load(const wchar_t* filePath);

		void PrintContent();
	};
}