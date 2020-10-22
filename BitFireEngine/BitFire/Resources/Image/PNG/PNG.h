#pragma once

#include "Chunk/Type/PNGChunkImageHeader.h"

#include "../IImage.h"

namespace BF
{
	struct PNG : public IImage
	{
	public:
		PNGChunkImageHeader ImageHeader;

		PNG();
	};
}