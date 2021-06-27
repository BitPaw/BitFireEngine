#pragma once

#include "MTLMaterial.h"

#include "../../../Container/List.hpp"

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