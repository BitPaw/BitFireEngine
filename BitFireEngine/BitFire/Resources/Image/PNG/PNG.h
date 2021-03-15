#pragma once

#include "../IImage.h"
#include "Chunk/PNGChunk.h"
#include "Chunk/PNGHeader.h"

namespace BF
{
	struct PNG : public IImage
	{
		public:
		PNGHeader Header;

		List<PNGChunk> ChunkList;

		void PrintData();
	};
}