#pragma once

#include <cstddef>

#include <Model/OBJ/OBJElement.h>

#define MeshSegmentNameLength 64

namespace BF
{
	struct MeshSegment
	{
		public:
		wchar_t Name[MeshSegmentNameLength];
		size_t IndexDataListSize;
		unsigned int* IndexDataList;

		OBJElementMaterialInfo* MaterialInfo;
		size_t MaterialInfoSize;

		MeshSegment();
		~MeshSegment();
	};
}