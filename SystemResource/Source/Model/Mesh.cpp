#include "Mesh.h"

BF::Mesh::Mesh()
{
	VertexDataListSize = 0;
	VertexDataList = nullptr;

	VertexDataStructureListSize = 0;
	VertexDataStructureList[0] = 0;
	VertexDataStructureList[1] = 0;
	VertexDataStructureList[2] = 0;
	VertexDataStructureList[3] = 0;

	SegmentListSize = 0;
	SegmentList = nullptr;
}