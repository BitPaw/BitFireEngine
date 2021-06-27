#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../Container/List.hpp"
#include "../Types/RGBA.hpp"

#include "../../../MathSystem/Source/Geometry/Position.hpp"

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