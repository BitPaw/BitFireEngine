#ifndef PXLinkedListDEFINED
#define PXLinkedListDEFINED

#include <Format/Type.h>

#define PXLinkedListNodeNotUsed (PXSize)-1
#define PXLinkedListNodeNoNext (PXSize)0

#define PXLinkedListUseAdress (PXSize)-1

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXLinkedListNodeFixed_ PXLinkedListNodeFixed;

	typedef struct PXLinkedListNodeFixed_
	{
		void* BlockData;
		PXLinkedListNodeFixed* NodeNext; // 0=No Next 0xFFF=InvalidData
	}
	PXLinkedListNodeFixed;

	typedef struct PXLinkedListNodeDynamic_
	{
		void* BlockData;
		PXSize BlockSize;
	}
	PXLinkedListNodeDynamic;

	typedef struct PXLinkedListFixed_
	{
		void* Data;
		PXSize DataSize;

		PXSize NodeSize; // if size is -1, we will store the data pointer itself
		PXSize NodeListSizeCurrent;
		PXSize NodeListSizeMaximal;


		void* DataEntryLast;
	}
	PXLinkedListFixed;

	PXPublic void PXLinkedListFixedNodeConstruct(PXLinkedListFixed* const linkedListFixed);
	PXPublic void PXLinkedListFixedNodeDestruct(PXLinkedListFixed* const linkedListFixed);
	

	PXPublic void PXLinkedListFixedNodeSet(PXLinkedListFixed* const linkedListFixed, void* const data, const PXSize dataSize, const PXSize nodeSize);

	PXPublic PXBool PXLinkedListFixedNodeAt(PXLinkedListFixed* const linkedListFixed, PXLinkedListNodeFixed* const pxLinkedListNodeFixed, const PXSize index);
	PXPublic PXBool PXLinkedListFixedNodeNext(PXLinkedListFixed* const linkedListFixed, PXLinkedListNodeFixed* const pxLinkedListNodeFixed);

	//PXPublic PXBool PXLinkedListFixedNodeFetch(PXLinkedListFixed* const linkedListFixed, void* const element);

	PXPrivate PXBool PXLinkedListFixedDataSize(const PXLinkedListFixed* const linkedListFixed);
	PXPrivate PXBool PXLinkedListFixedIsDataEmbedded(const PXLinkedListFixed* const linkedListFixed);
	PXPrivate PXSize PXLinkedListFixedNodeStride(const PXLinkedListFixed* const linkedListFixed);
	PXPrivate void* PXLinkedListFixedNodeEmptySlotFetch(const PXLinkedListFixed* const linkedListFixed);

	PXPublic PXBool PXLinkedListFixedNodeAdd(PXLinkedListFixed* const linkedListFixed, void* const element);
	PXPublic PXBool PXLinkedListFixedNodeRemoveAt(PXLinkedListFixed* const linkedListFixed, const PXSize index);
#ifdef __cplusplus
}
#endif

#endif
