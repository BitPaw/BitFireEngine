#include "QueueMapping.h"

#include <Hardware/Memory/Memory.h>

BF::QueueMapping::QueueMapping()
{
	_offsetBytesUsed = 0;
	_elementConter = 0;
}

void BF::QueueMapping::Allocate(const size_t sizeInBytes)
{
	MapToVirtualMemory(sizeInBytes);
}

bool BF::QueueMapping::Enqueue(const void* source, const size_t sizeInBytes)
{
	Write(source, sizeInBytes);

	++_elementConter;

	return true;
}

bool BF::QueueMapping::Dequeue(void* target, size_t sizeInBytes)
{
	{
		const bool hasElements = _elementConter > 0;

		if(!hasElements)
		{
			return false;
		}
	}

	const Byte* adressStart = Data + _offsetBytesUsed;

	Memory::Copy(target, adressStart, sizeInBytes);

	_offsetBytesUsed += sizeInBytes;

	--_elementConter;

	return true;
}