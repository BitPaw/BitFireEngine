#pragma once

#include "../../../SystemResource/Source/Image/Image.h"
#include "../../../SystemResource/Source/Container/Dictionary.hpp"

namespace BF
{
	class Sprite
	{
		public:
		//Dictionary<unsigned int, Image> TextureLookup;

		Image* Texture;

		Sprite();
	};
}