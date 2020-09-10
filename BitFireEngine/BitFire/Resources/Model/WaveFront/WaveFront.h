#pragma once

#include <string>

#include "WaveFrontElement.h"
#include "MaterialLibrary/MaterialLibrary.h"

/// <summary>
/// [.OBJ] Wavefront - 3D model format
/// </summary>

namespace BF
{
	struct WaveFront
	{
	public:
		std::string Name = "[N/A]";
		MaterialLibrary Materials;
		List<WaveFrontElement> ElementList;

		Position* GetVertexPositionFromGlobalID(unsigned int globalIndex);
		Point* GetVertexTextureCoordinatesFromGlobalID(unsigned int globalIndex);
		Position* GetVertexNormalFromGlobalID(unsigned int globalIndex);
	};
}