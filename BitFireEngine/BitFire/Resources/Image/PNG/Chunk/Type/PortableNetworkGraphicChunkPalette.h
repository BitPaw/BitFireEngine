#pragma once

#include <vector>
#include "../../../../../Color/RGB8Bit.h"

namespace BF
{
	class PortableNetworkGraphicChunkPalette
	{
	public:
		// Contains from 1 to 256 palette entries
		std::vector<RGB8Bit> Entries;
	};
}