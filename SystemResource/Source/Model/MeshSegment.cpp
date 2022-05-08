#include "MeshSegment.h"

#include <Hardware/Memory/Memory.h>

BF::MeshSegment::MeshSegment()
{
	Name[0] = '\0';
	IndexDataListSize = 0;
	IndexDataList = nullptr;
}

BF::MeshSegment::~MeshSegment()
{
	Memory::Release(IndexDataList, IndexDataListSize);
}