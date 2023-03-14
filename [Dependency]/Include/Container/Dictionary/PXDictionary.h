#ifndef PXDictionaryDEFINED
#define PXDictionaryDEFINED

#include <Format/Type.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXDictionary_
	{
		PXSize EntryAmountCurrent;
		PXSize EntryAmountMaximal;

		//---<Need to be predefined>------------
		PXSize KeyTypeSize; 
		PXSize ValueTypeSize;
		//--------------------------------------

		PXSize DataSize;
		void* Data;
	}
	PXDictionary;

	typedef struct PXDictionaryEntry_
	{
		void* Key;
		void* Value;
	}
	PXDictionaryEntry;

	PXPublic void PXDictionaryConstruct(PXDictionary* const dictionary, const PXSize keySize, const PXSize valueSize);
	PXPublic void PXDictionaryDestruct(PXDictionary* const dictionary);

	PXPublic void PXDictionaryResize(PXDictionary* const dictionary, const PXSize entrys);
	PXPublic void PXDictionaryAdd(PXDictionary* const dictionary, const void* key, const void* value);
	PXPublic void PXDictionaryRemove(PXDictionary* const dictionary, const void* key);
	PXPublic void PXDictionaryIndex(const PXDictionary* const dictionary, const PXSize index, PXDictionaryEntry* const pxDictionaryEntry);
	PXPublic PXBool PXDictionaryFind(PXDictionary* const dictionary, const void* const key, void* const value);

#ifdef __cplusplus
}
#endif

#endif