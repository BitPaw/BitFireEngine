#include "Word.h"

BF::Word::Word()
{
	Set(0, 0);
}

BF::Word::Word(char byteA, char byteB)
{
	Set(byteA, byteB);
}

void BF::Word::Set(char byteA, char byteB)
{
	ByteA = byteA;
	ByteB = byteB;
}

unsigned int BF::Word::ExtractInt(EndianType endianType)
{
	switch (endianType)
	{
		case BF::EndianType::Big:
			return (ByteA << 8) | (ByteB);			

		default:
		case BF::EndianType::Little:
			return (ByteA) | (ByteB << 8);
	}
}

unsigned int BF::Word::InsertInt(EndianType endianType, unsigned int value)
{
	return 0;
}
