#pragma once

#include <File/Image.h>

#define TextureCubeImageListSize 6

namespace BF
{
	struct TextureCube
	{
		public:
		unsigned int ID;
		Image ImageList[TextureCubeImageListSize];

		TextureCube();

		bool HasTextures();
	};
}