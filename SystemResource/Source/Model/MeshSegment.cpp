#include "MeshSegment.h"

#include <cstdlib>

BF::MeshSegment::MeshSegment()
{
	Name[0] = '\0';
	IndexDataListSize = 0;
	IndexDataList = nullptr;
}

BF::MeshSegment::~MeshSegment()
{
	free(IndexDataList);
}