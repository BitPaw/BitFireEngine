#pragma once

#include "Material.h"

#include "../../../../Utility/List.hpp"

namespace BF
{	
	// [.MTL]
	class MTL
	{
		public:
		List<Material> MaterialList;

		void Load(AsciiString& filePath);
	};
}