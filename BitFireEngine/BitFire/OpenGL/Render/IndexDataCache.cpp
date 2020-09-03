#include "IndexDataCache.h"

IndexDataCache::IndexDataCache()
{
	Data = nullptr;
}

IndexDataCache::~IndexDataCache()
{
	if (Data != nullptr)
	{
		delete[] Data;
	}
}

void IndexDataCache::AllocateSpace(unsigned int amountOfValues)
{
	Data = new unsigned int[amountOfValues];
	Size.Maximal = amountOfValues;
	SizeInBytes.Maximal = amountOfValues * DataBlockSizeInBytes;
}