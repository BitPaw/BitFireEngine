#pragma once

#include "DataSize.h"

class VertexDataCache
{
public:
	const unsigned int DataBlockSizeInBytes = sizeof(float) * (4 + 4 + 4 + 2);
	DataSize SizeInBytes;
	DataSize Size;
	float* Data;

	VertexDataCache();
	~VertexDataCache();

	void AllocateSpace(unsigned int amountOfValues);
	void CalculateByteSize();
};