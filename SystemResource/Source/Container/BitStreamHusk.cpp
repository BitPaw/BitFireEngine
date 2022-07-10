#include "BitStreamHusk.h"
#include <stdio.h>
#include <cassert>

BF::BitStreamHusk::BitStreamHusk()
{
	RePosition(nullptr, 0);
}

BF::BitStreamHusk::BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh)
{
	RePosition(startAdress, dataLengh);
}

BF::BitStreamHusk::BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh, size_t startPosition)
{
	RePosition(startAdress, dataLengh);

	CurrentPosition = startPosition;
}

void BF::BitStreamHusk::RePosition(unsigned char* startAdress, unsigned int dataLengh)
{
	StartAdress = startAdress;
	DataLengh = dataLengh;
	CurrentPosition = 0;
	//BlockSizeInBytes = sizeof(unsigned char);
	BlockSizeInBits = 8;
	CurrentBitOffset = 0;
}

void BF::BitStreamHusk::SkipBitsToNextByte()
{
	if (CurrentBitOffset > 0)
	{
		CurrentBitOffset = 0;
		++CurrentPosition;
	}
}

unsigned int BF::BitStreamHusk::ExtractBitsAndMove(unsigned char amountOfBits)
{
	unsigned int result = ExtractBits(amountOfBits);

	Move(amountOfBits);

	return result;
}

unsigned int BF::BitStreamHusk::ExtractBits(unsigned char amountOfBits)
{
	unsigned int bitMask = ((1u << amountOfBits) - 1u) << CurrentBitOffset; // 0000111111
	unsigned int bitBlock;
	unsigned char* a = StartAdress + CurrentPosition;
	unsigned char* b = a + 1;
	unsigned char* c = a + 2;
	unsigned char* d = a + 3;
	unsigned char* maxAdress = StartAdress + (DataLengh -1);

	unsigned int ai = a > maxAdress ? 0 : *a;
	unsigned int bi = b > maxAdress ? 0 : *b;
	unsigned int ci = c > maxAdress ? 0 : *c;
	unsigned int di = d > maxAdress ? 0 : *d;

	// [d][c][b][a] Little Endian

	bitBlock = ai | bi << 8 | ci << 16 | di << 24;

	unsigned int result = bitBlock & bitMask;

#if defined(DEBUG)
	printf("Extract %i Bits. Byte__:%i Offset:%i\n", amountOfBits, CurrentPosition, CurrentBitOffset);
	printf("BitBlock : ");
	PrintBinary(bitBlock);
	printf("BitMask  : ");
	PrintBinary(bitMask);
	printf("Result   : ");
	PrintBinary(result);
#endif

	result >>= CurrentBitOffset; // Shoitft correction

#if defined(DEBUG)
	printf("Shifted  : ");
	PrintBinary(result);
#endif

	return result;
}

void BF::BitStreamHusk::Move(size_t amount)
{
	CurrentBitOffset += amount;

	Allign();
}

void BF::BitStreamHusk::Allign()
{
	while (CurrentBitOffset >= 8) // Move a Byte__ at the time forward, 8 Bits = 1 Byte__.
	{
		CurrentPosition++;
		CurrentBitOffset -= 8;
	}

	//assert(CurrentPosition < DataLengh);
}

void BF::BitStreamHusk::PrintBinary(unsigned int number)
{
	unsigned int filter = 1u;

	printf("[%10i] ", number);

	unsigned char d = number & 0x000000FF;
	unsigned char c = (number & 0x0000FF00) >> 8;
	unsigned char b = (number & 0x00FF0000) >> (8*2);
	unsigned char a = (number & 0xFF000000) >> (8*3);

	PrintBinary(a);
	PrintBinary(b);
	PrintBinary(c);
	PrintBinary(d);

	printf("\n");
}

void BF::BitStreamHusk::PrintBinary(unsigned char number)
{
	printf
	(
		"%c%c%c%c%c%c%c%c ",
		number & 0x80 ? '1' : '0',
		number & 0x40 ? '1' : '0',
		number & 0x20 ? '1' : '0',
		number & 0x10 ? '1' : '0',

		number & 0x08 ? '1' : '0',
		number & 0x04 ? '1' : '0',
		number & 0x02 ? '1' : '0',
		number & 0x01 ? '1' : '0'
	);
}
