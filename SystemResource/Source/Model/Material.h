#pragma once

#include <cstddef>

#define MaterialNameLength 64
#define MaterialTextureFilePathLength 260

namespace BF
{
	struct Material
	{
		public:
		wchar_t Name[MaterialNameLength];
		wchar_t TextureFilePath[MaterialTextureFilePathLength];
		float Ambient[3];
		float Diffuse[3];
		float Specular[3];
		float Emission[3];

		Material();

		size_t FullSizeInMemory();
	};
}