#include "MeshSegment.h"

#include <Hardware/Memory/Memory.h>

BF::MeshSegment::MeshSegment()
{
	Name[0] = '\0';
	IndexDataListSize = 0;
	IndexDataList = nullptr;

	 MaterialInfo = nullptr;
	MaterialInfoSize = 0;
}

BF::MeshSegment::~MeshSegment()
{
	Memory::Release(IndexDataList, IndexDataListSize);
}