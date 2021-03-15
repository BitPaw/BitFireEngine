#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../../Utility/List.hpp"
#include "../../Color/RGBA.hpp"

namespace BF
{
	class LinkedMesh
	{
		public:
		List<Vertex*> VertexList;
		List<Position<float>*> NormalPointList;
		List<Point<float>*> TexturePointList;
		List<MeshIndexData*> IndexList;

		List<RGBA<float>*> ColorList;
	};
}