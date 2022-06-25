#pragma once

#include <cstddef>
#include "MTLMaterial.h"

#include <File/FileActionResult.hpp>

namespace BF
{	
	enum class MTLLineType
	{
		Invalid,

		Name,
		Texture,
		Weight,
		Ambient,
		Diffuse,
		Specular,
		Emission,
		Dissolved,
		Density,
		Illumination
	};

	// [.MTL]
	struct MTL
	{
		public:
		size_t MaterialListSize;
		MTLMaterial* MaterialList;

		MTL();
		~MTL();

		MTLLineType PeekLine(const char* data) const;

		FileActionResult Load(const char* filePath);
		FileActionResult Load(const wchar_t* filePath);
		FileActionResult Load(const unsigned char* data, const size_t dataSize);

		void PrintContent();
	};
}