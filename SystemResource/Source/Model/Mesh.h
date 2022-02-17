#pragma once

#include "MeshSegment.h"

namespace BF
{
	struct Mesh
	{
		public:
		size_t VertexDataListSize;
		float* VertexDataList;

		size_t VertexDataStructureListSize;
		unsigned int VertexDataStructureList[4];

		size_t SegmentListSize;
		MeshSegment* SegmentList;

		Mesh();
	};
}