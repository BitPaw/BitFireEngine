#include "BitStreamHusk.h"

BF::BitStreamHusk::BitStreamHusk()
{
	StartAdress = nullptr;
	CurrentPosition = 0;
	DataLengh = 0;
	BlockSizeInBytes = 0;
	BlockSizeInBits = 0;
	CurrentBitOffset = 0;

	_leftToRight = true;
}

BF::BitStreamHusk::BitStreamHusk(unsigned char* startAdress, unsigned int dataLengh, bool leftToRight = true)
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

	if (_leftToRight)
	{
		CurrentBitOffset = 0;
	}
	else
	{
		CurrentBitOffset = 8u - 1u;
	}	
}

void BF::BitStreamHusk::SkipBitsToNextByte()
{
	if (_leftToRight)
	{
		if (CurrentBitOffset != 0)
		{
			CurrentPosition++;
			CurrentBitOffset = 0;
		}
	}
	else
	{
		if (CurrentBitOffset != 7u)
		{
			CurrentPosition--;
			CurrentBitOffset = 7;
		}
	}	
}

unsigned int BF::BitStreamHusk::ExtractBitsAndMove(unsigned char amountOfBits)
{
	unsigned int bitBlock;

	if (_leftToRight)
	{
		bitBlock = GetFromLeftCurrentPosition(amountOfBits);

		CurrentBitOffset += amountOfBits; // Add new offset, we used x bits, they are 'used up'.

		while (CurrentBitOffset >= 8) // Move a Byte at the time forward, 8 Bits = 1 Byte.
		{
			CurrentPosition++;
			CurrentBitOffset -= 8;
		}
	}
	else
	{
		bitBlock = GetFromRightCurrentPosition(amountOfBits);

		CurrentBitOffset -= amountOfBits; // Add new offset, we used x bits, they are 'used up'.

		while (CurrentBitOffset < 0) // Move a Byte at the time forward, 8 Bits = 1 Byte.
		{
			CurrentPosition++;
			CurrentBitOffset = 7u;
		}
	}

	return bitBlock;
}

unsigned int BF::BitStreamHusk::GetFromLeftCurrentPosition(unsigned char amountOfBits)
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

unsigned int BF::BitStreamHusk::GetFromRightCurrentPosition(unsigned char amountOfBits)
{
	unsigned int data = 0;

	data =	StartAdress[CurrentPosition  ]       |
			StartAdress[CurrentPosition+1] << 8  |
			StartAdress[CurrentPosition+2] << 16 |
			StartAdress[CurrentPosition+3] << 24;


	// 1111 1111 1111 1111 'Maximal Int'
	// 1111 1111 1100 0000 'Insert amountOfBits as Zeros'
	// 0000 0000 0011 1111 'Flip XOR'
	// 0000 0111 1110 0000 'Insert rightOffset as Zeros' 

	unsigned int rightOffset = 7u - CurrentBitOffset;
	unsigned int bitMask = (~(0xFFFFFFFF << amountOfBits)) << rightOffset;
	unsigned int result = 0;

	result = (data & bitMask) >> rightOffset;

	return result;
}