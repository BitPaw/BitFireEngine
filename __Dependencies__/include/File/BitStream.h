#ifndef BitStreamInclude
#define BitStreamInclude

#include <stddef.h>

#include "Endian.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct BitStream_
	{
		unsigned char* Data;
		size_t DataSize;
		size_t DataCursor;
		size_t BitOffset;
	}
	BitStream;

	extern void BitStreamConstruct(BitStream* bitStream, void* data, const size_t dataSize);

	extern size_t BitStreamRemainingSize(BitStream* bitStream);
	extern unsigned char* BitStreamCursorPosition(BitStream* bitStream);

	//extern void BitStreamCursorPositionSet(BitStream* bitStream, unsigned char* startAdress, unsigned int dataLengh);
	extern void BitStreamSkipBitsToNextByte(BitStream* bitStream);
	extern size_t BitStreamCursorMoveInBytes(BitStream* bitStream, const size_t amountOfBytes);
	extern size_t BitStreamCursorMoveInBits(BitStream* bitStream, const size_t amountOfBits);
	extern void BitStreamAllign(BitStream* bitStream);

	extern size_t BitStreamRead(BitStream* bitStream, const size_t amountOfBits);

	extern size_t BitStreamWrite(BitStream* const bitStream, const size_t bitData, const size_t amountOfBits);

	extern size_t BitStreamReadFullByte(BitStream* bitStream);
	extern size_t BitStreamPeek(BitStream* bitStream, const size_t amountOfBits);

#endif

#ifdef __cplusplus
}
#endif