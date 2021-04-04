#pragma once

#include "IlluminationMode.h"

#include "../../../../Mathematic/Geometry/Position.hpp"
#include "../../../../Utility/AsciiString.h"

namespace BF
{
	struct MTLMaterial
	{
		public:
		AsciiString Name;
		AsciiString TextureFilePath;

		// Ranges between 0 and 1000
		float Weight;

		Position<float> Ambient;
		Position<float> Diffuse;
		Position<float> Specular;
		Position<float> Emission;

		float Dissolved;

		// range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
		float Density;

		IlluminationMode Illumination;

		MTLMaterial();
	};
}