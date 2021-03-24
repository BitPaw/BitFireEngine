#include "HuffmanCodeFixed.h"

unsigned char BF::HuffmanCodeFixed::GetBitLengh(unsigned int value)
{
	if (value < 144)
	{
		return 8;
	}
	
	if (value < 256)
	{
		return 9;
	}

	if (value < 280)
	{
		return 7;
	}

	return 8;
}

unsigned char BF::HuffmanCodeFixed::TranslateIndex(unsigned char index)
{
	// 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15

	switch (index)
	{
		case 1: return 16;
		case 2: return 17;
		case 3: return 18;
		case 4: return 0;
		case 5: return 8;
		case 6: return 7;
		case 7: return 9;
		case 8: return 6;
		case 9: return 10;
		case 10: return 5;
		case 11: return 11;
		case 12: return 4;
		case 13: return 12;
		case 14: return 3;
		case 15: return 13;
		case 16: return 2;
		case 17: return 14;
		case 18: return 1;
		case 19: return 15;	

		default: return -1;
	}
}

unsigned int BF::HuffmanCodeFixed::DecodeRunLength(unsigned int value, BitStreamHusk& bitStream)
{
	bool isInValidRange = value < 257 || value > 287;

	if (isInValidRange)  // Cannot occur in the bit stream; indicates the decompressor is buggy
	{
		throw "Invalid run length symbol";
	}		
	else if (value <= 264)
	{
		return value - 254;
	}	
	else if (value <= 284)
	{
		int numExtraBits = (value - 261) / 4;
		return (((value - 265) % 4 + 4) << numExtraBits) + 3 + bitStream.ExtractBitsAndMove(numExtraBits);
	}
	else if (value == 285)
	{
		return 258;
	}
	else// sym is 286 or 287
	{
		throw "Reserved length symbol";
	}			
}

unsigned int BF::HuffmanCodeFixed::DecodeDistance(unsigned int value, BitStreamHusk& bitStream)
{
	if (value < 0 || value > 31)  // Cannot occur in the bit stream; indicates the decompressor is buggy
	{
		throw "Invalid distance symbol: ";
	}		
	if (value <= 3)
	{
		return value + 1;
	}		
	else if (value <= 29)
	{
		int numExtraBits = value / 2 - 1;
		return ((value % 2 + 2) << numExtraBits) + 1 + bitStream.ExtractBitsAndMove(numExtraBits);
	}
	else  // sym is 30 or 31
	{
		throw "Reserved distance symbol: ";
	}
		
}

unsigned int BF::HuffmanCodeFixed::DecodeNextSymbol(BitStreamHusk& bitStream)
{
	int codeBits = 1;  // The start bit

	while (true) 
	{
		// Accumulate one bit at a time on the right side until a match is
		// found in the symbolCodeBits array. Because the Huffman code tree is
		// full, this loop must terminate after at most MAX_CODE_LENGTH iterations.
		codeBits = codeBits << 1 | bitStream.ExtractBitsAndMove(5);
		
		int index = HuffmanCodeFixed::GetBitLengh(codeBits);

		return index;

		/*
		if (index >= 0)
		{
			return symbolValues[index];
		}	*/	
	}
}

unsigned int BF::HuffmanCodeFixed::FindNextLiteralSymbol(BitStreamHusk& bitStream)
{
	/*
	  0 - 143     8          00110000 through 10111111
	144 - 255     9          110010000 through 111111111
	256 - 279     7          0000000 through 0010111
	280 - 287     8          11000000 through 11000111
	*/


		// Accumulate one bit at a time on the right side until a match is
		// found in the symbolCodeBits array. Because the Huffman code tree is
		// full, this loop must terminate after at most MAX_CODE_LENGTH iterations.

	bool is7Bit;
	bool is8BitA;
	bool is8BitB;
	bool is9Bit;
	unsigned int codeBits;


	codeBits = bitStream.ExtractBitsAndMove(7);

	is7Bit = 0b0000000 < codeBits && codeBits < 0b0010111; // 0 - 23

	if (is7Bit)
	{
		return codeBits;
	}

	codeBits = codeBits << 1 | bitStream.ExtractBitsAndMove(1);

	is8BitA = 0b00110000 < codeBits && codeBits < 0b10111111; // 48 - 191
	is8BitB = 0b11000000 < codeBits && codeBits < 0b11000111; // 192 - 199

	if (is8BitA)
	{
		return codeBits;
	}

	if (is8BitB)
	{
		return codeBits;
	}

	codeBits = codeBits << 1 | bitStream.ExtractBitsAndMove(1);

	is9Bit = 0b110010000 < codeBits && codeBits < 0b111111111; // 400 - 511

	if (is9Bit)
	{
		return codeBits;
	}

	return -1;	
}

unsigned int BF::HuffmanCodeFixed::FindNextDistancelSymbol(BitStreamHusk& bitStream)
{
	return bitStream.ExtractBitsAndMove(3);
}
