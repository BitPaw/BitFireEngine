#include "VertexDataCache.h"

VertexDataCache::VertexDataCache()
{
	Data = nullptr;
}

VertexDataCache::~VertexDataCache()
{
	if (Data != nullptr)
	{
		delete[] Data;
	}
}

void VertexDataCache::AllocateSpace(unsigned int amountOfValues)
{
	Data = new float[amountOfValues];
	Size.Maximal = amountOfValues;
	SizeInBytes.Maximal = amountOfValues * DataBlockSizeInBytes;
}

void VertexDataCache::CalculateByteSize()
{
	SizeInBytes.Current = DataBlockSizeInBytes * Size.Current;
}
