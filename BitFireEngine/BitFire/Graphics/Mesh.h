#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Vertex.h"

#include "../Utility/List.h"
#include "MeshIndexData.h"

namespace BF
{
	class Mesh
	{
	public:
		std::string Name;

		int ObjectBufferIndex;

		List<Vertex> VertexList;
		List<Position> NormalPointList;
		List<Point> TexturePointList;
		List<RGBA> ColorList;
		List<MeshIndexData> IndexList;

		Mesh();

		bool HasNormalVectors() { return NormalPointList.Size.Value > 0; }
		bool HasTexturePoints() { return TexturePointList.Size.Value > 0; }
		bool HasColorPoints() { return ColorList.Size.Value > 0; }
	};
}