#pragma once

#include <cstddef>

#include "RenderableSegment.h"

namespace BF
{
	struct RenderableChunk
	{
		public:
		unsigned int ID; // VBO

		size_t SegmentListSize;
		RenderableSegment* SegmentList;

		RenderableChunk();
	};
}