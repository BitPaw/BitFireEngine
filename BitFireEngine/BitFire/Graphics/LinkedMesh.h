#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"
#include "../Utility/List.h"

namespace BF
{
	class LinkedMesh
	{
	public:
		List<Vertex*> VertexList;
		List<Position*> NormalPointList;
		List<Point*> TexturePointList;
		List<RGBA*> ColorList;
		List<MeshIndexData*> IndexList;
	};
}