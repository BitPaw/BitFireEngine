#pragma once

#include <vector>
#include "../../../../../Color/RGBEightBit.h"

class PortableNetworkGraphicChunkPalette
{
public:
	// Contains from 1 to 256 palette entries
	std::vector<RGBEightBit> Entries;
};