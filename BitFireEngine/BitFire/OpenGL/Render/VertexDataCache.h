#pragma once

#include "DataSize.h"

namespace BF
{
	class VertexDataCache
	{
		public:
		const unsigned int DataBlockSizeInBytes = sizeof(float) * (3 + 3 + 4 + 2);
		DataSize SizeInBytes;
		DataSize Size;
		float* Data;

		VertexDataCache();
		~VertexDataCache();

		void AllocateSpace(unsigned int amountOfValues);
		void CalculateByteSize();
	};
}