#pragma once

#include <vector>

#include "Chunk/Type/PortableNetworkGraphicChunkImageHeader.h"

class PortableNetworkGraphic
{
public:
	PortableNetworkGraphicChunkImageHeader ImageHeader;

	PortableNetworkGraphic();
};