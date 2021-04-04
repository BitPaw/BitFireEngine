#pragma once

#include "MTLMaterial.h"

#include "../../../../Utility/List.hpp"

namespace BF
{	
	// [.MTL]
	class MTL
	{
		public:
		List<MTLMaterial> MaterialList;

		void Load(AsciiString& filePath);

		void PrintContent();
	};
}