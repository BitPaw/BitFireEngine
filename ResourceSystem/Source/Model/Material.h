#pragma once

#include "../Image/Image.h"

#include "../../../MathSystem/Source/Geometry/Position.hpp"

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