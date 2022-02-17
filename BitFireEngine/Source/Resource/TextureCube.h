#pragma once

#include <Image/Image.h>

namespace BF
{
	struct TextureCube
	{
		public:
		unsigned int ID;
		Image ImageList[6];

		TextureCube();
	};
}