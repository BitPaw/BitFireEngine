#pragma once

#include "IlluminationMode.h"

namespace BF
{
#define MTLNameSize 50u
#define MTLFilePath 60u

	struct MTLMaterial
	{
		public:
		char Name[MTLNameSize];
		char TextureFilePath[MTLFilePath];

		// Ranges between 0 and 1000
		float Weight;

		float Ambient[3];
		float Diffuse[3];
		float Specular[3];
		float Emission[3];

		float Dissolved;

		// range from 0.001 to 10. A value of 1.0 means that light does not bend as it passes through an object.
		float Density;

		IlluminationMode Illumination;
	};
}