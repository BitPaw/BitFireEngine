#include "IndexDataCache.h"

BF::IndexDataCache::IndexDataCache()
{
	Data = nullptr;
}

BF::IndexDataCache::~IndexDataCache()
{
	if (Data != nullptr)
	{
		delete[] Data;
	}
}

void BF::IndexDataCache::AllocateSpace(unsigned int amountOfValues)
{
	Data = new unsigned int[amountOfValues];
	Size.Maximal = amountOfValues;
	SizeInBytes.Maximal = amountOfValues * DataBlockSizeInBytes;
}