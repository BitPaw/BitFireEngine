#pragma once

#include "ImageType.h"

namespace BF
{
	struct RenderableSegment
	{
		public:
		unsigned int ID; // IBO
		unsigned int Size;

		ImageType TextureType;

		unsigned int ShaderID;
		unsigned int TextureID;

		RenderableSegment();
	};
}