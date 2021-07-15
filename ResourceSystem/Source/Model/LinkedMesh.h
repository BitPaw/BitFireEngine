#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../Container/List.hpp"
#include "../Math/Geometry/Vector4.hpp"

namespace BF
{
	class LinkedMesh
	{
		public:
		List<Vertex*> VertexList;
		List<Position<float>*> NormalPointList;
		List<Point<float>*> TexturePointList;
		List<MeshIndexData*> IndexList;

		List<Vector4<float>*> ColorList;
	};
}