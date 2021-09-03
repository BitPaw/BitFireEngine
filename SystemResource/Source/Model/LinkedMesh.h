#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../Container/List.hpp"
#include "../Math/Geometry/Vector2.hpp"
#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Vector4.hpp"

namespace BF
{
	class LinkedMesh
	{
		public:
		List<Vertex*> VertexList;
		List<Vector3<float>*> NormalPointList;
		List<Vector2<float>*> TexturePointList;
		List<MeshIndexData*> IndexList;

		List<Vector4<float>*> ColorList;
	};
}