#ifndef PXListDEFINED
#define PXListDEFINED

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXRingBuffer_
	{
		void* Data; // Contains the whole data.
		PXSize DataTypeSize; // Size of a single object.
		PXSize DataIndexCurrent;  // Current data index.
		PXSize SizeAllocated; // Size currently allocated and usable
	}
	PXRingBuffer;

	PXPublic void PXRingBufferConstruct(PXRingBuffer* const ringBuffer);
	PXPublic void PXRingBufferDestruct(PXRingBuffer* const ringBuffer);

	PXPublic void PXRingBufferInitialize(PXRingBuffer* const ringBuffer, void* const data, const PXSize dataTypeSize, const PXSize sizeAllocated);

	PXPublic void PXRingBufferAdd(PXRingBuffer* const ringBuffer, void* const dataElement);

#ifdef __cplusplus
}
#endif

#endif