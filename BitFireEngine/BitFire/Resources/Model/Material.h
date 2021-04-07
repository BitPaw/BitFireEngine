#pragma once

#include "../../Mathematic/Geometry/Position.hpp"
#include "../../Utility/AsciiString.h"
#include "../Image/Image.h"

namespace BF
{
	struct Material
	{
		public:
		AsciiString Name;
		AsciiString TextureFilePath;
		Image* Texture;

		Position<float> Ambient;
		Position<float> Diffuse;
		Position<float> Specular;
		Position<float> Emission;

		Material();
	};
}