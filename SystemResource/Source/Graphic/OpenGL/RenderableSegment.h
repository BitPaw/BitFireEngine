#pragma once

#include "ImageType.h"

#include <cstddef>

namespace BF
{
	struct SegmentMaterialRange
	{
		unsigned int ShaderID;
		unsigned int TextureID;
		size_t Size;
		
		SegmentMaterialRange()
		{
			ShaderID = -1;
			TextureID = -1;
			Size = -1;
		}
	};

	struct RenderableSegment
	{
		public:
		unsigned int ID; // IBO
		unsigned int Size;

		ImageType TextureType;

		size_t MaterialRangeSize;
		SegmentMaterialRange* MaterialRange;

		RenderableSegment();
	};
}