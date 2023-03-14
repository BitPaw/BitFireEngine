#ifndef SBPPackageHeaderChunkINCLUDE
#define SBPPackageHeaderChunkINCLUDE

#include <Format/Type.h>
#include <File/PXDataStream.h>
#include <Container/Dictionary/PXDictionary.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum SBPPackageHeaderChunkResult_
	{
		SBPPackageHeaderChunkResultInvalid,

		// If a chunk header is expected and does not follow the format.
		SBPPackageHeaderChunkIllegal,

		// Data is not fully complete and is stored until the additional data has been serverd
		SBPPackageHeaderChunkCached,

		// Data is now complete and ready to be consumed
		SBPPackageHeaderChunkComplete,

		// Data has not been cached. It can be handled fully at once.
		SBPPackageHeaderChunkComsumeImmediately,
	}
	SBPPackageHeaderChunkResult;

	typedef enum SBPPackageHeaderCacheState_
	{
		SBPPackageHeaderCacheStateInvalid,
		SBPPackageHeaderCacheStateAwaitHeaderStart,
		SBPPackageHeaderCacheStateAwaitHeaderRemainingData,
		SBPPackageHeaderCacheStateAwaitData
	}
	SBPPackageHeaderCacheState;

	typedef enum SBPPackageHeaderCacheChunkOrder_
	{
		SBPPackageHeaderCacheChunkOrderInvalid,
		SBPPackageHeaderCacheChunkOrderClose, // 0b00
		SBPPackageHeaderCacheChunkOrderFirst, // 0b01
		SBPPackageHeaderCacheChunkOrderMiddle, // 0b10
		SBPPackageHeaderCacheChunkOrderFinal, // 0b11
	}
	SBPPackageHeaderCacheChunkOrder;

	typedef struct SBPPackageHeaderChunk_
	{
		//---<Info>-----------------
		SBPPackageHeaderCacheChunkOrder Order;
		PXInt8U Channal;
		//--------------------------

		//---<Spesific temp data>---
		PXInt16U DataSizeCurrent;
		PXInt16U DataSizeTotal;
		//--------------------------

		//---<Volitile data>--------
		PXByte* Data;
		//--------------------------
	}
	SBPPackageHeaderChunk;


	typedef struct SBPPackageHeaderCache_ SBPPackageHeaderCache;

	typedef void (*SBPPackageHeaderChunkIOEvent)(void* const owner, SBPPackageHeaderCache* const sbpDataCache, const SBPPackageHeaderChunk* const sbpDataChunk);
	typedef void (*SBPPackageHeaderChunkChannalCreated)(void* const owner, SBPPackageHeaderCache* const sbpDataCache, const PXInt8U channalID);

	typedef struct SBPPackageHeaderCache_
	{
		SBPPackageHeaderCacheState State;

		// Data holding recieving data
		PXSize DataHeaderStartOffset;

		PXDataStream Data;

		// Callbacks for each channel
		PXDictionary DataCallBackLookup;

		// general CallBacks

		void* Owmer;

		SBPPackageHeaderChunkChannalCreated ChannalCreatedCallBack;
		SBPPackageHeaderChunkIOEvent DataChunkRecievedCallBack;
	}
	SBPPackageHeaderCache;




	PXPublic void SBPPackageHeaderCacheConstruct(SBPPackageHeaderCache* const sbpDataCache);
	PXPublic void SBPPackageHeaderCacheDestruct(SBPPackageHeaderCache* const sbpDataCache);

	PXPublic void SBPPackageHeaderCacheStateChange(SBPPackageHeaderCache* const sbpDataCache, const SBPPackageHeaderCacheState sbpDataCacheState);

	PXPublic void SBPPackageHeaderCacheHandle(SBPPackageHeaderCache* const sbpDataCache, const SBPPackageHeaderChunk* const sbpDataChunk);

	PXPublic void SBPPackageHeaderCacheChannalCallBackRegister(SBPPackageHeaderCache* const sbpDataCache, const PXInt8U channelID, const SBPPackageHeaderChunkIOEvent sbpDataChunkIOEvent);
	PXPublic void SBPPackageHeaderCacheChannalCallBackUnregister(SBPPackageHeaderCache* const sbpDataCache, const PXInt8U channelID);

	// Cache data if needed and trigger handling event of possible.
	PXPublic SBPPackageHeaderChunkResult SBPPackageHeaderCacheAppend(SBPPackageHeaderCache* const sbpDataCache, const void* const data, const PXSize dataSize);
	
#ifdef __cplusplus
}
#endif

#endif