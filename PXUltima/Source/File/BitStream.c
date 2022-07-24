#include "BitStream.h"

#define BitStreamDebug 0

#if BitStreamDebug
#include <stdio.h>
#endif

void BitStreamConstruct(BitStream* bitStream, void* data, const size_t dataSize)
{
	bitStream->Data = data;
	bitStream->DataSize = dataSize;
	bitStream->DataCursor = 0;
	bitStream->BitOffset = 0;
}

size_t BitStreamRemainingSize(BitStream* bitStream)
{
	return bitStream->DataSize - bitStream->DataCursor;
}

unsigned char* BitStreamCursorPosition(BitStream* bitStream)
{
	return bitStream->Data + bitStream->DataCursor;
}

void BitStreamSkipBitsToNextByte(BitStream* bitStream)
{
	const unsigned char hasAnyBitConsumed = bitStream->BitOffset > 0;

	if(hasAnyBitConsumed)
	{
		bitStream->BitOffset = 0; // Reset
		++bitStream->DataCursor; // Go 1 Byte further
	}
}

size_t BitStreamCursorMoveInBytes(BitStream* bitStream, const size_t amountOfBytes)
{
	bitStream->DataCursor += amountOfBytes;

	return 0;
}

size_t BitStreamCursorMoveInBits(BitStream* bitStream, const size_t amountOfBits)
{
	bitStream->BitOffset += amountOfBits;

	BitStreamAllign(bitStream);

	return 0;
}

void BitStreamAllign(BitStream* bitStream)
{
	while(bitStream->BitOffset >= 8u) // Move a Byte__ at the time forward, 8 Bits = 1 Byte__.
	{
		bitStream->DataCursor++;
		bitStream->BitOffset -= 8u;
	}
}

size_t BitStreamRead(BitStream* bitStream, const size_t amountOfBits)
{
	const size_t result = BitStreamPeek(bitStream, amountOfBits);

	BitStreamCursorMoveInBits(bitStream, amountOfBits);

	return result;
}

size_t BitStreamPeek(BitStream* bitStream, const size_t amountOfBits)
{
	unsigned int bitMask = ((1u << amountOfBits) - 1u) << bitStream->BitOffset; // 0000111111
	unsigned int bitBlock;
	unsigned char* a = bitStream->Data + bitStream->DataCursor;
	unsigned char* b = a + 1;
	unsigned char* c = a + 2;
	unsigned char* d = a + 3;
	unsigned char* maxAdress = bitStream->Data + (bitStream->DataSize - 1);

	unsigned int ai = a > maxAdress ? 0 : *a;
	unsigned int bi = b > maxAdress ? 0 : *b;
	unsigned int ci = c > maxAdress ? 0 : *c;
	unsigned int di = d > maxAdress ? 0 : *d;

	// [d][c][b][a] Little Endian

	bitBlock = ai | bi << 8 | ci << 16 | di << 24;

	unsigned int result = bitBlock & bitMask;

#if BitStreamDebug
	printf("Extract %i Bits. Byte__:%i Offset:%i\n", amountOfBits, bitStream->DataCursor, bitStream->BitOffset);
	printf("BitBlock : ");
	PrintBinary(bitBlock);
	printf("BitMask  : ");
	PrintBinary(bitMask);
	printf("Result   : ");
	//PrintBinary(result);
#endif

	result >>= bitStream->BitOffset; // Shoitft correction

#if BitStreamDebug
	printf("Shifted  : ");
	//PrintBinary(result);
#endif

	return result;
}
