#pragma once

#include "../Image/Image.h"

namespace BF
{
	struct Material
	{
		public:

		char Name[20];
		char TextureFilePath[50];		

		float Ambient[3];
		float Diffuse[3];
		float Specular[3];
		float Emission[3];

		Image* Texture;

		Material();
	};
}