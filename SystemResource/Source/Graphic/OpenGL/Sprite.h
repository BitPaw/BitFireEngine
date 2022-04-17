#pragma once

#include <Media/Image/Image.h>

#include "Texture.h"
#include "Renderable.h"

namespace BF
{
	class Sprite : public Renderable
	{
		public:
		Texture* UsedTexture;

		Sprite();
	};
}