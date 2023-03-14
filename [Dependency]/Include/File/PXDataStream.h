#ifndef PXDataStreamINCLUDE
#define PXDataStreamINCLUDE

#include <Format/Type.h>
#include <OS/Error/PXActionResult.h>
#include <OS/File/File.h>
#include <OS/File/Endian.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum PXDataStreamLocation_
	{
		FileLocationInvalid,
		FileLocationExternal,
		FileLocationMappedVirtual, // Used 'VirtalAlloc()' / 'mmap()'
		FileLocationMappedFromDisk, // Used 'FileView()' / 'fmap()'
		FileLocationCachedFromDisk, // When the file is cached into an CPrivate buffer
		FileLocationLinked // Used existing file with 'fopen()'
	}
	PXDataStreamLocation;

	typedef enum DataPersistence_
	{
		PersistenceInvalid,
		PersistencePermanent,
		PersistenceTempoary
	}
	DataPersistence;

	typedef enum PXDataStreamCachingMode_
	{
		FileCachingDefault,

		FileCachingRandom,  // Access data in a random order.
		FileCachingSequential, // Data sequentially from lower offsets to higher offsets.
		FileCachingTemporary, // File will not be saves to drive.
		FileCachingUseOnce, // Access the specified data once and then not reuse it again.

		// Windows only
		FileCachingWriteThrough,
		FileCachingNoBuffering, // No OS Caching, direct to Harddrive if supprted

		// UNIX only
		FileCachingNeedLater, // Data is not needed right now. "For later"[near future].
		FileCachingDontNeedNow // Data will not be cached. "I dont need it yet"
	}
	PXDataStreamCachingMode;

	typedef struct PXDataStreamElementType_
	{
		PXDataType Type;
		void* Adress;
	}
	PXDataStreamElementType;

	typedef struct PXDataStream_
	{
		//---<Raw Data>--------------------------------------------------------
		void* Data; // [Do not use directly] Data from where to read/write depending on the used method of linking.
		PXSize DataCursor; // [Do not use directly] Current position of the data.
		PXSize DataCursorBitOffset; // [Do not use directly] Current offset in bits of current byte
		PXSize DataSize; // [Do not use directly] The total size of the data block.
		PXSize DataAllocated; // [Do not use directly] The size of the data pace in which you can move without triggering an invalid access.
		//---------------------------------------------------------------------

		//---<Temporal>--------------------------------------------------------
		PXByte* FilePath; // Temporal refrence to the source data, link needs to be removed afetr use!
		//---------------------------------------------------------------------

		//---<Extended Settings>-----------------------------------------------
		MemoryProtectionMode MemoryMode;
		PXDataStreamLocation DataLocation; // Where the is stored, used as indicator how to clean up.
		//---------------------------------------------------------------------

		//---<Internal location Info>------------------------------------------
		FileHandleType FileHandle; // Only used if file is used directly
		FileMappingID IDMapping; // Only used while mapping a file

#if OSUnix

#elif OSWindows
		FILE* FileHandleCStyle; // Used for writing only, usage of fprintf()
#endif
		//---------------------------------------------------------------------
	}
	PXDataStream;

	//---------------------------------------------------------------------
	PXPublic void PXDataStreamConstruct(PXDataStream* const dataStream);
	PXPublic void PXDataStreamDestruct(PXDataStream* const dataStream);
	//---------------------------------------------------------------------

	//---<Convert>---------------------------------------------------------
	PXPrivate PXDataStreamCachingMode ConvertToFileCachingMode(const unsigned int value);
	PXPrivate unsigned int ConvertFromFileCachingMode(const PXDataStreamCachingMode fileCachingMode);
	//---------------------------------------------------------------------

	//---<Set>-------------------------------------------------------------
	PXPublic void PXDataStreamFromExternal(PXDataStream* const dataStream, void* const data, const PXSize dataSize);
	//---------------------------------------------------------------------

	//---<Open>------------------------------------------------------------
	PXPublic PXActionResult PXDataStreamOpenFromPathA(PXDataStream* const dataStream, const PXTextASCII filePath, const MemoryProtectionMode fileOpenMode, const PXDataStreamCachingMode dataStreamCachingMode);
	PXPublic PXActionResult PXDataStreamOpenFromPathW(PXDataStream* const dataStream, const PXTextUNICODE filePath, const MemoryProtectionMode fileOpenMode, const PXDataStreamCachingMode dataStreamCachingMode);
	PXPublic PXActionResult PXDataStreamOpenFromPathU(PXDataStream* const dataStream, const PXTextUTF8 filePath, const MemoryProtectionMode fileOpenMode, const PXDataStreamCachingMode dataStreamCachingMode);
	//---------------------------------------------------------------------

	//---<Close>-----------------------------------------------------------
	PXPublic PXActionResult PXDataStreamClose(PXDataStream* const dataStream);
	//---------------------------------------------------------------------

	//---<Mapping>---------------------------------------------------------
	PXPublic PXActionResult PXDataStreamMapToMemoryA(PXDataStream* const dataStream, const PXTextASCII filePath, const PXSize fileSize, const MemoryProtectionMode protectionMode);
	PXPublic PXActionResult PXDataStreamMapToMemoryW(PXDataStream* const dataStream, const PXTextUNICODE filePath, const PXSize fileSize, const MemoryProtectionMode protectionMode);
	PXPublic PXActionResult PXDataStreamMapToMemoryU(PXDataStream* const dataStream, const PXTextUTF8 filePath, const PXSize fileSize, const MemoryProtectionMode protectionMode);
	PXPublic PXActionResult PXDataStreamMapToMemory(PXDataStream* const dataStream, const PXSize size, const MemoryProtectionMode protectionMode);
	PXPublic PXActionResult PXDataStreamUnmapFromMemory(PXDataStream* const dataStream);
	//---------------------------------------------------------------------

	//---<Parsing Utility>-----------------------------------------------------
	PXPublic PXSize PXDataStreamRemainingSize(const PXDataStream* __restrict const dataStream);
	PXPublic PXBool PXDataStreamIsAtEnd(const PXDataStream* __restrict const dataStream);

	PXPublic void* PXDataStreamCursorPosition(PXDataStream* const dataStream);
	PXPublic void PXDataStreamCursorMoveTo(PXDataStream* const dataStream, const PXSize position);
	PXPublic void PXDataStreamCursorToBeginning(PXDataStream* const dataStream);
	PXPublic PXSize PXDataStreamCursorAdvance(PXDataStream* const dataStream, const PXSize steps);
	PXPublic void PXDataStreamCursorRewind(PXDataStream* const dataStream, const PXSize steps);
	PXPublic void PXDataStreamCursorToEnd(PXDataStream* const dataStream);
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	PXPublic PXSize PXDataStreamSkipEndOfLineCharacters(PXDataStream* const  PXDataStream);
	PXPublic PXSize PXDataStreamSkipEmptySpace(PXDataStream* const dataStream);

	PXPublic PXSize PXDataStreamReadNextLineInto(PXDataStream* const dataStream, void* exportBuffer, const PXSize exportBufferSize);


	// Skips current block thats seperated with spaces.
	// Example : '|' is the cursor.
	// Before : |AAAA  BBBB CCC
	// After :  AAAA |BBBB CCC
	PXPublic PXSize PXDataStreamSkipBlock(PXDataStream* const dataStream);
	PXPublic PXSize PXDataStreamSkipToNextBlock(PXDataStream* const dataStream);
	PXPublic PXSize PXDataStreamSkipLine(PXDataStream* const dataStream);


	PXPublic PXSize PXDataStreamDataCopy(PXDataStream* const pxInputStream, PXDataStream* const pxOutputStream, const PXSize length);

	PXPublic PXSize PXDataStreamReadTextIU8(PXDataStream* const dataStream, PXInt8U* const number);
	PXPublic PXSize PXDataStreamReadTextI(PXDataStream* const dataStream, int* const number);


	PXPublic PXSize PXDataStreamReadI8S(PXDataStream* const dataStream, PXInt8S* const value);
	PXPublic PXSize PXDataStreamReadI8SV(PXDataStream* const dataStream, PXInt8S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI8U(PXDataStream* const dataStream, PXInt8U* const value);
	PXPublic PXSize PXDataStreamReadI8UV(PXDataStream* const dataStream, PXInt8U* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamReadI16S(PXDataStream* const dataStream, PXInt16S* const value);
	PXPublic PXSize PXDataStreamReadI16SV(PXDataStream* const dataStream, PXInt16S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI16SE(PXDataStream* const dataStream, PXInt16S* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI16SVE(PXDataStream* const dataStream, PXInt16S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamReadI16U(PXDataStream* const dataStream, PXInt16U* const value);
	PXPublic PXSize PXDataStreamReadI16UV(PXDataStream* const dataStream, PXInt16U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI16UE(PXDataStream* const dataStream, PXInt16U* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI16UVE(PXDataStream* const dataStream, PXInt16U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamReadI32S(PXDataStream* const dataStream, PXInt32S* const value);
	PXPublic PXSize PXDataStreamReadI32SV(PXDataStream* const dataStream, PXInt32S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI32SE(PXDataStream* const dataStream, PXInt32S* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI32SVE(PXDataStream* const dataStream, PXInt32S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamReadI32U(PXDataStream* const dataStream, PXInt32U* const value);
	PXPublic PXSize PXDataStreamReadI32UV(PXDataStream* const dataStream, PXInt32U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI32UE(PXDataStream* const dataStream, PXInt32U* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI32UVE(PXDataStream* const dataStream, PXInt32U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamReadI64S(PXDataStream* const dataStream, PXInt64S* const value);
	PXPublic PXSize PXDataStreamReadI64SV(PXDataStream* const dataStream, PXInt64S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI64SE(PXDataStream* const dataStream, PXInt64S* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI64VE(PXDataStream* const dataStream, PXInt64S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamReadI64U(PXDataStream* const dataStream, PXInt64U* const value);
	PXPublic PXSize PXDataStreamReadI64UV(PXDataStream* const dataStream, PXInt64U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamReadI64UE(PXDataStream* const dataStream, PXInt64U* const value, const Endian endian);
	PXPublic PXSize PXDataStreamReadI64UVE(PXDataStream* const dataStream, PXInt64U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamReadF(PXDataStream* const dataStream, float* const value);
	PXPublic PXSize PXDataStreamReadFV(PXDataStream* const dataStream, float* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamReadD(PXDataStream* const dataStream, double* const value);
	PXPublic PXSize PXDataStreamReadDV(PXDataStream* const dataStream, double* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamReadMultible(PXDataStream* const dataStream, PXDataStreamElementType* const pxDataStreamElementList, const PXSize pxDataStreamElementListSize);

	PXPublic PXSize PXDataStreamReadB(PXDataStream* const dataStream, void* const value, const PXSize length);
	
	// read Text
	PXPublic PXSize PXDataStreamReadTextA(PXDataStream* const dataStream, PXTextASCII value, const PXSize length);
	PXPublic PXSize PXDataStreamReadTextW(PXDataStream* const dataStream, PXTextUNICODE value, const PXSize length);
	PXPublic PXSize PXDataStreamReadTextU(PXDataStream* const dataStream, PXTextUNICODE value, const PXSize length);

	PXPublic void PXDataStreamReadUntil(PXDataStream* const dataStream, void* value, const PXSize length, const char character);



	// Additional check how many bytes are read.
	// Slower version of Read(), this function can't fail.
	//PXSize ReadSafe(Byte__* value, const PXSize length);


	PXPublic PXBool PXDataStreamReadAndCompare(PXDataStream* const dataStream, const void* value, const PXSize length);
	PXPublic PXBool PXDataStreamReadAndCompareV(PXDataStream* const dataStream, const void** value, const PXSize* valueElementSizeList, const PXSize valueLength);
	//unsigned char PXDataStreamReadAndCompareC(PXDataStream* PXDataStream, const char value);
	//unsigned char PXDataStreamReadAndCompareIU(PXDataStream* PXDataStream, const unsigned int value);

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	PXPublic PXSize PXDataStreamWriteI8S(PXDataStream* const dataStream, const PXInt8S value);
	PXPublic PXSize PXDataStreamWriteI8SV(PXDataStream* const dataStream, const PXInt8S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI8U(PXDataStream* const dataStream, const PXInt8U value);
	PXPublic PXSize PXDataStreamWriteAtI8U(PXDataStream* const dataStream, const PXInt8U value, const PXSize index);
	PXPublic PXSize PXDataStreamWriteI8UV(PXDataStream* const dataStream, const PXInt8U* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamWriteI16S(PXDataStream* const dataStream, const PXInt16S const value);
	PXPublic PXSize PXDataStreamWriteI16SV(PXDataStream* const dataStream, const PXInt16S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI16SE(PXDataStream* const dataStream, const PXInt16S const value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI16SVE(PXDataStream* const dataStream, const PXInt16S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI16U(PXDataStream* const dataStream, const PXInt16U const value);
	PXPublic PXSize PXDataStreamWriteAtI16U(PXDataStream* const dataStream, const PXInt16U const value, const PXSize index);
	PXPublic PXSize PXDataStreamWriteI16UV(PXDataStream* const dataStream, const PXInt16U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI16UE(PXDataStream* const dataStream, const PXInt16U const value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI16UVE(PXDataStream* const dataStream, const PXInt16U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamWriteI32S(PXDataStream* const dataStream, const PXInt32S value);
	PXPublic PXSize PXDataStreamWriteI32SV(PXDataStream* const dataStream, const PXInt32S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI32SE(PXDataStream* const dataStream, const PXInt32S value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI32SVE(PXDataStream* const dataStream, const PXInt32S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI32U(PXDataStream* const dataStream, const PXInt32U value);
	PXPublic PXSize PXDataStreamWriteAtI32U(PXDataStream* const dataStream, const PXInt32U value, const PXSize index);
	PXPublic PXSize PXDataStreamWriteI32UV(PXDataStream* const dataStream, const PXInt32U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI32UE(PXDataStream* const dataStream, const PXInt32U value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteAtI32UE(PXDataStream* const dataStream, const PXInt32U value, const Endian endian, const PXSize index);
	PXPublic PXSize PXDataStreamWriteI32UVE(PXDataStream* const dataStream, const PXInt32U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamWriteI64S(PXDataStream* const dataStream, const PXInt64S const value);
	PXPublic PXSize PXDataStreamWriteI64SV(PXDataStream* const dataStream, const PXInt64S* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI64SE(PXDataStream* const dataStream, const PXInt64S const value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI64VE(PXDataStream* const dataStream, const PXInt64S* const valueList, const PXSize valueListSize, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI64U(PXDataStream* const dataStream, const PXInt64U const value);
	PXPublic PXSize PXDataStreamWriteI64UV(PXDataStream* const dataStream, const PXInt64U* const valueList, const PXSize valueListSize);
	PXPublic PXSize PXDataStreamWriteI64UE(PXDataStream* const dataStream, const PXInt64U const value, const Endian endian);
	PXPublic PXSize PXDataStreamWriteI64UVE(PXDataStream* const dataStream, const PXInt64U* const valueList, const PXSize valueListSize, const Endian endian);

	PXPublic PXSize PXDataStreamWriteF(PXDataStream* const dataStream, const float value);
	PXPublic PXSize PXDataStreamWriteFV(PXDataStream* const dataStream, const float* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamWriteD(PXDataStream* const dataStream, const double value);
	PXPublic PXSize PXDataStreamWriteDV(PXDataStream* const dataStream, const double* const valueList, const PXSize valueListSize);

	PXPublic PXSize PXDataStreamWriteB(PXDataStream* const dataStream, const void* const value, const PXSize length);
	PXPublic PXSize PXDataStreamWriteAtB(PXDataStream* const dataStream, const void* const data, const PXSize dataSize, const PXSize index);

	PXPublic PXSize PXDataStreamWriteMultible(PXDataStream* const dataStream, const PXDataStreamElementType* const pxDataStreamElementList, const PXSize pxDataStreamElementListSize);

	PXPublic PXSize PXDataStreamWriteFill(PXDataStream* const dataStream, const unsigned char value, const PXSize length);

	// Write ASCII string \0 terminated.
	PXPublic PXSize PXDataStreamWriteA(PXDataStream* const dataStream, const char* const text, PXSize textSize);

	// Write UNICODE string \0 terminated
	PXPublic PXSize PXDataStreamWriteW(PXDataStream* const dataStream, const wchar_t* const text, PXSize textSize);




	PXPublic PXSize PXDataStreamWrite(PXDataStream* const dataStream, const char* format, ...);
	//-------------------------------------------------------------------------



	//---<Extra bit stuff>-----------------------------------------------------
	PXPublic PXSize PXDataStreamSkipBitsToNextByte(PXDataStream* const dataStream);
	PXPublic PXSize PXDataStreamCursorMoveBits(PXDataStream* const dataStream, const PXSize amountOfBits);
	PXPublic PXSize PXDataStreamBitsAllign(PXDataStream* const dataStream);

	PXPublic PXSize PXDataStreamPeekBits(PXDataStream* const dataStream, const PXSize amountOfBits);
	PXPublic PXSize PXDataStreamReadBits(PXDataStream* const dataStream, const PXSize amountOfBits);

	PXPublic PXSize PXDataStreamWriteBits(PXDataStream* const dataStream, const PXSize bitData, const PXSize amountOfBits);
	//-------------------------------------------------------------------------


	PXPublic PXSize PXDataStreamFilePathGetA(PXDataStream* const dataStream, char* const filePath, const PXSize filePathMaxSize);
	PXPublic PXSize PXDataStreamFilePathGetW(PXDataStream* const dataStream, wchar_t* const filePath, const PXSize filePathMaxSize);

#ifdef __cplusplus
}
#endif

#endif
