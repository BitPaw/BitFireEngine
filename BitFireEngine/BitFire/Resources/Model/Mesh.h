#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../../Utility/List.hpp"
#include "../../Utility/ASCIIString.h"

namespace BF
{
	class Mesh
	{
		public:
		ASCIIString Name;

		int ObjectBufferIndex;

		List<Vertex> VertexList;
		List<Position<float>> NormalPointList;
		List<Point<float>> TexturePointList;
		//List<RGBA> ColorList;
		List<MeshIndexData> IndexList;

		Mesh();

		bool HasNormalVectors() { return NormalPointList.Size() > 0; }
		bool HasTexturePoints() { return TexturePointList.Size() > 0; }
		//bool HasColorPoints() { return ColorList.Size.Value > 0; }
	};
}