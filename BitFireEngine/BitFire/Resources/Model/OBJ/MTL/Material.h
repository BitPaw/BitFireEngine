#pragma once

#include <string>

#include "IlluminationMode.h"

#include "../../../../Mathematic/Geometry/Position.h"

namespace BF
{
	struct Material
	{
	public:
		std::string Name;

		// Ranges between 0 and 1000
		float Weight;

		Position Ambient;
		Position Diffuse;
		Position Specular;
		Position Emission;

		float Dissolved;

		// range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
		float Density;

		IlluminationMode Illumination;

		Material();
		~Material();
	};
}