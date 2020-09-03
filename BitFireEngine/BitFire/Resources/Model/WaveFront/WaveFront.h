#pragma once

#include "WaveFrontElement.h"
#include "MaterialLibrary/MaterialLibrary.h"

/// <summary>
/// [.OBJ] Wavefront - 3D model format
/// </summary>
class WaveFront
{
public:
	char* Name;

	MaterialLibrary Materials;

	WaveFrontElement* ElementList;
	unsigned int ElementListSize;

	Position* GetVertexPositionFromGlobalID(unsigned int globalIndex);
	Point* GetVertexTextureCoordinatesFromGlobalID(unsigned int globalIndex);
	Position* GetVertexNormalFromGlobalID(unsigned int globalIndex);
};