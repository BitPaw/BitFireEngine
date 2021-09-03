#pragma once

#include "Vertex.h"
#include "Material.h"
#include "MeshIndexData.h"

#include "../Math/Geometry/Vector2.hpp"
#include "../Math/Geometry/Vector3.hpp"

namespace BF
{
	class Mesh
	{
		public:
		char Name[30];

		int ObjectBufferIndex;
		Material* MeshMaterial;

		List<Vertex> VertexList;
		List<Vector3<float>> NormalPointList;
		List<Vector2<float>> TexturePointList;
		//List<RGBA> ColorList;
		List<MeshIndexData> IndexList;

		Mesh();

		bool HasNormalVectors() { return NormalPointList.Size() > 0; }
		bool HasTexturePoints() { return TexturePointList.Size() > 0; }
		//bool HasColorPoints() { return ColorList.Size.Value > 0; }
	};
}