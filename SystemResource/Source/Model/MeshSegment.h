#pragma once

#include <cstddef>

#define MeshSegmentNameLength 64

namespace BF
{
	struct MeshSegment
	{
		public:
		wchar_t Name[MeshSegmentNameLength];
		size_t IndexDataListSize;
		unsigned int* IndexDataList;

		MeshSegment();
		~MeshSegment();
	};
}