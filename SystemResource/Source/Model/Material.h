#pragma once

#include "../Image/Image.h"
#include "../File/FileActionResult.hpp"

namespace BF
{
	struct Material : public Resource
	{
		public:
		float Ambient[3];
		float Diffuse[3];
		float Specular[3];
		float Emission[3];

		Image* Texture;

		Material();

		FileActionResult Load();
	};
}