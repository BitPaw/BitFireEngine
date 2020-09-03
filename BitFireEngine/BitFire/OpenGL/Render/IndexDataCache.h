#pragma once

#include "DataSize.h"

class IndexDataCache
{
public:
	const unsigned int DataBlockSizeInBytes = sizeof(unsigned int);
	DataSize SizeInBytes;
	DataSize Size;
	unsigned int* Data;

	 unsigned int HighestValue;

	IndexDataCache();
	~IndexDataCache();

	void AllocateSpace(unsigned int amountOfValues);
};