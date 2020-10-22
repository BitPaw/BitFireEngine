#include "VertexDataCache.h"

BF::VertexDataCache::VertexDataCache()
{
	Data = nullptr;
}

BF::VertexDataCache::~VertexDataCache()
{
	if (Data != nullptr)
	{
		delete[] Data;
	}
}

void BF::VertexDataCache::AllocateSpace(unsigned int amountOfValues)
{
	Data = new float[amountOfValues];
	Size.Maximal = amountOfValues;
	SizeInBytes.Maximal = amountOfValues * DataBlockSizeInBytes;
}

void BF::VertexDataCache::CalculateByteSize()
{
	SizeInBytes.Current = DataBlockSizeInBytes * Size.Current;
}
