#ifndef PXListDEFINED
#define PXListDEFINED

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXList_
	{
		void* Data; // Contains the whole data.
		PXSize DataTypeSize; // Size of a single object.
		PXSize SizeUsed;  // Size currently used by data.
		PXSize SizeAllocated; // Size currently allocated and usable
	}
	PXList;

	PXPublic void PXListConstruct(PXList* const list);
	PXPublic void PXListDestruct(PXList* const list);

	PXPublic void PXListInitialize(PXList* const list, void* const data, const PXSize dataTypeSize, const PXSize sizeAllocated);

	PXPublic PXBool PXListAdd(PXList* const list, void* const dataElement);

#ifdef __cplusplus
}
#endif

#endif