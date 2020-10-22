#pragma once

#include "Vertex.h"
#include "MeshIndexData.h"

#include "../../Color/RGBA.h"

#include "../../Utility/List.hpp"

namespace BF
{
	class LinkedMesh
	{
	public:
		List<Vertex*> VertexList;
		List<Position*> NormalPointList;
		List<Point*> TexturePointList;	
		List<MeshIndexData*> IndexList;

		List<RGBA*> ColorList;
	};
}