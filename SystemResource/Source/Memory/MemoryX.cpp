#include "MemoryX.h"

void* operator new(const size_t size)
{
	void* adress = MemoryAllocate(size);

#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Allocate (new)\n", adress, size);
#endif

	return adress;
}

/*
void* operator new[](const size_t size)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif
}*/

void operator delete(void* adress)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p free (delete)\n", adress);
#endif

	if(adress)
	{
		MemoryRelease(adress, 0);
	}
}

/*
void operator delete[](void* adress)
{
#if MemoryDebug
	printf("[#][Memory] 0x%p (%10zi B) Compare to 0x%p\n", a, length, b);
#endif
}*/