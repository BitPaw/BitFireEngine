#include "BitStreamHusk.h"

BF::BitStreamHusk::BitStreamHusk()
{
	StartAdress = nullptr;
	CurrentPosition = 0;
	DataLengh = 0;
	BlockSizeInBytes = 0;
	BlockSizeInBits = 0;
	CurrentBitOffset = 0;
}

BF::BitStreamHusk::BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh)
{
	RePosition(startAdress, dataLengh);
}

void BF::BitStreamHusk::RePosition(unsigned char* startAdress, unsigned int dataLengh)
{
	StartAdress = startAdress;
	DataLengh = dataLengh;
	CurrentPosition = 0;
	BlockSizeInBytes = sizeof(unsigned char);
	BlockSizeInBits = BlockSizeInBytes * 8;
	CurrentBitOffset = 0;
}

void BF::BitStreamHusk::SkipBitsToNextByte()
{
	if(CurrentBitOffset != 0)
	{
		CurrentPosition++;
		CurrentBitOffset = 0;
	}	
}

unsigned int BF::BitStreamHusk::ExtractBitsAndMove(unsigned char amountOfBits)
{
	unsigned int bitBlock = GetFromCurrentPosition(amountOfBits);

	CurrentBitOffset += amountOfBits; // Add new offset, we used x bits, they are 'used up'.

	while (CurrentBitOffset >= 8) // Move a Byte at the time forward, 8 Bits = 1 Byte.
	{
		CurrentPosition++;
		CurrentBitOffset -= 8;
	}

	return bitBlock;
}

unsigned int BF::BitStreamHusk::GetFromCurrentPosition(unsigned char amountOfBits)
{
	unsigned int maxInteger = 0xFFFFFFFF;
	unsigned int bitMask = (maxInteger << amountOfBits) ^ maxInteger; // how many 1's do we have? Seen in binary.
	unsigned int fourByteBlock = 0;
	unsigned int bitBlock = 0;

	for (unsigned int i = 0; i < 4; i++) // 4 Bytes = one Integer
	{
		if (CurrentPosition + i < DataLengh) // if we are in bounds, get the next byte, else take 0 (does nothing).
		{
			unsigned char rawByte = StartAdress[CurrentPosition + i];
			unsigned int rawData = rawByte;
			fourByteBlock |= rawByte << (i * 8); // 1. Get Value, 2.shift it to the left, 3.logic AND.
		}
	}

	//       <--- 
	// ...01 1110 00.... Shift bitmask to wanted position. 
	bitMask <<= CurrentBitOffset;

	/*
	From our data	--Byte-D- --Byte-C- --Byte-B- --Byte-A-		Byte order, Little Endian
	fourByteBlock	0101 1010 0101 1010 0101 1010 0101 1010		Some value
	bitMask			0000 0000 0000 0000 0001 1111 1111 1000		Get me the first 10 bits, offset 3"
					---------------------------------------
	logic-AND		0000 0000 0000 0000 0001 1010 0101 1000	    AND-Value
														/\
														||
	Now we have a offset in our result, need to shift this back.
	*/
	bitBlock = (fourByteBlock & bitMask) >> CurrentBitOffset;

	return bitBlock;
}